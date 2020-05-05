#include "CDice.hpp"

CDice::CDice(const cv::RotatedRect& diceRect)
{
	m_diceRect = diceRect;
}

CDice::~CDice()
{

}