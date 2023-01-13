#pragma once
#include <vector>
#include <opencv2/core/mat.hpp>
#include "Blob.h"

namespace POBR
{
	class Blobs
	{
	public:
		void addBlob(const Blob& blob);
		void filterBlobsBySize(const std::size_t size);

		void draw(cv::Mat& mat) const;
		const std::vector<POBR::Blob>& getBlobs() const;

	private:
		std::vector<POBR::Blob> blobs;
	};
}