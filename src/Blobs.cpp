#include "Blobs.h"

void POBR::Blobs::addBlob(const Blob& blob)
{
	blobs.push_back(blob);
}

void POBR::Blobs::filterBlobsBySize(const std::size_t size)
{
	// TODO
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
