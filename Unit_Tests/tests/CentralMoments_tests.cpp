#include <catch2/catch.hpp>
#include <opencv2/opencv.hpp>

#include "CentralMoments.h"
#include "RawMoments.h"
#include "Moment.h"

namespace CentralMomentsTest
{
	TEST_CASE("All rawMoments == 1", "[CENTRAL_1ALL]")
	{
		auto m_00 = POBR::Moment{ 1.0, 0, 0 };
		auto m_01 = POBR::Moment{ 1.0, 0, 1 };
		auto m_10 = POBR::Moment{ 1.0, 1, 0 };
		auto m_11 = POBR::Moment{ 1.0, 1, 1 };
		auto m_20 = POBR::Moment{ 1.0, 2, 1 };
		auto m_02 = POBR::Moment{ 1.0, 0, 2 };
		auto m_21 = POBR::Moment{ 1.0, 2, 1 };
		auto m_12 = POBR::Moment{ 1.0, 1, 2 };
		auto m_30 = POBR::Moment{ 1.0, 3, 0 };
		auto m_03 = POBR::Moment{ 1.0, 0, 3 };
		auto rawMoments = POBR::RawMoments{ m_00, m_01, m_10, m_11, m_20, m_02, m_21, m_12, m_30, m_03 };
		// Centroid = { 1.0, 1.0 }

		auto centralMoments = POBR::calcNormalizedCentralMoments(rawMoments);
		CHECK(centralMoments.M_00.value == 1.0);
		CHECK(centralMoments.M_01.value == 0.0);
		CHECK(centralMoments.M_10.value == 0.0);
		CHECK(centralMoments.M_11.value == 0.0);
		CHECK(centralMoments.M_20.value == 0.0);
		CHECK(centralMoments.M_02.value == 0.0);
		CHECK(centralMoments.M_21.value == 0.0);
		CHECK(centralMoments.M_12.value == 0.0);
		CHECK(centralMoments.M_30.value == 0.0);
		CHECK(centralMoments.M_30.value == 0.0);
	}

	TEST_CASE("All rawMoments == 0 except m_00 == 1", "[CENTRAL_0ALL]")
	{
		auto m_00 = POBR::Moment{ 1.0, 0, 0 };
		auto m_01 = POBR::Moment{ 0.0, 0, 1 };
		auto m_10 = POBR::Moment{ 0.0, 1, 0 };
		auto m_11 = POBR::Moment{ 0.0, 1, 1 };
		auto m_20 = POBR::Moment{ 0.0, 2, 1 };
		auto m_02 = POBR::Moment{ 0.0, 0, 2 };
		auto m_21 = POBR::Moment{ 0.0, 2, 1 };
		auto m_12 = POBR::Moment{ 0.0, 1, 2 };
		auto m_30 = POBR::Moment{ 0.0, 3, 0 };
		auto m_03 = POBR::Moment{ 0.0, 0, 3 };
		auto rawMoments = POBR::RawMoments{ m_00, m_01, m_10, m_11, m_20, m_02, m_21, m_12, m_30, m_03 };
		// Centroid = { 1.0, 1.0 }

		auto centralMoments = POBR::calcNormalizedCentralMoments(rawMoments);
		CHECK(centralMoments.M_00.value == 1.0);
		CHECK(centralMoments.M_01.value == 0.0);
		CHECK(centralMoments.M_10.value == 0.0);
		CHECK(centralMoments.M_11.value == 0.0);
		CHECK(centralMoments.M_20.value == 0.0);
		CHECK(centralMoments.M_02.value == 0.0);
		CHECK(centralMoments.M_21.value == 0.0);
		CHECK(centralMoments.M_12.value == 0.0);
		CHECK(centralMoments.M_30.value == 0.0);
		CHECK(centralMoments.M_30.value == 0.0);
	}

	TEST_CASE("rawMoments random", "[CENTRAL_RANDOM]")
	{
		auto m_00 = POBR::Moment{ 0.5, 0, 0 };
		auto m_01 = POBR::Moment{ 1.0, 0, 1 };
		auto m_10 = POBR::Moment{ 1.5, 1, 0 };
		auto m_11 = POBR::Moment{ 2.0, 1, 1 };
		auto m_20 = POBR::Moment{ 2.5, 2, 1 };
		auto m_02 = POBR::Moment{ 2.0, 0, 2 };
		auto m_21 = POBR::Moment{ 1.5, 2, 1 };
		auto m_12 = POBR::Moment{ 1.0, 1, 2 };
		auto m_30 = POBR::Moment{ 0.5, 3, 0 };
		auto m_03 = POBR::Moment{ 0.0, 0, 3 };
		auto rawMoments = POBR::RawMoments{ m_00, m_01, m_10, m_11, m_20, m_02, m_21, m_12, m_30, m_03 };
		// Centroid = { 3.0, 2.0 }

		auto centralMoments = POBR::calcNormalizedCentralMoments(rawMoments);
		CHECK(centralMoments.M_00.value == 1.0);
		CHECK(centralMoments.M_01.value == 0.0);
		CHECK(centralMoments.M_10.value == 0.0);
		CHECK(centralMoments.M_11.value == -4.0);
		CHECK(centralMoments.M_20.value == -8.0);
		CHECK(centralMoments.M_02.value == 0.0);
		auto M_21_epsilon = centralMoments.M_21.value - 14.1421;
		CHECK((M_21_epsilon < 0.0001 && M_21_epsilon > -0.0001));
		auto M_12_epsilon = centralMoments.M_12.value + 5.6568;
		CHECK((M_12_epsilon < 0.0001 && M_12_epsilon > -0.0001));
		auto M_30_epsilon = centralMoments.M_30.value - 28.2842;
		CHECK((M_30_epsilon < 0.0001 && M_30_epsilon > -0.0001));
		auto M_03_epsilon = centralMoments.M_03.value + 22.6274;
		CHECK((M_03_epsilon < 0.0001 && M_03_epsilon > -0.0001));
	}
}