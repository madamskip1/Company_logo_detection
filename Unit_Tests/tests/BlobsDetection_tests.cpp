#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "BlobsDetection.h"


namespace BlobsDetectionTests
{

	TEST_CASE("One pixel mat", "[ONE_PIXEL_BLOBS]")
	{
		SECTION("Pixel == 0")
		{
			uchar arr[1][1][1] = { { 0 } };
			auto mat = cv::Mat(1, 1, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 0);
		}

		SECTION("Pixel == 255")
		{
			uchar arr[1][1][1] = { { 255 } };
			auto mat = cv::Mat(1, 1, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 1);
			auto blob = blobs[0];
			REQUIRE(blob.countPoints() == 1);
			auto blobCorners = blob.getCorners();
			CHECK(blobCorners.first == cv::Point2i{ 0, 0 });
			CHECK(blobCorners.second == cv::Point2i{ 0, 0 });
		}
	}

	TEST_CASE("Multi-dimension mat", "[MULTI_DIM_BLOBS]")
	{
		SECTION("All pixels == 0")
		{
			uchar arr[3][3][1] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
			auto mat = cv::Mat(3, 3, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 0);
		}

		SECTION("All pixels == 255")
		{
			uchar arr[3][3][1] = { { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 255 } };
			auto mat = cv::Mat(3, 3, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 1);
			auto blob = blobs[0];
			REQUIRE(blob.countPoints() == 9);
			auto blobCorners = blob.getCorners();
			CHECK(blobCorners.first == cv::Point2i{ 0, 0 });
			CHECK(blobCorners.second == cv::Point2i{ 2, 2 });
		}

		SECTION("Two blobs")
		{
			uchar arr[3][3][1] = { { 255, 255, 0 }, { 255, 0, 0 }, { 0, 0, 255 } };
			auto mat = cv::Mat(3, 3, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 2);
			auto blob1 = blobs[0];
			REQUIRE(blob1.countPoints() == 3);
			auto blob1Corners = blob1.getCorners();
			CHECK(blob1Corners.first == cv::Point2i{ 0, 0 });
			CHECK(blob1Corners.second == cv::Point2i{ 1, 1 });

			auto blob2 = blobs[1];
			REQUIRE(blob2.countPoints() == 1);
			auto blob2Corners = blob2.getCorners();
			CHECK(blob2Corners.first == cv::Point2i{ 2, 2 });
			CHECK(blob2Corners.second == cv::Point2i{ 2, 2 });
		}

		SECTION("Diagonal pixels")
		{
			uchar arr[3][3][1] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 0 } };
			auto mat = cv::Mat(3, 3, CV_8UC1, &arr);
			auto blobs = detectBlobs(mat);

			REQUIRE(blobs.size() == 1);
			auto blob = blobs[0];
			REQUIRE(blob.countPoints() == 2);
			auto blobCorners = blob.getCorners();
			CHECK(blobCorners.first == cv::Point2i{ 0, 0 });
			CHECK(blobCorners.second == cv::Point2i{ 1, 1 });
		}
	}
}