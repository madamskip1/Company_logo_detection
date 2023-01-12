#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "FilterImage.h"


namespace FilterImageTests
{
	TEST_CASE("Identity kernel", "[Identity_kernel]")
	{
		SECTION("3x3, 1 channel")
		{
			uchar arr[3][3][1] = {
				{ {1}, {2}, {3} },
				{ {4}, {5}, {6} },
				{ {7}, {8}, {9} }
			};
			auto mat = cv::Mat(3, 3, CV_8UC1, &arr);

			float kernel[3][3][1] = {
				{ {0.0 / 9.0}, {0.0 / 9.0}, {0.0 / 9.0} },
				{ {0.0 / 9.0}, {9.0 / 9.0}, {0.0 / 9.0} },
				{ {0.0 / 9.0}, {0.0 / 9.0}, {0.0 / 9.0} }
			};
			auto kernelMat = cv::Mat(3, 3, CV_32F, &kernel);

			auto output = POBR::filterImage(mat, kernelMat);
			auto outputData = output.data;
			
			REQUIRE(outputData[0] == 1);
			REQUIRE(outputData[1] == 2);
			REQUIRE(outputData[2] == 3);

			REQUIRE(outputData[3] == 4);
			REQUIRE(outputData[4] == 5);
			REQUIRE(outputData[5] == 6);

			REQUIRE(outputData[6] == 7);
			REQUIRE(outputData[7] == 8);
			REQUIRE(outputData[8] == 9);
		}

		SECTION("3x3, 3 channels")
		{
			uchar arr[3][3][3] = {
				{ { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } },
				{ { 10, 11, 12 }, { 13, 14, 15 }, { 16, 17, 18 } },
				{ { 19, 20, 21 }, { 22, 23, 24 }, { 25, 26, 27 } }
			};
			auto mat = cv::Mat(3, 3, CV_8UC3, &arr);

			float kernel[3][3][1] = {
				{ {0.0 / 9.0}, {0.0 / 9.0}, {0.0 / 9.0} },
				{ {0.0 / 9.0}, {9.0 / 9.0}, {0.0 / 9.0} },
				{ {0.0 / 9.0}, {0.0 / 9.0}, {0.0 / 9.0} }
			};
			auto kernelMat = cv::Mat(3, 3, CV_32F, &kernel);

			auto output = POBR::filterImage(mat, kernelMat);
			auto outputData = output.data;

			REQUIRE(outputData[0] == 1);
			REQUIRE(outputData[1] == 2);
			REQUIRE(outputData[2] == 3);

			REQUIRE(outputData[3] == 4);
			REQUIRE(outputData[4] == 5);
			REQUIRE(outputData[5] == 6);

			REQUIRE(outputData[6] == 7);
			REQUIRE(outputData[7] == 8);
			REQUIRE(outputData[8] == 9);

			REQUIRE(outputData[9] == 10);
			REQUIRE(outputData[10] == 11);
			REQUIRE(outputData[11] == 12);

			REQUIRE(outputData[12] == 13);
			REQUIRE(outputData[13] == 14);
			REQUIRE(outputData[14] == 15);

			REQUIRE(outputData[15] == 16);
			REQUIRE(outputData[16] == 17);
			REQUIRE(outputData[17] == 18);
		}

		SECTION("5x5, 1 channel")
		{
			uchar arr[5][5][1] = {
				{ 1, 2, 3, 4, 5 },
				{ 6, 7, 8, 9, 10 },
				{ 11, 12, 13, 14, 15 },
				{ 16, 17, 18, 19, 20 },
				{ 21, 22, 23, 24, 25 },
			};
			auto mat = cv::Mat(5, 5, CV_8UC3, &arr);

			float kernel[5][5][1] = {
				{ {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0} },
				{ {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0} },
				{ {0.0 / 25.0}, {0.0 / 25.0}, {25.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0} },
				{ {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0} },
				{ {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0}, {0.0 / 25.0} }
			};
			auto kernelMat = cv::Mat(5, 5, CV_32F, &kernel);

			auto output = POBR::filterImage(mat, kernelMat);
			auto outputData = output.data;

			REQUIRE(outputData[0] == 1);
			REQUIRE(outputData[1] == 2);
			REQUIRE(outputData[2] == 3);
			REQUIRE(outputData[3] == 4);
			REQUIRE(outputData[4] == 5);

			REQUIRE(outputData[5] == 6);
			REQUIRE(outputData[6] == 7);
			REQUIRE(outputData[7] == 8);
			REQUIRE(outputData[8] == 9);
			REQUIRE(outputData[9] == 10);

			REQUIRE(outputData[10] == 11);
			REQUIRE(outputData[11] == 12);
			REQUIRE(outputData[12] == 13);
			REQUIRE(outputData[13] == 14);
			REQUIRE(outputData[14] == 15);

			REQUIRE(outputData[15] == 16);
			REQUIRE(outputData[16] == 17);
			REQUIRE(outputData[17] == 18);
			REQUIRE(outputData[18] == 19);
			REQUIRE(outputData[19] == 20);

			REQUIRE(outputData[20] == 21);
			REQUIRE(outputData[21] == 22);
			REQUIRE(outputData[22] == 23);
			REQUIRE(outputData[23] == 24);
			REQUIRE(outputData[24] == 25);
		}
	}

	TEST_CASE("Custom kernel", "[custor_kernel]")
	{
		uchar arr[3][3][1] = {
				{ {1}, {2}, {1} },
				{ {1}, {3}, {1} },
				{ {1}, {2}, {1} }
		};
		auto mat = cv::Mat(3, 3, CV_8UC1, &arr);

		float kernel[3][3][1] = {
			{ {1.0 / 9.0}, {2.0 / 9.0}, {1.0 / 9.0} },
			{ {0.0 / 9.0}, {1.0 / 9.0}, {0.0 / 9.0} },
			{ {1.0 / 9.0}, {2.0 / 9.0}, {1.0 / 9.0} }
		};
		auto kernelMat = cv::Mat(3, 3, CV_32F, &kernel);

		auto output = POBR::filterImage(mat, kernelMat);
		auto outputData = output.data;

		REQUIRE(outputData[0] == 1);
		REQUIRE(outputData[1] == 2);
		REQUIRE(outputData[2] == 1);

		REQUIRE(outputData[3] == 1);
		REQUIRE(outputData[4] == 1);
		REQUIRE(outputData[5] == 1);

		REQUIRE(outputData[6] == 1);
		REQUIRE(outputData[7] == 2);
		REQUIRE(outputData[8] == 1);
	}

	TEST_CASE("val < 0", "[filter_less_than_zero]")
	{
		uchar arr[3][3][1] = {
				{ {1}, {2}, {1} },
				{ {1}, {3}, {1} },
				{ {1}, {2}, {1} }
		};
		auto mat = cv::Mat(3, 3, CV_8UC1, &arr);

		float kernel[3][3][1] = {
			{ {1.0 / 9.0}, {0.0 / 9.0}, {1.0 / 9.0} },
			{ {0.0 / 9.0}, {-5.0 / 9.0}, {0.0 / 9.0} },
			{ {1.0 / 9.0}, {0.0 / 9.0}, {1.0 / 9.0} }
		};
		auto kernelMat = cv::Mat(3, 3, CV_32F, &kernel);

		auto output = POBR::filterImage(mat, kernelMat);
		auto outputData = output.data;

		REQUIRE(outputData[0] == 1);
		REQUIRE(outputData[1] == 2);
		REQUIRE(outputData[2] == 1);

		REQUIRE(outputData[3] == 1);
		REQUIRE(outputData[4] == 0);
		REQUIRE(outputData[5] == 1);

		REQUIRE(outputData[6] == 1);
		REQUIRE(outputData[7] == 2);
		REQUIRE(outputData[8] == 1);
	}

	TEST_CASE("val > 255", "[filter_less_than_zero]")
	{
		uchar arr[3][3][1] = {
				{ {255}, {2}, {255} },
				{ {1}, {255}, {1} },
				{ {255}, {2}, {255} }
		};
		auto mat = cv::Mat(3, 3, CV_8UC1, &arr);

		float kernel[3][3][1] = {
			{ {2.0 / 9.0}, {-1.0 / 9.0}, {2.0 / 9.0} },
			{ {-1.0 / 9.0}, {5.0 / 9.0}, {-1.0 / 9.0} },
			{ {2.0 / 9.0}, {-1.0 / 9.0}, {2.0 / 9.0} }
		};
		auto kernelMat = cv::Mat(3, 3, CV_32F, &kernel);

		auto output = POBR::filterImage(mat, kernelMat);
		auto outputData = output.data;

		REQUIRE(outputData[0] == 255);
		REQUIRE(outputData[1] == 2);
		REQUIRE(outputData[2] == 255);

		REQUIRE(outputData[3] == 1);
		REQUIRE(outputData[4] == 255);
		REQUIRE(outputData[5] == 1);

		REQUIRE(outputData[6] == 255);
		REQUIRE(outputData[7] == 2);
		REQUIRE(outputData[8] == 255);
	}
}