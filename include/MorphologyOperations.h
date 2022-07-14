#pragma once
#include <opencv2/opencv.hpp>

class MorphologyOperations
{
public:
	cv::Mat erode(const cv::Mat& inMat, const int size);
	cv::Mat dilate(const cv::Mat& inMat, const int size);

private:
	cv::Mat morph(const cv::Mat& inMat, const int size, const int kernelValue);
};

