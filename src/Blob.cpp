#include "Blob.h"

void Blob::addPoint(const cv::Point2i& point)
{
	checkIfBoundaryChanged(point.x, point.y);
	points.emplace_back(point);
}

void Blob::addPoint(const cv::Point2i&& point)
{
	checkIfBoundaryChanged(point.x, point.y);
	points.emplace_back(std::move(point));
}

void Blob::checkIfBoundaryChanged(int x, int y)
{
	if (x < topLeftCorner.x)
	{
		topLeftCorner.x = x;
	}
	if (y < topLeftCorner.y)
	{
		topLeftCorner.y = y;
	}
	if (x > bottomRightCorner.x)
	{
		bottomRightCorner.x = x;
	}
	if (y > bottomRightCorner.y)
	{
		bottomRightCorner.y = y;
	}
}
