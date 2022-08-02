#include "RawMoments.h"

namespace POBR
{
	static double calcRawMoment(const Blob& blob, const int p, const int q)
	{
		auto moment{ 0.0 };
		auto& points = blob.getPoints();
		for (const auto& point : points)
		{
			moment += static_cast<double>(std::pow(point.x, p) * std::pow(point.y, q));
		}
		return moment;
	}

	RawMoments calcRawMoments(const Blob& blob)
	{
		auto m_00 = calcRawMoment(blob, 0, 0);
		auto m_01 = calcRawMoment(blob, 0, 1);
		auto m_10 = calcRawMoment(blob, 1, 0);
		auto m_11 = calcRawMoment(blob, 1, 1);
		auto m_20 = calcRawMoment(blob, 2, 0);
		auto m_02 = calcRawMoment(blob, 0, 2);
		auto m_21 = calcRawMoment(blob, 2, 1);
		auto m_12 = calcRawMoment(blob, 1, 2);
		auto m_30 = calcRawMoment(blob, 3, 0);
		auto m_03 = calcRawMoment(blob, 0, 3);
		
		auto rawMoment = RawMoments(m_00, m_01, m_10, m_11, m_20, m_02, m_21, m_12, m_30, m_03);
		return rawMoment;
	}
}