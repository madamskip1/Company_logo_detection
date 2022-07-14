#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "MorphologyOperations.h"

namespace MorphologyOperationsTests
{
	MorphologyOperations morph;

	TEST_CASE("Erosion", "[erode]")
	{
		uchar arr[5][5][1] =
		{
			{0, 0, 0, 255, 255},
			{0, 0, 0, 0, 255},
			{0, 0, 255, 255, 255},
			{255, 0, 255, 255, 255},
			{0, 0, 255, 255, 255}
		};
		auto mat = cv::Mat(5, 5, CV_8UC1, &arr);
		auto newMat = morph.erode(mat, 3);
		auto newMatData = newMat.data;

		CHECK(newMatData[0] == 0);
		CHECK(newMatData[1] == 0);
		CHECK(newMatData[2] == 0);
		CHECK(newMatData[3] == 0);
		CHECK(newMatData[4] == 0);

		CHECK(newMatData[5] == 0);
		CHECK(newMatData[6] == 0);
		CHECK(newMatData[7] == 0);
		CHECK(newMatData[8] == 0);
		CHECK(newMatData[9] == 0);

		CHECK(newMatData[10] == 0);
		CHECK(newMatData[11] == 0);
		CHECK(newMatData[12] == 0);
		CHECK(newMatData[13] == 0);
		CHECK(newMatData[14] == 0);

		CHECK(newMatData[15] == 0);
		CHECK(newMatData[16] == 0);
		CHECK(newMatData[17] == 0);
		CHECK(newMatData[18] == 255);
		CHECK(newMatData[19] == 255);

		CHECK(newMatData[20] == 0);
		CHECK(newMatData[21] == 0);
		CHECK(newMatData[22] == 0);
		CHECK(newMatData[23] == 255);
		CHECK(newMatData[24] == 255);
	}

	TEST_CASE("Dilation", "[dilate]")
	{
		uchar arr[5][5][1] =
		{
			{0, 0, 0, 255, 255},
			{0, 0, 0, 0, 255},
			{0, 0, 0, 255, 255},
			{255, 0, 255, 255, 255},
			{0, 0, 255, 255, 255}
		};
		auto mat = cv::Mat(5, 5, CV_8UC1, &arr);
		auto newMat = morph.dilate(mat, 3);
		auto newMatData = newMat.data;

		CHECK(newMatData[0] == 0);
		CHECK(newMatData[1] == 0);
		CHECK(newMatData[2] == 255);
		CHECK(newMatData[3] == 255);
		CHECK(newMatData[4] == 255);

		CHECK(newMatData[5] == 0);
		CHECK(newMatData[6] == 0);
		CHECK(newMatData[7] == 255);
		CHECK(newMatData[8] == 255);
		CHECK(newMatData[9] == 255);

		CHECK(newMatData[10] == 255);
		CHECK(newMatData[11] == 255);
		CHECK(newMatData[12] == 255);
		CHECK(newMatData[13] == 255);
		CHECK(newMatData[14] == 255);

		CHECK(newMatData[15] == 255);
		CHECK(newMatData[16] == 255);
		CHECK(newMatData[17] == 255);
		CHECK(newMatData[18] == 255);
		CHECK(newMatData[19] == 255);

		CHECK(newMatData[20] == 255);
		CHECK(newMatData[21] == 255);
		CHECK(newMatData[22] == 255);
		CHECK(newMatData[23] == 255);
		CHECK(newMatData[24] == 255);
	}
}