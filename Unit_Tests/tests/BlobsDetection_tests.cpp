#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>
#include "BlobsDetection.h"


namespace BlobsDetectionTests
{

	TEST_CASE("One pixel mat", "[ONE_PIXEL]")
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

}