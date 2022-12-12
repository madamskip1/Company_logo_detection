#include "MomentsCalculator.h"
#include <limits>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "MorphologyOperations.h"
#include "BlobsDetection.h"
#include "HuMoments.h"

void calcMumentsRange(std::string imageName)
{
	auto img = cv::imread(imageName, cv::IMREAD_GRAYSCALE);
	auto morphed = POBR::dilate(img, 1);
	auto blobs = POBR::detectBlobs(morphed);

	for (auto& blob : blobs)
	{
		blob.draw(img);
	}
	cv::imshow("test2", img);
	//auto minHuMoments = POBR::HuMoments{double_max, double_max, double_max, double_max, double_max, double_max, double_max, double_max, double_max, double_max};
	//auto maxHuMoments = POBR::HuMoments{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	auto minHuValues = std::vector<double>(10, std::numeric_limits<double>::max());
	auto maxHuValues = std::vector<double>(10, 0);

	for (const auto& blob : blobs)
	{
		auto huMoments = POBR::HuMoments::calcHuMoments(blob);
		auto huMomentsValue = huMoments.getHuValues();
		for (std::size_t i = 0; i < huMomentsValue.size(); ++i)
		{
			minHuValues[i] = std::min(minHuValues[i], huMomentsValue[i]);
			maxHuValues[i] = std::max(maxHuValues[i], huMomentsValue[i]);
		}
	}

	for (std::size_t i = 0; i < minHuValues.size(); ++i)
	{
		auto delta = maxHuValues[i] - minHuValues[i];
		std::cout << "Hu_" << i << ": <" << minHuValues[i] << ", " << maxHuValues[i] << ">, delta: " << delta << " \n";
	}
}
