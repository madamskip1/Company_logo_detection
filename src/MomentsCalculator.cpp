#include "MomentsCalculator.h"
#include <limits>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream> 
#include <ctime>
#include <opencv2/opencv.hpp>
#include "MorphologyOperations.h"
#include "BlobsDetection.h"
#include "HuMoments.h"

void calcMomentsRange(std::string imageName)
{
	auto img = cv::imread(imageName, cv::IMREAD_GRAYSCALE);
	auto imgCopy = img.clone();
	auto rows = img.rows;
	auto cols = img.cols;
	auto blobs = POBR::detectBlobs(imgCopy);
	blobs.filterBySize(20, 10000000);
	auto blobsVector = blobs.getBlobs();

	auto hu_values = std::vector<std::vector<double>>(10, std::vector<double>{});
	auto momentsCounter = std::size_t{ 0 };

	std::for_each(hu_values.begin(), hu_values.end(), [&blobsVector](auto& v) { v.reserve(blobsVector.size()); });

	auto blobID{ 0 };

	for (const auto& blob : blobsVector)
	{
		auto blobCorners = blob.getCorners();
		auto startRow = std::clamp(blobCorners.first.y - 1, 0, rows);
		auto endRow = std::clamp(blobCorners.second.y + 1, 0, rows);
		auto startCol = std::clamp(blobCorners.first.x - 1, 0, cols);
		auto endCol = std::clamp(blobCorners.second.x + 1, 0, cols);

		cv::Mat cropped = img(cv::Range(startRow, endRow), cv::Range(startCol, endCol));
		cv::imwrite("img/moments_logo/blue_blobs/" + std::to_string(blobID) + ".jpg", cropped);

		++blobID;
		startRow++;
		endRow++;
		startCol++;
		endCol++;
		++momentsCounter;
		auto huMoments = POBR::HuMoments::calcHuMoments(blob);
		auto huMomentsValues = huMoments.getHuValues();

		for (std::size_t i = 0; i < huMomentsValues.size(); ++i)
		{
			hu_values[i].push_back(huMomentsValues[i]);
		}
	}
	writeMomentsToFile(hu_values);

	auto minHuValues = std::vector<double>(10, std::numeric_limits<double>::max());
	auto maxHuValues = std::vector<double>(10, 0);
	auto avgHuValues = std::vector<double>(10, 0);
	auto stdHuValues = std::vector<double>(10, 0);
	auto medianHuValues = std::vector<double>(10, 0);

	for (std::size_t i = 0; i < 10; ++i)
	{
		const auto& hu_i_values{ hu_values[i] };
		auto minHuValue{ minHuValues[i] };
		auto maxHuValue{ maxHuValues[i] };
		auto avgHuValue{ avgHuValues[i] };
		

		for (std::size_t j = 0; j < momentsCounter; ++j)
		{
			minHuValue = std::min(minHuValue, hu_i_values[j]);
			minHuValues[i] = minHuValue;
			maxHuValue = std::max(maxHuValue, hu_i_values[j]);
			maxHuValues[i] = maxHuValue;
			avgHuValue += hu_i_values[j];
		}


		avgHuValue /= momentsCounter;
	}

	stdHuValues = calcSTDs(hu_values, avgHuValues);
	medianHuValues = calcMedians(hu_values);

	printMomentsInfo(minHuValues, maxHuValues, avgHuValues, stdHuValues, medianHuValues);
}

std::vector<double> calcMedians(std::vector<std::vector<double>>& hu_values)
{
	auto medians{ std::vector<double>{} };
	medians.reserve(hu_values.size());
	auto momentsCounter{ hu_values[0].size()};

	for (auto& moments : hu_values)
	{
		std::sort(moments.begin(), moments.end());
		auto median = (moments.size() % 2 != 0 ? moments[momentsCounter / 2] : (moments[momentsCounter / 2] + moments[momentsCounter / 2 + 1]) / 2);
		medians.push_back(median);
	}

	return medians;
}

std::vector<double> calcSTDs(std::vector<std::vector<double>>& hu_values, std::vector<double>& avgMomentsValue)
{
	auto STDs{ std::vector<double>{} };
	STDs.reserve(hu_values.size());
	auto momentsCounter{ hu_values[0].size() };

	for (std::size_t i = 0; i < 10; ++i)
	{
		auto std{ 0.0 };
		const auto& avgHuValue{ avgMomentsValue[i] };
		const auto& hu_i_values{ hu_values[i] };

		for (std::size_t j = 0; j < momentsCounter; ++j)
		{
			auto distToMean = hu_i_values[j] - avgHuValue;
			std += std::pow(distToMean, 2.0);
		}

		std /= momentsCounter;
		std = std::sqrt(std);

		STDs.push_back(std);
	}

	return STDs;
}

void printMomentsInfo(std::vector<double>& minHuValues, std::vector<double>& maxHuValues, std::vector<double>& avgHuValues, std::vector<double>& stdHuValues, std::vector<double>& medianHuValues)
{
	for (std::size_t i = 0; i < 10; ++i)
	{
		auto delta = maxHuValues[i] - minHuValues[i];
		std::cout << "Hu_" << i << ": <" << minHuValues[i] << ", " << maxHuValues[i] << ">, delta: " << delta << ", avg: " << avgHuValues[i] << ", std: " << stdHuValues[i] << ", median: " << medianHuValues[i] << " \n";
	}
}

void writeMomentsToFile(std::vector<std::vector<double>>& hu_values)
{
	// name of file to be datetime
	std::ofstream outfile("test.txt");
	auto momentsCounter{ hu_values[0].size() };

	for (std::size_t i = 0; i < momentsCounter; ++i)
	{
		outfile << i << ";";
		for (std::size_t j = 0; j < 10; ++j)
		{
			outfile << hu_values[j][i];
			if (j != 9)
			{
				outfile << ";";
			}
		}
		outfile << '\n';
	}
	outfile << std::endl;
	outfile.close();
}
