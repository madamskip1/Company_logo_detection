#pragma once
#include "RawMoments.h"

namespace POBR
{
	struct CentralMoments
	{
		double M_00;
		double M_01;
		double M_10;
		double M_11;
		double M_20;
		double M_02;
		double M_21;
		double M_12;
		double M_30;
		double M_03;

		CentralMoments() = delete;
		CentralMoments(double M_00, double M_01, double M_10, double M_11, double M_20, double M_02, double M_21, double M_12, double M_30, double M_03)
			: M_00{ M_00 }, M_01{ M_01 }, M_10{ M_10 }, M_11{ M_11 }, M_20{ M_20 }, M_02{ M_02 }, M_21{ M_21 }, M_12{ M_12 }, M_30{ M_30 }, M_03{ M_03 } {};
	};

	CentralMoments calcNormalizedCentralMoments(const RawMoments& rawMoments);
}