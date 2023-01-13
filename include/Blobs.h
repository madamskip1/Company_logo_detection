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
		void filterBlobsBySize(const std::size_t& size);
		void filterBlobsByHuMoments(const POBR::HuMoments& huMin, const POBR::HuMoments& huMax);

		void draw(cv::Mat& mat) const;
		const std::vector<POBR::Blob>& getBlobs() const;

	private:
		std::vector<POBR::Blob> blobs;
	};
}