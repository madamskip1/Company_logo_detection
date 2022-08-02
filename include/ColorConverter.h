#pragma once
#include <opencv2/opencv.hpp>

namespace POBR
{
	cv::Mat convertBGRToHSV(const cv::Mat& inMat);
}