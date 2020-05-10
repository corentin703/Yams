#ifndef Q_CAMERAWIDGET_H
#define Q_CAMERAWIDGET_H

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
#include <QMessageBox>

// OpenCV
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>


#include "../models/CDice.hpp"
#include "../models/CDiceSet.hpp"

// UI
#include "ui_QCameraWidget.h"

class QCameraWidget : public QWidget
{
	Q_OBJECT

private:
	const uint MIN_DICE_WIDTH = 1000;
	const uint MAX_DICE_WIDTH = 4000;
	const uint MIN_DICE_DOT_WIDTH = 10;
	const uint MAX_DICE_DOT_WIDTH = 200;
	const cv::Size DEFAULT_KERNEL = cv::Size(3, 3);

	const uint MIN_CANNY_THRESHOLD = 210;
	const uint MAX_CANNY_THRESHOLD = 255;
	const uint MIN_DISTANCE_FROM_DICE_CENTER = 7;

	const uint MIN_BLOB_THRESHOLD = 100;
	const uint MAX_BLOB_THRESHOLD = 255;
	const uint MIN_AREA = 5;
	const uint MAX_AREA = 200;
	const float MIN_CIRCULARITY = 0.3;
	const float MIN_INERTIA_RATIO = 0.5;

	const float SAME_POS_TOLERANCE = 10;

	Ui::QCameraWidget m_ui;

	cv::VideoCapture m_videoCapture;
	std::unique_ptr<cv::Mat> m_matImageCaptured = nullptr;
	
	QTimer m_qTimerFrame;
	
	std::list<std::shared_ptr<CDice>> m_lDices;
	std::list<std::shared_ptr<CDice>> m_lDicesBuffer;

	std::shared_ptr<CDiceSet> m_pLastDiceSet = nullptr;
	std::shared_ptr<CDiceSet> m_pLastValidatedDiceSet = nullptr;
	bool m_bIsWrongDetection = false;

	bool m_bThreadsEnabled = false;
	std::list<std::unique_ptr<std::thread>> m_lThreads;

public:
	QCameraWidget(QWidget* parent = Q_NULLPTR);
	~QCameraWidget();

public slots:
	void onWrongDetection();
	
private:
	void _updateWindow();

	void _findDicesByMinArea(std::list<std::shared_ptr<CDice>>& lDetectedDices, size_t& iNDetectedDices) const;
	void _findDicesByBlob(size_t& iNDetectedDices) const;

private slots: 
	void _findDices();

signals:
	void cameraImgUpdated();
	void dicesUpdated(CDiceSet& diceSet, bool isDetectionCorrection);
};

#endif // Q_CAMERAWIDGET_H
