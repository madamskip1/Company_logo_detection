#pragma once
#include <opencv2/core/mat.hpp>
namespace POBR
{
	cv::Mat filterMedian(const cv::Mat& inMat, const int kernelSize);
}