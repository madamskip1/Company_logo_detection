#pragma once
#include <opencv2/core/mat.hpp>

namespace POBR
{
	cv::Mat filterImage(const cv::Mat& inMat, const cv::Mat& kernel);
}