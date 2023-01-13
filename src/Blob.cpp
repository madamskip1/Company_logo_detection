#include "Blob.h"

#include "HuMoments.h"

namespace POBR
{
	void Blob::addPoint(const cv::Point2i& point)
	{
		checkIfBoundaryChanged(point.x, point.y);
		points.emplace_back(point);
	}

	void Blob::draw(cv::Mat& inMat) const
	{
		auto rect = cv::Rect(topLeftCorner, bottomRightCorner);
		cv::rectangle(inMat, rect, cv::Scalar(255, 0, 0));
	}

	std::pair<cv::Point2i, cv::Point2i> Blob::getCorners() const
	{
		return std::make_pair(topLeftCorner, bottomRightCorner);
	}

	std::size_t Blob::countPoints() const
	{
		return points.size();
	}

	bool Blob::isInHuMomentsRange(const HuMoments& minHuMoments, const HuMoments& maxHuMoments) const
	{
		auto huMoments = HuMoments::calcHuMoments(*this);
		return huMoments.isInRange(minHuMoments, maxHuMoments);
	}

	POBR::Blob Blob::createBlobFromFew(const std::vector<Blob>& blobs)
	{
		auto newBlob = POBR::Blob{};

		for (const auto& blob : blobs)
		{
			auto points = blob.getPoints();
			for (const auto& point : points)
			{
				newBlob.addPoint(point);
			}
		}
		return newBlob;
	}

	const std::vector<cv::Point2i>& Blob::getPoints() const
	{
		return points;
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
}