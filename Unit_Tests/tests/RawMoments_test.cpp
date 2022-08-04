#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>

#include "RawMoments.h"
#include "Blob.h"

namespace RawMomentsTests
{
	TEST_CASE("Raw Moments", "[RAW_MOMENTS]")
	{
		SECTION("single pixel == 255")
		{
			auto blob = POBR::Blob();
			blob.addPoint(cv::Point2i{ 0, 0 });
			auto rawMoments = POBR::calcRawMoments(blob);

			CHECK(rawMoments.m_00 == 1);
			CHECK(rawMoments.m_01 == 0);
			CHECK(rawMoments.m_10 == 0);
			CHECK(rawMoments.m_11 == 0);
			CHECK(rawMoments.m_20 == 0);
			CHECK(rawMoments.m_02 == 0);
			CHECK(rawMoments.m_21 == 0);
			CHECK(rawMoments.m_12 == 0);
			CHECK(rawMoments.m_30 == 0);
			CHECK(rawMoments.m_03 == 0);

		}

		SECTION("single Pixel == 255, but not {0,0}")
		{
			auto blob = POBR::Blob();
			blob.addPoint(cv::Point2i{ 2, 3 });
			auto rawMoments = POBR::calcRawMoments(blob);

			CHECK(rawMoments.m_00 == 1);
			CHECK(rawMoments.m_01 == 3);
			CHECK(rawMoments.m_10 == 2);
			CHECK(rawMoments.m_11 == 6);
			CHECK(rawMoments.m_20 == 4);
			CHECK(rawMoments.m_02 == 9);
			CHECK(rawMoments.m_21 == 12);
			CHECK(rawMoments.m_12 == 18);
			CHECK(rawMoments.m_30 == 8);
			CHECK(rawMoments.m_03 == 27);
		}
		
		SECTION("More pixels == 255")
		{
			auto blob = POBR::Blob();
			blob.addPoint(cv::Point2i{ 1, 2 });
			blob.addPoint(cv::Point2i{ 2, 3 });
			auto rawMoments = POBR::calcRawMoments(blob);

			CHECK(rawMoments.m_00 == 2);
			CHECK(rawMoments.m_01 == 5);
			CHECK(rawMoments.m_10 == 3);
			CHECK(rawMoments.m_11 == 8);
			CHECK(rawMoments.m_20 == 5);
			CHECK(rawMoments.m_02 == 13);
			CHECK(rawMoments.m_21 == 14);
			CHECK(rawMoments.m_12 == 22);
			CHECK(rawMoments.m_30 == 9);
			CHECK(rawMoments.m_03 == 35);
		}
	}
}