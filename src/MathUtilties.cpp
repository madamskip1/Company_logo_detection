#include "MathUtilties.h"

#include <algorithm>
#include <cmath>

int calcMedian(std::vector<int> values)
{
	auto valuesSize = values.size();
	std::sort(values.begin(), values.end());
	auto median = (valuesSize % 2 != 0 ? values[valuesSize / 2] : (values[valuesSize / 2] + values[valuesSize / 2 + 1]) / 2);

	return median;
}

int calcSTD(std::vector<int> values, int avg)
{
	auto std{ 0 };
	for (auto i = 0; i < values.size(); ++i)
	{
		auto distToMean = values[i] - avg;
		std += std::pow(distToMean, 2.0);
	}
	std /= values.size();
	std = std::sqrt(std);
		
	return std;;
}
