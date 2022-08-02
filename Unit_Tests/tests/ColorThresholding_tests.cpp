#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"


namespace ColorThresholdingTests
{
	TEST_CASE("BGR color thresholding", "[BGRThresholding]")
	{
		SECTION("Single channel")
		{
			ColorRange colorRange(20, 50);
			uchar arr[2][2][1] = { {10, 30}, {20, 50} };
			auto mat = cv::Mat(2, 2, CV_8UC1, &arr);
			auto newMat = thresholdByHSV(mat, { colorRange });
			auto newMatData = newMat.data;

			CHECK(newMatData[0] == 0);
			CHECK(newMatData[1] == 255);
			CHECK(newMatData[2] == 255);
			CHECK(newMatData[3] == 255);
		}

		SECTION("Three channels")
		{
			std::vector<ColorRange> colorRanges = { ColorRange(10, 20), ColorRange(30, 40), ColorRange(50, 60) };
			uchar arr[2][2][3] = { { {10, 30, 50}, {5, 5, 5} }, { {5, 30, 50}, {5, 5, 50} } };
			auto mat = cv::Mat(2, 2, CV_8UC3, &arr);
			auto newMat = thresholdByHSV(mat, colorRanges);
			auto newMatData = newMat.data;

			CHECK(newMatData[0] == 255);
			CHECK(newMatData[1] == 0);
			CHECK(newMatData[2] == 0);
			CHECK(newMatData[3] == 0);
		}
	}
}