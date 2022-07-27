#pragma once
#include <opencv2/opencv.hpp>

cv::Mat erode(const cv::Mat& inMat, const int size);
cv::Mat dilate(const cv::Mat& inMat, const int size);