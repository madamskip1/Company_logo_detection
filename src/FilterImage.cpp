#include "FilterImage.h"
#include <algorithm>

namespace POBR
{
	cv::Mat filterImage(const cv::Mat& inMat, const cv::Mat& kernel)
	{
		CV_Assert(kernel.rows == kernel.cols);
		CV_Assert(kernel.rows % 2 != 0);



		auto imgRows{ inMat.rows };
		auto imgCols{ inMat.cols };
		auto imgChannels{ inMat.channels() };
		auto kernelSize{ kernel.rows };
		auto anchorX{ static_cast<int>(kernelSize / 2) };
		auto anchorY{ static_cast<int>(kernelSize / 2) };

		auto outputMat = inMat.clone();



		for (auto y = anchorY; y < (imgRows - anchorY); ++y)
		{
			uchar* outputMatRow = outputMat.ptr<uchar>(y);

			for (auto x = anchorX; x < (imgCols - anchorX); ++x)
			{
				auto newValues = std::vector<float>(inMat.channels(), 0.0);
				auto outputMatCol = x * imgChannels;

				for (auto ky = 0; ky < kernelSize; ++ky)
				{
					auto inMatY{ y + ky - anchorY };
					auto* inMatRow = inMat.ptr<uchar>(inMatY);

					auto kernelRow = kernel.ptr<float>(ky);

					for (auto kx = 0; kx < kernelSize; ++kx)
					{
						auto inMatX{ x + kx - anchorX };
						inMatX *= imgChannels;
						float kernelValue = kernelRow[kx];

						for (auto c = 0; c < imgChannels; ++c)
						{
							newValues[c] += inMatRow[inMatX + c] * kernelValue;
						}
					}
				}

				for (auto c = 0; c < imgChannels; ++c)
				{
					newValues[c] = std::clamp(newValues[c], 0.0f, 255.0f);
					outputMatRow[outputMatCol + c] = newValues[c];
				}

			}
		}

		return outputMat;
	}
}