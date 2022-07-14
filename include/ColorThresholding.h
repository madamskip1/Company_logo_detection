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

class ColorThresholding
{
public:
	cv::Mat threshold(cv::Mat& inMat, const std::vector<ColorRange>& colorRanges);
	//const ColorRange& channel1Range, const ColorRange& channel2Range, const ColorRange& channel3Range);

private:
	bool checkIfColorInRange(uchar color, const ColorRange& colorRange);
};

