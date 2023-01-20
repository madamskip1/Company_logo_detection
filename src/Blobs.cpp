#include "Blobs.h"
#include <algorithm>

void POBR::Blobs::addBlob(const Blob& blob)
{
	blobs.push_back(blob);
}

void POBR::Blobs::filterBySize(const std::size_t& minSize, const std::size_t& maxSize)
{
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&minSize, &maxSize](const POBR::Blob& blob) {
			auto isInRange = blob.isInSizeRange(minSize, maxSize);
			auto blobSize{ blob.countPoints() };
			return !isInRange;
		}), blobs.end());
}

void POBR::Blobs::filterByHuMoments(const POBR::HuMoments& huMin, const POBR::HuMoments& huMax)
{
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&huMin, &huMax](const POBR::Blob& blob) {
			auto isInRange =  blob.isInHuMomentsRange(huMin, huMax);
			return !isInRange;
		}), blobs.end());
}

void POBR::Blobs::filterByEdgeRatio(const double minRatio, const double maxRatio)
{
	blobs.erase(std::remove_if(blobs.begin(), blobs.end(), [&minRatio, &maxRatio](const POBR::Blob& blob) {
		auto isInRange = blob.isInEdgeRatio(minRatio, maxRatio);
		return !isInRange;
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
