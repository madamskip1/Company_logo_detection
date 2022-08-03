#pragma once
#include "RawMoments.h"

#include "Moment.h"

namespace POBR
{
	struct CentralMoments
	{
		Moment M_00;
		Moment M_01;
		Moment M_10;
		Moment M_11;
		Moment M_20;
		Moment M_02;
		Moment M_21;
		Moment M_12;
		Moment M_30;
		Moment M_03;

		CentralMoments() = delete;
		CentralMoments(const Moment& M_00, const Moment& M_01, const Moment& M_10, const Moment& M_11, const Moment& M_20, const Moment& M_02, const Moment& M_21, const Moment& M_12, const Moment& M_30, const Moment& M_03)
			: M_00{ M_00 }, M_01{ M_01 }, M_10{ M_10 }, M_11{ M_11 }, M_20{ M_20 }, M_02{ M_02 }, M_21{ M_21 }, M_12{ M_12 }, M_30{ M_30 }, M_03{ M_03 } {};
	};

	CentralMoments calcNormalizedCentralMoments(const RawMoments& rawMoments);
}