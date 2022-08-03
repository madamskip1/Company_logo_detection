#pragma once
#include "CentralMoments.h"

namespace POBR
{
	class HuMoments
	{
	public:
		double hu_1{ 0.0 };
		double hu_2{ 0.0 };
		double hu_3{ 0.0 };
		double hu_4{ 0.0 };
		double hu_5{ 0.0 };
		double hu_6{ 0.0 };
		double hu_7{ 0.0 };
		double hu_8{ 0.0 };
		double hu_9{ 0.0 };
		double hu_10{ 0.0 };

		HuMoments() = default;
		HuMoments(double hu_1, double hu_2, double hu_3, double hu_4, double hu_5, double hu_6, double hu_7, double hu_8, double hu_9, double hu_10)
			: hu_1{ hu_1 }, hu_2{ hu_2 }, hu_3{ hu_3 }, hu_4{ hu_4 }, hu_5{ hu_5 }, hu_6{ hu_6 }, hu_7{ hu_7 }, hu_8{ hu_8 }, hu_9{ hu_9 }, hu_10{ hu_10 } {};
	};

	HuMoments calcHuMoments(const CentralMoments& normalizedCentralMoments);
}