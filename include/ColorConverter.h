#pragma once
#include <opencv2/opencv.hpp>

class ColorConverter
{
public:
	cv::Mat convertBGRToRGB(const cv::Mat& in_mat);
};

