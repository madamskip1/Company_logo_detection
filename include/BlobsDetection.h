#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Blob.h"

std::vector<Blob> detectBlobs(cv::Mat inMat);