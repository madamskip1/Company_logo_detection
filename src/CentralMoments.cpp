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

	static double normalizeCentralMoment(const double centralMoment, const double m_00, const double i, const double j)
	{
		auto powExponent = ((i + j) / 2.0) + 1.0;
		auto normalizedCentralMoment = centralMoment / std::pow(m_00, powExponent);
		return normalizedCentralMoment;
	}

	static void normalizeCentralMoments(CentralMoments& centralMoments, const double m_00)
	{
		centralMoments.M_00 = normalizeCentralMoment(centralMoments.M_00, m_00, 0.0, 0.0);
		centralMoments.M_01 = normalizeCentralMoment(centralMoments.M_01, m_00, 0.0, 1.0);
		centralMoments.M_10 = normalizeCentralMoment(centralMoments.M_10, m_00, 1.0, 0.0);
		centralMoments.M_11 = normalizeCentralMoment(centralMoments.M_11, m_00, 1.0, 1.0);
		centralMoments.M_20 = normalizeCentralMoment(centralMoments.M_20, m_00, 2.0, 0.0);
		centralMoments.M_02 = normalizeCentralMoment(centralMoments.M_02, m_00, 0.0, 2.0);
		centralMoments.M_21 = normalizeCentralMoment(centralMoments.M_21, m_00, 2.0, 1.0);
		centralMoments.M_12 = normalizeCentralMoment(centralMoments.M_12, m_00, 1.0, 2.0);
		centralMoments.M_30 = normalizeCentralMoment(centralMoments.M_30, m_00, 3.0, 0.0);
		centralMoments.M_03 = normalizeCentralMoment(centralMoments.M_03, m_00, 0.0, 3.0);
	}

	CentralMoments calcNormalizedCentralMoments(const RawMoments& rawMoments)
	{
		auto centroid = calcCentroid(rawMoments);

		auto M_00 = rawMoments.m_00;
		auto M_01 = rawMoments.m_01 - (rawMoments.m_01 / rawMoments.m_00) * rawMoments.m_00;
		auto M_10 = rawMoments.m_10 - (rawMoments.m_10 / rawMoments.m_00) * rawMoments.m_00;
		auto M_11 = rawMoments.m_11 - rawMoments.m_10 * rawMoments.m_01 / rawMoments.m_00;
		auto M_20 = rawMoments.m_20 - std::pow(rawMoments.m_10, 2.0) / rawMoments.m_00;
		auto M_02 = rawMoments.m_02 - std::pow(rawMoments.m_01, 2.0) / rawMoments.m_00;
		auto M_21 = rawMoments.m_21 - 2.0 * rawMoments.m_11 * centroid.x - rawMoments.m_20 * centroid.y + 2.0 * rawMoments.m_01 * std::pow(centroid.x, 2.0);
		auto M_12 = rawMoments.m_12 - 2.0 * rawMoments.m_11 * centroid.y - rawMoments.m_02 * centroid.x + 2.0 * rawMoments.m_10 * std::pow(centroid.y, 2.0);
		auto M_30 = rawMoments.m_30 - 3.0 * rawMoments.m_20 * centroid.x + 2.0 * rawMoments.m_10 * std::pow(centroid.x, 2.0);
		auto M_03 = rawMoments.m_03 - 3.0 * rawMoments.m_02 * centroid.y + 2.0 * rawMoments.m_01 * std::pow(centroid.y, 2.0);
		
		auto centralMoments = CentralMoments(M_00, M_01, M_10, M_11, M_20, M_02, M_21, M_12, M_30, M_03);
		normalizeCentralMoments(centralMoments, rawMoments.m_00);
		
		return centralMoments;
	}
}