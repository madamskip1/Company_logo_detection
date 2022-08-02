#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "ColorConverter.h"


namespace ColorConverterTests
{
	TEST_CASE("BGR to HSV, hue", "[BGRtoHSV_value]")
	{
		SECTION("Max == Min")
		{
			uchar arr[1][1][3] = { { {122, 122, 122} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 0);
		}

		SECTION("Max == b")
		{
			uchar arr[1][1][3] = { { {255, 100, 200} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 139);
		}

		SECTION("Max = g")
		{
			uchar arr[1][1][3] = { { {100, 255, 200} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 40);
		}

		SECTION("Max == r")
		{
			uchar arr[1][1][3] = { { {100, 200, 255} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 19);
		}

		SECTION("Hue < 0")
		{
			uchar arr[1][1][3] = { { {200, 100, 255} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 160);
		}
	}

	TEST_CASE("BGR to HSV, saturation", "[BGRtoHSV_saturation]")
	{
		SECTION("Max = 0, Min = 0")
		{
			uchar arr[1][1][3] = { { {0, 0, 0} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[1] == 0);
		}

		SECTION("Max = 255, Min = 0")
		{
			uchar arr[1][1][3] = { { {100, 255, 0} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[1] == 255);
		}

		SECTION("Max = 255, Min = 255")
		{
			uchar arr[1][1][3] = { { {255, 255, 255} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[1] == 0);
		}

		SECTION("Max = 200, Min = 100")
		{
			uchar arr[1][1][3] = { { {100, 200, 150} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[1] == 127);
		}
	}

	TEST_CASE("BGR to HSV, value", "[BGRtoHSV_value]")
	{
		SECTION("Value 0 (min)")
		{
			uchar arr[1][1][3] = { { {0, 0, 0} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[2] == 0);
		}

		SECTION("Value 255 (max)")
		{
			uchar arr[1][1][3] = { { {100, 255, 0} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[2] == 255);
		}

		SECTION("Value 200")
		{
			uchar arr[1][1][3] = { { {100, 200, 0} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[2] == 200);
		}
	}

	TEST_CASE("BGR to HSV conversion", "[BGRtoHSV]")
	{
		SECTION("One pixel")
		{
			uchar arr[1][1][3] = { { {10, 70, 190} } };
			auto mat = cv::Mat(1, 1, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 10);
			REQUIRE(newMatData[1] == 241);
			REQUIRE(newMatData[2] == 190);
		}

		SECTION("Multi-dimension mat")
		{
			uchar arr[2][2][3] =
			{
				{ {210, 110, 70}, {10, 70, 190} },
				{ {190, 70, 10}, {70, 110, 210} }
			};
			auto mat = cv::Mat(2, 2, CV_8UC3, &arr);
			auto newMat = POBR::convertBGRToHSV(mat);
			auto newMatData = newMat.data;

			REQUIRE(newMatData[0] == 111);
			REQUIRE(newMatData[1] == 170);
			REQUIRE(newMatData[2] == 210);

			REQUIRE(newMatData[3] == 10);
			REQUIRE(newMatData[4] == 241);
			REQUIRE(newMatData[5] == 190);

			REQUIRE(newMatData[6] == 110);
			REQUIRE(newMatData[7] == 241);
			REQUIRE(newMatData[8] == 190);

			REQUIRE(newMatData[9] == 8);
			REQUIRE(newMatData[10] == 170);
			REQUIRE(newMatData[11] == 210);
		}
	}
}