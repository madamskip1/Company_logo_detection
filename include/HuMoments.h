#pragma once

#include <initializer_list>
#include <vector>

#include "CentralMoments.h"
#include "Blob.h"

namespace POBR
{
	class HuMoments
	{
	public:
		HuMoments() = delete;
		HuMoments(double hu_1 = 0.0, double hu_2 = 0.0, double hu_3 = 0.0, double hu_4 = 0.0, double hu_5 = 0.0, double hu_6 = 0.0, double hu_7 = 0.0, double hu_8 = 0.0, double hu_9 = 0.0, double hu_10 = 0.0);

		static HuMoments calcHuMoments(const CentralMoments& normalizedCentralMoments);
		static HuMoments calcHuMoments(const Blob& blob);

		bool isInRange(const HuMoments& min, const HuMoments& max) const;
		double operator[](int index) const;

		void print() const;
		std::vector<double> getHuValues() const;

	private:
		std::vector<double> huValues;
	};
}