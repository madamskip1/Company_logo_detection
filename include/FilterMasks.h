#pragma once
#include <opencv2/core/mat.hpp>

namespace POBR
{
	cv::Mat getSharpenMask()
	{
		float mask[3][3][1] = {
			{ 0.0, -1.0, 0.0 },
			{ -1.0, 5.0, -1.0 },
			{ 0.0, -1.0, 0.0 }
		};

		auto maskMat = cv::Mat(3, 3, CV_32F, &mask);
		return maskMat;
	}
}