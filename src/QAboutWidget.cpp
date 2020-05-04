#include "QAboutWidget.hpp"

QAboutWidget::QAboutWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.btnAboutQt, &QPushButton::clicked, this, &QAboutWidget::showAboutQtWindow);
	connect(m_ui.btnAboutOpenCV, &QPushButton::clicked, this, &QAboutWidget::showAboutOpenCVWindow);

	//connect(this, &QWidget::closeEvent, this, &QAboutWidget::onClose);
}

QAboutWidget::~QAboutWidget()
{
}

void QAboutWidget::showAboutQtWindow()
{
	QMessageBox::aboutQt(this);
}

void QAboutWidget::showAboutOpenCVWindow()
{
	QString cvVersion = QString::fromLatin1(cv::getVersionString().c_str());

	
	QMessageBox aboutOpenCV;
	aboutOpenCV.setIconPixmap(QPixmap(":/about/logo_open_cv"));
	aboutOpenCV.setWindowTitle("About OpenCV");
	aboutOpenCV.setText("<b>About OpenCV");
	aboutOpenCV.setInformativeText(
		"This program uses OpenCV version " + cvVersion + "\n"
		"OpenCV (Open Source Computer Vision Library) "
		"is an open source computer vision and machine learning software library. "
		"OpenCV was built to provide a common infrastructure for computer vision "
		"applications and to accelerate the use of machine perception in the commercial products. "
		"Being a BSD-licensed product, "
		"OpenCV makes it easy for businesses to utilize and modify the code. \n"
		//"See <a href=\"https://opencv.org/\">opencv.org</a>"
		);

	aboutOpenCV.exec();
}

