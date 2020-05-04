#include "QCameraWidget.hpp"

using namespace cv;
using namespace std;

QCameraWidget::QCameraWidget(QWidget* parent)
	: QWidget(parent)
{
	m_videoCapture.open(0);

	if (!m_videoCapture.isOpened()) {
		throw new Exception(0, "Problème d'ouverture de la caméra", "", "", 0);
	}

	// On vérifie si la machine prend en charge au moins deux threads sinon l'analyse d'image se fera en monothread
	m_bThreadsEnabled = (thread::hardware_concurrency() >= 2);
	
	connect(&m_qTimer, &QTimer::timeout, this, &QCameraWidget::_updateWindow);
	connect(this, &QCameraWidget::cameraImgUpdated, this, &QCameraWidget::_findDices);
	m_qTimer.start(20);

	m_ui.setupUi(this);
}

QCameraWidget::~QCameraWidget()
{
	m_videoCapture.release();
}

void QCameraWidget::_updateWindow()
{
	// On récupère l'image
	m_videoCapture >> m_matImageCaptured;

	m_ui.label->setPixmap(QPixmap::fromImage(
		QImage(m_matImageCaptured.data, m_matImageCaptured.cols, m_matImageCaptured.rows, QImage::Format_RGB888)
	));
	m_ui.label->resize(m_ui.label->pixmap()->size());

	cv::resize(m_matImageCaptured, m_matImageCaptured, Size(640, 480));

	emit cameraImgUpdated();
}

void QCameraWidget::_findDices()
{
	list<shared_ptr<CDice>> lDetectedDices;

	size_t nDicesDetectedByMinArea;
	size_t nDicesDetectedByBlob;

	if (m_bThreadsEnabled)
	{
		m_lThreads.push_back(make_unique<std::thread>(&QCameraWidget::_findDicesByMinArea, this, ref(lDetectedDices), ref(nDicesDetectedByMinArea)));
		m_lThreads.push_back(make_unique<std::thread>(&QCameraWidget::_findDicesByBlob, this, ref(nDicesDetectedByBlob)));

		for (unique_ptr<std::thread>& thread : m_lThreads)
		{
			thread->join();
		}

		m_lThreads.clear();
	}
	else
	{
		_findDicesByMinArea(lDetectedDices, nDicesDetectedByMinArea);
		_findDicesByBlob(nDicesDetectedByBlob);
	}

	// On regarde si les deux algorithmes comptent le même total 
	if (nDicesDetectedByMinArea == nDicesDetectedByBlob)
	{
		if (m_lDices.size() == 0)
		{
			for (shared_ptr<CDice> dice : lDetectedDices)
			{
				m_lDices.push_back(dice);
			}
			
			return;
		}

		// On regarde les similitudes entre les dés déjà enregistrés et ceux venant d'être détéctés
		for (auto itDetectedDices = lDetectedDices.begin(); itDetectedDices != lDetectedDices.end(); itDetectedDices++)
		{
			for (auto itDice = m_lDices.begin(); itDice != m_lDices.end(); itDice++)
			{
				// Si le dé est un faux positif ou si on l'a déjà traité, on passe
				if (((*itDetectedDices)->getCount() == 0) || (*itDetectedDices)->getCount() > 6 || (std::find(m_lDicesBuffer.begin(), m_lDicesBuffer.end(), *itDetectedDices) != m_lDicesBuffer.end()))
				{
					continue;
				}

				// Si le numéro est le même, on compare la position pour savoir si c'est le même dé (avec une marge d'erreur / tolérance)
				if ((*itDetectedDices)->getCount() == (*itDice)->getCount())
				{
					const float fX = std::abs<float>((*itDetectedDices)->getDiceRect().boundingRect().x - (*itDice)->getDiceRect().boundingRect().x);
					const float fY = std::abs<float>((*itDetectedDices)->getDiceRect().boundingRect().y - (*itDice)->getDiceRect().boundingRect().y);

					if (fX <= SAME_POS_TOLERANCE && fY <= SAME_POS_TOLERANCE)
					{
						m_lDicesBuffer.push_back(*itDetectedDices);
					}
				}
				else
				{
					m_lDicesBuffer.push_back(*itDetectedDices);
				}
			}
		}

		// Si on détecte plus de 5 dés
		if (m_lDicesBuffer.size() > 5)
		{
			QMessageBox messageBox;
			messageBox.setText(QString::fromLatin1("Plus de 5 dés détectés !"));
			messageBox.exec();
			
		}
		else if (m_lDicesBuffer.size() == 5)
		{
			m_lDices.clear();
			m_lDices = m_lDicesBuffer;

			// On compte les dés par capacité
			int* pDiceSet = new int[6]{ 0, 0, 0, 0, 0, 0 };
			for (shared_ptr<CDice>& const dice : m_lDices)
			{
				pDiceSet[dice->getCount() - 1]++;
			}

			// Si on obtient le même set de dés que précédemment, on passe, sinon on émet le signal
			for (int i = 0; i < 6; ++i)
			{
				if (pDiceSet[i] != m_pLastDiceSet[i])
				{
					delete m_pLastDiceSet;
					m_pLastDiceSet = pDiceSet;
					
					emit dicesUpdated(pDiceSet);
					break;
				}
			}
		}
		
		m_lDicesBuffer.clear();
	}

	//_debug(nDicesDetectedByMinArea, nDicesDetectedByBlob);
}

void QCameraWidget::_findDicesByMinArea(list<shared_ptr<CDice>>& lDetectedDices, size_t& iNDetectedDices)
{
	iNDetectedDices = 0;

	Mat matImageBuffer;
	
	// Passage de l'image en niveau de gris
	cvtColor(m_matImageCaptured, matImageBuffer, COLOR_BGR2GRAY);
	
	// Suppression du bruit
	blur(matImageBuffer, matImageBuffer, Size(3, 3));
	
	// Filtre de Canny afin d'extraire les contours
	Canny(matImageBuffer, matImageBuffer, MIN_THRESHOLD, MAX_THRESHOLD);

	// Extraction des contours et de la hierarchie
	vector<vector<Point>> vContours;
	vector<Vec4i> vHierarchy;
	findContours(matImageBuffer, vContours, vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	// On veut déterminer les rectangles qui sont contours des dés
	for (vector<Point>& contour : vContours)
	{
		// Pour chaque contour, on cherche l'aire minimum du triangle
		RotatedRect rect = minAreaRect(contour);
		
		// On traite uniquement les rectangles qui n'ont pas des angles droits parfaits
		// L'aire dépend de la résolution de la webcam
		const float fAspect = fabs(rect.size.aspectRatio() - 1);
		if ((fAspect < 0.25) && (rect.size.area() > MIN_DICE_WIDTH) && (rect.size.area() < MAX_DICE_WIDTH))
		{
			// On vérifie le rectangle ou un rectangle proche n'a pas déjà été assigné
			bool bProcess = true;
			for (shared_ptr<CDice>& dice : lDetectedDices)
			{
				float dist = norm(rect.center - dice->getDiceRect().center);
				if (dist < 10)
				{
					bProcess = false;
					break;
				}
			}

			if (bProcess)
			{
				lDetectedDices.push_back(make_shared<CDice>(rect));
			}
		}
	}
	
	// On compte les points de chaque dé
	for (shared_ptr<CDice>& dice : lDetectedDices)
	{
		// Extraction du dés de l'image
		Mat rotation, rotated, cropped;
		RotatedRect rect = dice->getDiceRect();
		rotation = getRotationMatrix2D(rect.center, rect.angle, 1.0);
		warpAffine(matImageBuffer, rotated, rotation, matImageBuffer.size(), INTER_CUBIC);
		getRectSubPix(rotated, Size(rect.size.width - 10, rect.size.height - 10), rect.center, cropped);

		// On cherche les contours
		vector<vector<Point>> vDotContours;
		vector<Vec4i> vDotHierarchy;
		threshold(cropped, cropped, 64, 255, THRESH_BINARY);
		findContours(cropped, vDotContours, vDotHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		// On cherche les rectangles des points
		for (vector<Point>& diceContour : vDotContours)
		{
			// Pour chaque contour on associe un rectangle
			RotatedRect rect = minAreaRect(diceContour);

			const float aspect = std::abs<float>(rect.size.aspectRatio() - 1);
			if ((aspect < 0.4) && (rect.size.area() > MIN_DICE_DOT_WIDTH) && (rect.size.area() < MAX_DICE_DOT_WIDTH)) {
				bool process = true;

				for (RotatedRect& dotRect : dice->getDotRects())
				{
					float dist = norm(rect.center - dotRect.center);
					if (dist < 10)
					{
						process = false;
						break;
					}
				}

				if (process) {
					dice->addDotRect(rect);
					iNDetectedDices++;
				}
			}
		}
	}
}

void QCameraWidget::_findDicesByBlob(size_t& iNDetectedDices)
{
	Mat grayImage;
	cvtColor(m_matImageCaptured, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	SimpleBlobDetector::Params detectorParams;
	detectorParams.filterByArea = true;
	detectorParams.filterByCircularity = true;
	detectorParams.filterByInertia = true;
	detectorParams.minThreshold = MIN_THRESHOLD;
	detectorParams.maxThreshold = MAX_THRESHOLD;
	detectorParams.minArea = MIN_AREA;
	detectorParams.minCircularity = MIN_CIRCULARITY;
	detectorParams.minInertiaRatio = MIN_INERTIA_RATIO;

	const Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(detectorParams);

	std::vector<KeyPoint> keypoints;
	detector->detect(grayImage, keypoints);

	iNDetectedDices = keypoints.size();
}

void QCameraWidget::_debug(int& const iNDicesDetectedByMinArea, int& const iNDicesDetectedByBlob)
{
	static bool bOK = false;

	if (iNDicesDetectedByBlob == iNDicesDetectedByMinArea && iNDicesDetectedByBlob != 0) {
		bOK = true;
	}
	
	char buffer[64];
	sprintf_s(buffer, "Dice: %s : MinArea : %d - Blob : %d", (bOK) ? "OK" : "NN", iNDicesDetectedByMinArea, iNDicesDetectedByBlob);
	putText(m_matImageCaptured, buffer, Point(20, 30), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 255, 0), 1, LINE_AA);

	m_ui.label->setPixmap(QPixmap::fromImage(
		QImage(m_matImageCaptured.data, m_matImageCaptured.cols, m_matImageCaptured.rows, QImage::Format_RGB888)
		));
	m_ui.label->resize(m_ui.label->pixmap()->size());
}
