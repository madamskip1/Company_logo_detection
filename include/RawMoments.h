#pragma once
#include "Blob.h"

namespace POBR
{
	struct RawMoments
	{
		double m_00;
		double m_01;
		double m_10;
		double m_11;
		double m_20;
		double m_02;
		double m_21;
		double m_12;
		double m_30;
		double m_03;

		RawMoments() = delete;

		RawMoments(double m_00, double m_01, double m_10, double m_11, double m_20, double m_02, double m_21, double m_12, double m_30, double m_03)
			: m_00{ m_00 }, m_01{ m_01 }, m_10{ m_10 }, m_11{ m_11 }, m_20{ m_20 }, m_02{ m_02 }, m_21{ m_21 }, m_12{ m_12 }, m_30{ m_30 }, m_03{ m_03 } {};
	};

	RawMoments calcRawMoments(const Blob& blob);
}