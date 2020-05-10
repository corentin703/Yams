#include "QCameraWidget.hpp"

using namespace cv;
using namespace std;

QCameraWidget::QCameraWidget(QWidget* parent)
	: QWidget(parent)
{
	m_videoCapture.open(0);

	if (!m_videoCapture.isOpened()) {
		throw new Exception(0, "Probl�me d'ouverture de la cam�ra", "", "", 0);
	}

	// On v�rifie si la machine prend en charge au moins deux threads sinon l'analyse d'image se fera en monothread
	m_bThreadsEnabled = (thread::hardware_concurrency() >= 2);
	
	connect(&m_qTimerFrame, &QTimer::timeout, this, &QCameraWidget::_updateWindow);
	connect(this, &QCameraWidget::cameraImgUpdated, this, &QCameraWidget::_findDices);
	m_qTimerFrame.start(20);

	m_ui.setupUi(this);
}

QCameraWidget::~QCameraWidget()
{
	m_videoCapture.release();
}

void QCameraWidget::onWrongDetection()
{
	m_lDices.clear();
	m_pLastValidatedDiceSet = nullptr;
	m_bIsWrongDetection = true;
}



void QCameraWidget::_updateWindow()
{
	Mat matDiff;
	
	unique_ptr<Mat> matNewImageCaptured = make_unique<Mat>();

	m_videoCapture >> *matNewImageCaptured;
	
	m_ui.label->setPixmap(QPixmap::fromImage(
		QImage(matNewImageCaptured->data, matNewImageCaptured->cols, matNewImageCaptured->rows, QImage::Format_RGB888)
	));
	m_ui.label->resize(m_ui.label->pixmap()->size());

	// Passage de l'image en niveau de gris
	cvtColor(*matNewImageCaptured, *matNewImageCaptured, COLOR_BGR2GRAY);
	// Redimensionnement
	cv::resize(*matNewImageCaptured, *matNewImageCaptured, Size(640, 480));

	// Suppression du bruit
	blur(*matNewImageCaptured, *matNewImageCaptured, DEFAULT_KERNEL);
	
	// On r�cup�re l'image
	bool bNotify = true;
	if (m_matImageCaptured != nullptr)
	{
		absdiff(*m_matImageCaptured, *matNewImageCaptured, matDiff);
		const int iImgSize = matDiff.rows * matDiff.cols;
		const float fSimilarity = ((static_cast<double>(iImgSize - countNonZero(matDiff)) / iImgSize) * 100);
		
		if (fSimilarity < 40)
			bNotify = false;
	}

	m_matImageCaptured = std::move(matNewImageCaptured);

	if (bNotify)
	{
		emit cameraImgUpdated();
	}
}

void QCameraWidget::_findDices()
{
	list<shared_ptr<CDice>> lDetectedDices;

	size_t nDotsDetectedByMinArea = 0;
	size_t nDotsDetectedByBlob = 0;

	if (m_bThreadsEnabled)
	{
		m_lThreads.push_back(make_unique<std::thread>(&QCameraWidget::_findDicesByMinArea, this, ref(lDetectedDices), ref(nDotsDetectedByMinArea)));
		m_lThreads.push_back(make_unique<std::thread>(&QCameraWidget::_findDicesByBlob, this, ref(nDotsDetectedByBlob)));

		for (unique_ptr<std::thread>& thread : m_lThreads)
			thread->join();

		m_lThreads.clear();
	}
	else
	{
		_findDicesByMinArea(lDetectedDices, nDotsDetectedByMinArea);
		_findDicesByBlob(nDotsDetectedByBlob);
	}
	
	// On regarde si les deux algorithmes comptent le m�me total 
	if (nDotsDetectedByMinArea == nDotsDetectedByBlob)
	{
		if (m_lDices.size() == 0)
		{
			for (shared_ptr<CDice> dice : lDetectedDices)
				m_lDicesBuffer.push_back(dice);
		}
		else
		{
			bool bProcess = true;
			// On regarde les similitudes entre les d�s d�j� enregistr�s et ceux venant d'�tre d�t�ct�s
			for (auto itDetectedDices = lDetectedDices.begin(); itDetectedDices != lDetectedDices.end(); ++itDetectedDices)
			{
				// Si le d� est un faux positif on passe
				if (((*itDetectedDices)->getCount() == 0)
					|| (*itDetectedDices)->getCount() > 6)
					continue;
				
				for (auto itDice = m_lDices.begin(); itDice != m_lDices.end(); ++itDice)
				{
					// Si le num�ro est le m�me, on compare la position pour savoir si c'est le m�me d� (avec une marge d'erreur / tol�rance)
					if ((*itDetectedDices)->getCount() == (*itDice)->getCount())
					{
						const float fX = std::abs<float>((*itDetectedDices)->getDiceRect().boundingRect().x - (*itDice)->getDiceRect().boundingRect().x);
						const float fY = std::abs<float>((*itDetectedDices)->getDiceRect().boundingRect().y - (*itDice)->getDiceRect().boundingRect().y);
						
						if (fX <= SAME_POS_TOLERANCE && fY <= SAME_POS_TOLERANCE)
						{
							m_lDicesBuffer.push_back(*itDice);
							bProcess = false;
							break;
						}
						else
							bProcess = true;
					}

				}

				if (bProcess)
					m_lDicesBuffer.push_back(*itDetectedDices);
			}
			
		}
		
		// Si on d�tecte 5 d�s
		if (m_lDicesBuffer.size() == 5)
		{
			m_lDices.clear();
			m_lDices = m_lDicesBuffer;

			// On compte les d�s par capacit�
			shared_ptr<CDiceSet> pDiceSet = make_shared<CDiceSet>();
			for (shared_ptr<CDice>& const dice : m_lDices)
				(*pDiceSet)[dice->getCount()]++;

			// Si on obtient le m�me set de d�s que pr�c�demment, on passe, sinon on �met le signal
			if (m_pLastDiceSet != nullptr && *m_pLastDiceSet == *pDiceSet
				&& (m_pLastValidatedDiceSet == nullptr || *pDiceSet != *m_pLastValidatedDiceSet))
			{
				m_pLastValidatedDiceSet = pDiceSet;

				if (m_bIsWrongDetection)
					QMessageBox::information(this, QString::fromLatin1("Red�tection termin�e"), QString::fromLatin1("D�s mis � jour"));

				emit dicesUpdated(*pDiceSet, m_bIsWrongDetection);

				m_bIsWrongDetection = false;
			}
			else
				m_pLastDiceSet = pDiceSet;
			
		}
		
		m_lDicesBuffer.clear();
	}
}

void QCameraWidget::_findDicesByMinArea(list<shared_ptr<CDice>>& lDetectedDices, size_t& iNDetectedDices) const
{
	iNDetectedDices = 0;

	Mat matImageBuffer;
	
	// Filtre de Canny afin d'extraire les contours
	Canny(*m_matImageCaptured, matImageBuffer, MIN_CANNY_THRESHOLD, MAX_CANNY_THRESHOLD);
	
	// Extraction des contours et de la hierarchie
	vector<vector<Point>> vContours;
	vector<Vec4i> vHierarchy;
	findContours(matImageBuffer, vContours, vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	// On veut d�terminer les rectangles qui sont contours des d�s
	for (vector<Point>& contour : vContours)
	{
		// Pour chaque contour, on cherche l'aire minimum du triangle
		RotatedRect rect = minAreaRect(contour);
		
		// On traite uniquement les rectangles qui n'ont pas des angles droits parfaits
		// L'aire d�pend de la r�solution de la webcam
		const float fAspect = fabs(rect.size.aspectRatio() - 1);
		if ((fAspect < 0.25) && (rect.size.area() > MIN_DICE_WIDTH) && (rect.size.area() < MAX_DICE_WIDTH))
		{
			// On v�rifie le rectangle ou un rectangle proche n'a pas d�j� �t� assign�
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
				lDetectedDices.push_back(make_shared<CDice>(rect));
		}
	}

	
	// On compte les points de chaque d�
	for (shared_ptr<CDice>& dice : lDetectedDices)
	{
		// Extraction du d�s de l'image
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
				
				for (const RotatedRect& dotRect : dice->getDotRects())
				{
					float dist = norm(rect.center - dotRect.center);
					if (dist < MIN_DISTANCE_FROM_DICE_CENTER)
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

void QCameraWidget::_findDicesByBlob(size_t& iNDetectedDices) const
{
	iNDetectedDices = 0;
	
	Mat matImageBuffer;

	SimpleBlobDetector::Params detectorParams;
	detectorParams.filterByArea = true;
	detectorParams.filterByCircularity = true;
	detectorParams.filterByInertia = true;
	detectorParams.minThreshold = MIN_BLOB_THRESHOLD;
	detectorParams.maxThreshold = MAX_BLOB_THRESHOLD;
	detectorParams.minArea = MIN_AREA;
	detectorParams.maxArea = MAX_AREA;
	detectorParams.minCircularity = MIN_CIRCULARITY;
	detectorParams.minInertiaRatio = MIN_INERTIA_RATIO;

	const Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(detectorParams);

	std::vector<KeyPoint> vKeypoints;
	detector->detect(*m_matImageCaptured, vKeypoints);

	iNDetectedDices = vKeypoints.size();
}
