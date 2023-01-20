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
		if (inMat.channels() == 3)
		{
			cv::rectangle(inMat, rect, cv::Scalar(0, 255, 255), 5);
		}
		else if (inMat.channels() == 1)
		{
			cv::rectangle(inMat, rect, cv::Scalar(120), 5);
		}
	}

	std::pair<cv::Point2i, cv::Point2i> Blob::getCorners() const
	{
		return std::make_pair(topLeftCorner, bottomRightCorner);
	}

	cv::Point2i Blob::getCenter() const
	{
		auto centerX = (topLeftCorner.x + bottomRightCorner.x) / 2;
		auto centerY = (topLeftCorner.y + bottomRightCorner.y) / 2;
		return cv::Point2i{ centerX, centerY };
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

	bool Blob::isInSizeRange(const std::size_t& min, const std::size_t& max) const
	{
		auto pointsCount = points.size();
		return pointsCount >= min && pointsCount <= max;
	}

	bool Blob::isInEdgeRatio(const double min, const double max) const
	{
		auto lenghtA = bottomRightCorner.x - topLeftCorner.x;
		auto lenghtB = bottomRightCorner.y - topLeftCorner.y;

		auto ratio = static_cast<double>(lenghtA) / static_cast<double>(lenghtB);
		if (ratio >= 1)
		{
			ratio = 1.0 / ratio;
		}
		return ratio >= min && ratio <= max;
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