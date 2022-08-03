#pragma once
#include "Blob.h"

#include "Moment.h"

namespace POBR
{
	struct RawMoments
	{
		Moment m_00;
		Moment m_01;
		Moment m_10;
		Moment m_11;
		Moment m_20;
		Moment m_02;
		Moment m_21;
		Moment m_12;
		Moment m_30;
		Moment m_03;

		RawMoments() = delete;

		RawMoments(const Moment& m_00, const Moment& m_01, const Moment& m_10, const Moment& m_11, const Moment& m_20, const Moment& m_02, const Moment& m_21, const Moment& m_12, const Moment& m_30, const Moment& m_03)
			: m_00{ m_00 }, m_01{ m_01 }, m_10{ m_10 }, m_11{ m_11 }, m_20{ m_20 }, m_02{ m_02 }, m_21{ m_21 }, m_12{ m_12 }, m_30{ m_30 }, m_03{ m_03 } {};
	};

	RawMoments calcRawMoments(const Blob& blob);
}