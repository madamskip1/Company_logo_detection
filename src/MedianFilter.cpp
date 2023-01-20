#include "MedianFilter.h"

#include <iostream>
#include <algorithm>

namespace POBR
{
	cv::Mat filterMedian(const cv::Mat& inMat, const int kernelSize)
	{
		CV_Assert(kernelSize % 2 != 0);
		std::cout << "--POBR::Median Filter --- start" << std::endl;

		auto imgRows{ inMat.rows };
		auto imgCols{ inMat.cols };
		auto imgChannels{ inMat.channels() };
		auto anchorX{ static_cast<int>(kernelSize / 2) };
		auto anchorY{ static_cast<int>(kernelSize / 2) };
		auto windowPoints = kernelSize * kernelSize;

		auto outputMat = inMat.clone();

		for (auto y = anchorY; y < (imgRows - anchorY); ++y)
		{
			uchar* outputMatRow = outputMat.ptr<uchar>(y);

			for (auto x = anchorX; x < (imgCols - anchorX); ++x)
			{
				auto newValues = std::vector<uchar>(windowPoints * imgChannels);

				auto outputMatCol = x * imgChannels;
				auto valueIndex{ 0 };

				for (auto ky = 0; ky < kernelSize; ++ky)
				{
					auto inMatY{ y + ky - anchorY };
					auto* inMatRow = inMat.ptr<uchar>(inMatY);

					for (auto kx = 0; kx < kernelSize; ++kx)
					{
						auto inMatX{ x + kx - anchorX };
						inMatX *= imgChannels;

						for (auto c = 0; c < imgChannels; ++c)
						{
							auto index = windowPoints * c + valueIndex;
							newValues[index] = inMatRow[inMatX + c];
						}

						valueIndex++;
					}
				}

				for (auto c = 0; c < imgChannels; ++c)
				{
					auto startElement = newValues.begin() + (windowPoints * c);
					auto endElement = startElement + windowPoints;
					std::sort(startElement, endElement);
					auto medianPoint = startElement + (windowPoints / 2);
					auto midValue = *medianPoint;
					outputMatRow[outputMatCol + c] = midValue;
				}
			}
		}
		std::cout << "--POBR::Median Filter --- end" << std::endl;
		return outputMat;
	}
}