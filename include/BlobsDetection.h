#pragma once
#include <opencv2/opencv.hpp>
#include "Blobs.h"

namespace POBR
{
	POBR::Blobs detectBlobs(cv::Mat inMat);
}
