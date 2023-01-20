#pragma once
#include <vector>
#include <utility>
#include <cstddef>
#include <opencv2/opencv.hpp>

namespace POBR
{
	class HuMoments;

	class Blob
	{
	public:
		void addPoint(const cv::Point2i& point);
		void draw(cv::Mat& inMat) const;
		const std::vector<cv::Point2i>& getPoints() const;
		std::pair<cv::Point2i, cv::Point2i> getCorners() const;
		cv::Point2i getCenter() const;
		std::size_t countPoints() const;

		bool isInHuMomentsRange(const HuMoments& minHuMoments, const HuMoments& maxHuMoments) const;
		bool isInSizeRange(const std::size_t& min, const std::size_t& max) const;
		bool isInEdgeRatio(const double min, const double max) const;

		static POBR::Blob createBlobFromFew(const std::vector<Blob>& blobs);
	private:
		cv::Point2i topLeftCorner{ INT_MAX, INT_MAX };
		cv::Point2i bottomRightCorner{ 0, 0 };

		std::vector<cv::Point2i> points;

		void checkIfBoundaryChanged(int x, int y);
	};
}
