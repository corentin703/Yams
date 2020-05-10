#include "QAboutWidget.hpp"

QAboutWidget::QAboutWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ui.setupUi(this);

	connect(m_ui.btnAboutQt, &QPushButton::clicked, this, &QAboutWidget::showAboutQtWindow);
	connect(m_ui.btnAboutOpenCV, &QPushButton::clicked, this, &QAboutWidget::showAboutOpenCVWindow);

	connect(m_ui.lblCEGEP, &QLabel::linkActivated, [this]()
	{
		QDesktopServices::openUrl(QUrl("https://cegepsi.ca", QUrl::TolerantMode));
	});
}

void QAboutWidget::showAboutQtWindow()
{
	QMessageBox::aboutQt(this);
}

void QAboutWidget::showAboutOpenCVWindow()
{
	const QString cvVersion = QString::fromLatin1(cv::getVersionString().c_str());

	QMessageBox aboutOpenCV;
	aboutOpenCV.setIconPixmap(QPixmap(":/about/logo_open_cv"));
	aboutOpenCV.setWindowIcon(QPixmap(":/about/logo_open_cv"));
	aboutOpenCV.setWindowTitle("About OpenCV");
	aboutOpenCV.setText("<h3>About OpenCV</h3>");
	aboutOpenCV.setInformativeText(
		"<p>This program uses OpenCV version " + cvVersion + "</p>"
		"<p>OpenCV (Open Source Computer Vision Library) "
		"is an open source computer vision and machine learning software library. "
		"OpenCV was built to provide a common infrastructure for computer vision "
		"applications and to accelerate the use of machine perception in the commercial products. "
		"Being a BSD-licensed product, "
		"OpenCV makes it easy for businesses to utilize and modify the code.</p>"
		"See <a href='https://opencv.org'>opencv.org</a>"
	);

	aboutOpenCV.exec();
}

