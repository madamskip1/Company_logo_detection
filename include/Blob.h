#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class Blob
{
public:
	void addPoint(const cv::Point2i& point);

	void draw(cv::Mat& inMat);

private:
	cv::Point2i topLeftCorner{ INT_MAX, INT_MAX };
	cv::Point2i bottomRightCorner{ 0, 0 };

	std::vector<cv::Point2i> points;

	void checkIfBoundaryChanged(int x, int y);
};

