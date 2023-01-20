#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
#include "Blob.h"
#include "HuMoments.h"

namespace POBR
{
	class Blobs
	{
	public:
		void addBlob(const Blob& blob);
		void filterBySize(const std::size_t& minSize, const std::size_t& maxSize);
		void filterByHuMoments(const POBR::HuMoments& huMin, const POBR::HuMoments& huMax);
		void filterByEdgeRatio(const double minRatio, const double maxRatio);

		void draw(cv::Mat& mat) const;
		const std::vector<POBR::Blob>& getBlobs() const;

	private:
		std::vector<POBR::Blob> blobs;
	};
}