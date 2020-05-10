#ifndef C_DICE_H
#define C_DICE_H

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
	CDice(const cv::RotatedRect& diceRect);

	const cv::RotatedRect& getDiceRect() const { return m_diceRect; }
	void setDiceRect(const cv::RotatedRect& diceRect) { m_diceRect = diceRect; }

	const std::list<cv::RotatedRect>& getDotRects() const { return m_lDotRects; }
	void addDotRect(const cv::RotatedRect& dotRect) { m_lDotRects.push_back(dotRect); }
	uint getCount() const { return m_lDotRects.size(); }

};

#endif // C_DICE_H
