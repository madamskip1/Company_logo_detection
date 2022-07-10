#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "ColorConverter.h"


namespace ColorConverterTests
{
	TEST_CASE("BGR to RGB conversion", "[BGRtoRGB]")
	{
		ColorConverter colorConverter;

		SECTION("one pixel")
		{
			uchar arr[1][1][3] = { { {50, 100, 150} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = colorConverter.convertBGRToRGB(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 150);
			REQUIRE(newMatData[1] == 100);
			REQUIRE(newMatData[2] == 50);
		}

		SECTION("Multi-dimension mat")
		{
			uchar arr[2][2][3] =
			{
				{ {0, 1, 2}, {3, 4, 5} },
				{ {6, 7, 8}, {9, 10, 11} }
			};
			auto mat = cv::Mat(2, 2, CV_8UC3, &arr);
			auto newMat = colorConverter.convertBGRToRGB(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 2);
			REQUIRE(newMatData[1] == 1);
			REQUIRE(newMatData[2] == 0);

			REQUIRE(newMatData[3] == 5);
			REQUIRE(newMatData[4] == 4);
			REQUIRE(newMatData[5] == 3);

			REQUIRE(newMatData[6] == 8);
			REQUIRE(newMatData[7] == 7);
			REQUIRE(newMatData[8] == 6);

			REQUIRE(newMatData[9] == 11);
			REQUIRE(newMatData[10] == 10);
			REQUIRE(newMatData[11] == 9);
		}
	}
}