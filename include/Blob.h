#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class Blob
{
public:
	void addPoint(const cv::Point2i& point);
	void addPoint(const cv::Point2i&& point);

private:
	cv::Point2i topLeftCorner;
	cv::Point2i bottomRightCorner;

	std::vector<cv::Point2i> points;

	void checkIfBoundaryChanged(int x, int y);
};

