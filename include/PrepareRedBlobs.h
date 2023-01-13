#pragma once
#include <vector>
#include "Blob.h"

namespace POBR
{
	std::vector<POBR::Blob> prepareRedBlobs(cv::Mat& hsvMat);
}