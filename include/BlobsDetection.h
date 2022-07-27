#pragma once
#include <opencv2/opencv.hpp>
#include <queue>
#include <vector>
#include "Blob.h"

std::vector<Blob> detectBlobs(cv::Mat inMat);

inline void addPixelNeighborsToCheck(const cv::Point2i pixel, std::queue<cv::Point2i>& pixelsToCheck, cv::Mat& inMat);