#include "CentralMoments.h"
#include <cmath>
#include <opencv2/opencv.hpp>


namespace POBR
{
	static cv::Point2d calcCentroid(const RawMoments& rawMoments)
	{
		auto x = rawMoments.m_10 / rawMoments.m_00;
		auto y = rawMoments.m_01 / rawMoments.m_00;

		return cv::Point2d(x, y);
	}

	static void normalizeCentralMoment(Moment& centralMoment, const double m_00)
	{
		auto powExponent = ((centralMoment.i + centralMoment.j) / 2.0) + 1.0;
		auto normalizedValue = centralMoment / std::pow(m_00, powExponent);
		
		centralMoment.value = normalizedValue;
	}

	static void normalizeCentralMoments(CentralMoments& centralMoments, const double m_00)
	{
		normalizeCentralMoment(centralMoments.M_00, m_00);
		normalizeCentralMoment(centralMoments.M_01, m_00);
		normalizeCentralMoment(centralMoments.M_10, m_00);
		normalizeCentralMoment(centralMoments.M_11, m_00);
		normalizeCentralMoment(centralMoments.M_20, m_00);
		normalizeCentralMoment(centralMoments.M_02, m_00);
		normalizeCentralMoment(centralMoments.M_21, m_00);
		normalizeCentralMoment(centralMoments.M_12, m_00);
		normalizeCentralMoment(centralMoments.M_30, m_00);
		normalizeCentralMoment(centralMoments.M_03, m_00);
	}

	CentralMoments calcNormalizedCentralMoments(const RawMoments& rawMoments)
	{
		auto centroid = calcCentroid(rawMoments);

		auto M_00_val = rawMoments.m_00;
		auto M_01_val = rawMoments.m_01 - (rawMoments.m_01 / rawMoments.m_00) * rawMoments.m_00;
		auto M_10_val = rawMoments.m_10 - (rawMoments.m_10 / rawMoments.m_00) * rawMoments.m_00;
		auto M_11_val = rawMoments.m_11 - rawMoments.m_10 * rawMoments.m_01 / rawMoments.m_00;
		auto M_20_val = rawMoments.m_20 - std::pow(rawMoments.m_10, 2.0) / rawMoments.m_00;
		auto M_02_val = rawMoments.m_02 - std::pow(rawMoments.m_01, 2.0) / rawMoments.m_00;
		auto M_21_val = rawMoments.m_21 - 2.0 * rawMoments.m_11 * centroid.x - rawMoments.m_20 * centroid.y + 2.0 * rawMoments.m_01 * std::pow(centroid.x, 2.0);
		auto M_12_val = rawMoments.m_12 - 2.0 * rawMoments.m_11 * centroid.y - rawMoments.m_02 * centroid.x + 2.0 * rawMoments.m_10 * std::pow(centroid.y, 2.0);
		auto M_30_val = rawMoments.m_30 - 3.0 * rawMoments.m_20 * centroid.x + 2.0 * rawMoments.m_10 * std::pow(centroid.x, 2.0);
		auto M_03_val = rawMoments.m_03 - 3.0 * rawMoments.m_02 * centroid.y + 2.0 * rawMoments.m_01 * std::pow(centroid.y, 2.0);
		
		auto M_00 = Moment{ M_00_val, 0, 0 };
		auto M_01 = Moment{ M_01_val, 0, 1 };
		auto M_10 = Moment{ M_10_val, 1, 0 };
		auto M_11 = Moment{ M_11_val, 1, 1 };
		auto M_20 = Moment{ M_20_val, 2, 0 };
		auto M_02 = Moment{ M_02_val, 0, 2 };
		auto M_21 = Moment{ M_21_val, 2, 1 };
		auto M_12 = Moment{ M_12_val, 1, 2 };
		auto M_30 = Moment{ M_30_val, 3, 0 };
		auto M_03 = Moment{ M_03_val, 0, 3 };

		auto centralMoments = CentralMoments(M_00, M_01, M_10, M_11, M_20, M_02, M_21, M_12, M_30, M_03);
		normalizeCentralMoments(centralMoments, rawMoments.m_00);
		
		return centralMoments;
	}
}