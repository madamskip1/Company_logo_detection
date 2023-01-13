#include "Blobs.h"
#include <algorithm>

void POBR::Blobs::addBlob(const Blob& blob)
{
	blobs.push_back(blob);
}

void POBR::Blobs::filterBlobsBySize(const std::size_t& size)
{
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&size](const auto& blob) {
			return (blob.countPoints() < size);
		}), blobs.end());
}

void POBR::Blobs::draw(cv::Mat& mat) const
{
	for (const auto& blob : blobs)
	{
		blob.draw(mat);
	}
}

const std::vector<POBR::Blob>& POBR::Blobs::getBlobs() const
{
	return blobs;
}
