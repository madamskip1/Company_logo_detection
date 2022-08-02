#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

struct ColorRange
{
	uchar min;
	uchar max;

	ColorRange(uchar min, uchar max) : min{ min }, max{ max } {};
	ColorRange(int min, int max) : min{ (uchar)min }, max{ (uchar)max } {};
};

cv::Mat thresholdByHSV(cv::Mat& inMat, const std::vector<ColorRange>& colorRanges);