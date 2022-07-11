#pragma once
#include <opencv2/opencv.hpp>

class ColorConverter
{
public:
	cv::Mat convertBGRToRGB(const cv::Mat& inMat);
	cv::Mat convertBGRToHSV(const cv::Mat& inMat);

private:
	int calcHue(const double& b, const double& g, const double& r, const double& min, const double& max);
	int calcSaturation(const double& min, const double& max);
};

