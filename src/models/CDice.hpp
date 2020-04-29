#ifndef CDICE_H
#define CDICE_H

#pragma once

// STL
#include <list>

// OpenCV
#include <opencv2/imgproc.hpp>

class CDice
{

private: 

	cv::RotatedRect m_diceRect;
	std::list<cv::RotatedRect> m_lDotRects;

public:
	CDice(cv::RotatedRect& const diceRect);
	~CDice();

	cv::RotatedRect& const getDiceRect() { return m_diceRect; }
	void setDiceRect(cv::RotatedRect& const diceRect) { m_diceRect = diceRect; }

	std::list<cv::RotatedRect>& const getDotRects() { return m_lDotRects; }
	void addDotRect(cv::RotatedRect& const dotRect) { m_lDotRects.push_back(dotRect); }
	unsigned int getCount() { return m_lDotRects.size(); }

};

#endif // CDICE_H
