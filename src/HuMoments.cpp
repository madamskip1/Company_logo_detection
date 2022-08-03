#include "HuMoments.h"

#include <algorithm>

namespace POBR
{
	HuMoments::HuMoments(double hu_1, double hu_2, double hu_3, double hu_4, double hu_5, double hu_6, double hu_7, double hu_8, double hu_9, double hu_10)
		: huValues{ hu_1, hu_2, hu_3, hu_4, hu_5, hu_6, hu_7, hu_8, hu_9, hu_10 }
	{
	}

	bool HuMoments::isInRange(const HuMoments& minHuMoments, const HuMoments& maxHuMoments) const
	{
		for (auto i = 0; i < huValues.size(); ++i)
		{
			auto value = huValues[i];
			auto min = minHuMoments[i];
			auto max = maxHuMoments[i];

			if (value < min || value > max)
			{
				return false;
			}
		}
		return true;
	}

	double HuMoments::operator[](int index) const
	{
		return huValues[index];
	}

	HuMoments HuMoments::calcHuMoments(const CentralMoments& normalizedCentralMoments)
	{
		auto& nCM = normalizedCentralMoments;

		double hu_1 = nCM.M_20 + nCM.M_02;
		double hu_2 = std::pow((nCM.M_20 - nCM.M_02), 2.0) + 4.0 * std::pow(nCM.M_11, 2.0);
		double hu_3 = std::pow((nCM.M_30 - 3.0 * nCM.M_12), 2.0) + std::pow((3.0 * nCM.M_21 - nCM.M_03), 2.0);
		double hu_4 = std::pow((nCM.M_30 + nCM.M_12), 2.0) + std::pow((nCM.M_21 + nCM.M_03), 2.0);
		double hu_5 = (nCM.M_30 - 3.0 * nCM.M_12) * (nCM.M_30 + nCM.M_12) * (std::pow((nCM.M_30 + nCM.M_12), 2.0) - 3.0 * std::pow((nCM.M_21 + nCM.M_03), 2.0)) +
			(3.0 * nCM.M_21 - nCM.M_03) * (nCM.M_21 + nCM.M_03) * (3.0 * std::pow((nCM.M_30 + nCM.M_12), 2.0) - std::pow((nCM.M_21 + nCM.M_03), 2.0));
		double hu_6 = (nCM.M_20 - nCM.M_02) * (std::pow((nCM.M_30 + nCM.M_12), 2.0) - std::pow((nCM.M_21 + nCM.M_03), 2.0)) +
			4.0 * nCM.M_11 * (nCM.M_30 + nCM.M_12) * (nCM.M_21 + nCM.M_03);
		double hu_7 = nCM.M_20 * nCM.M_02 - std::pow(nCM.M_11, 2.0);
		double hu_8 = nCM.M_30 * nCM.M_12 + nCM.M_21 * nCM.M_03 - std::pow(nCM.M_12, 2.0) - std::pow(nCM.M_21, 2.0);
		double hu_9 = nCM.M_20 * (nCM.M_21 * nCM.M_03 - std::pow(nCM.M_12, 2.0)) + nCM.M_02 * (nCM.M_30 * nCM.M_12 - std::pow(nCM.M_21, 2.0)) -
			nCM.M_11 * (nCM.M_30 * nCM.M_03 - nCM.M_21 * nCM.M_12);
		double hu_10 = std::pow((nCM.M_30 * nCM.M_03 - nCM.M_12 * nCM.M_21), 2.0) - 4.0 * (nCM.M_30 * nCM.M_12 - std::pow(nCM.M_21, 2.0)) * (nCM.M_03 * nCM.M_21 - nCM.M_12);

		auto huMoments = HuMoments{ hu_1, hu_2, hu_3, hu_4, hu_5, hu_6, hu_7, hu_8, hu_9, hu_10 };
		return huMoments;
	}
}
