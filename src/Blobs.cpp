#include "Blobs.h"
#include <algorithm>

void POBR::Blobs::addBlob(const Blob& blob)
{
	blobs.push_back(blob);
}

void POBR::Blobs::filterBlobsBySize(const std::size_t& size)
{
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&size](const POBR::Blob& blob) {
			return (blob.countPoints() < size);
		}), blobs.end());
}

void POBR::Blobs::filterBlobsByHuMoments(const POBR::HuMoments& huMin, const POBR::HuMoments& huMax)
{
	std::cout << blobs.size() << std::endl;
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&huMin, &huMax](const POBR::Blob& blob) {
			auto x =  blob.isInHuMomentsRange(huMin, huMax);
			std::cout << x << std::endl;
			return !x;
		}), blobs.end());
	std::cout << blobs.size() << std::endl;
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
