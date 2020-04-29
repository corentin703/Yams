#ifndef QCAMERAWIDGET_H
#define QCAMERAWIDGET_H

#pragma once

// STL
#include <list>
#include <cmath>
#include <memory>
#include <thread>
#include <vector>

// Qt
#include <QTimer>
#include <QtDebug>

// OpenCV
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


#include "..\models\CDice.hpp"

// UI
#include "ui_QCameraWidget.h"

class QCameraWidget : public QWidget
{
	Q_OBJECT

private:
	const unsigned int MIN_DICE_WIDTH = 1000;
	const unsigned int MAX_DICE_WIDTH = 6000;
	const unsigned int MIN_DICE_DOT_WIDTH = 8;
	const unsigned int MAX_DICE_DOT_WIDTH = 300;
	const cv::Size DEFAULT_KERNEL = cv::Size(3, 3);

	const unsigned int MIN_THRESHOLD = 170;
	const unsigned int MAX_THRESHOLD = 255;
	const unsigned int MIN_AREA = 10;
	const float MIN_CIRCULARITY = 0.3;
	const float MIN_INERTIA_RATIO = 0.5;

	const float SAME_POS_TOLERANCE = 10;


	Ui::QCameraWidget m_ui;

	cv::VideoCapture m_videoCapture;
	cv::Mat m_matImageCaptured;

	QTimer m_qTimer;
	
	std::list<std::shared_ptr<CDice>> m_lDices;
	std::list<std::shared_ptr<CDice>> m_lDicesBuffer;

	bool m_bThreadsEnabled = false;
	std::list<std::unique_ptr<std::thread>> m_lThreads;

public:
	QCameraWidget(QWidget* parent = Q_NULLPTR);
	~QCameraWidget();

	std::list< std::shared_ptr<CDice>> getDices() { return m_lDices; };

private:
	void _updateWindow();

	void _findDicesByMinArea(std::list<std::shared_ptr<CDice>>& lDetectedDices, size_t& iNDetectedDices);
	void _findDicesByBlob(size_t& iNDetectedDices);
	void _debug(int iNDicesDetectedByMinArea, int iNDicesDetectedByBlob);

private slots: 
	void _findDices();

signals:
	void cameraImgUpdated();
};

#endif // QCAMERAWIDGET_H
