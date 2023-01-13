#include "PrepareRedBlobs.h"
#include "ColorThresholding.h"
#include "MorphologyOperations.h"
#include "BlobsDetection.h"
#include "HuMoments.h"

#include <opencv2/opencv.hpp>

namespace POBR
{
	cv::Mat thresholdRed(cv::Mat& hsvMat);
	cv::Mat morphOpenRed(cv::Mat& binaryMat);
	void filterRedBlobs(POBR::Blobs& blobs);

	std::vector<POBR::Blob> prepareRedBlobs(cv::Mat& hsvMat)
	{
		auto thresholdedMat = thresholdRed(hsvMat);
		auto morphedOpenMat = morphOpenRed(thresholdedMat);
		cv::Mat resizedImg;
		cv::resize(morphedOpenMat, resizedImg, cv::Size{ 800, 600 });
		cv::imshow("MorphedProc", resizedImg);

		auto blobs = POBR::detectBlobs(morphedOpenMat);
		filterRedBlobs(blobs);
		blobs.draw(hsvMat);

		cv::imwrite("test.jpg", hsvMat);

		return std::vector<POBR::Blob>();
	}

	cv::Mat thresholdRed(cv::Mat& hsvMat)
	{
		auto hRange = POBR::ColorRange{ 165, 10 };
		auto sRange = POBR::ColorRange{ 70, 255 };
		auto vRange = POBR::ColorRange{ 70, 255 };

		auto thresholdedMat = POBR::thresholdByHSV(hsvMat, { hRange, sRange, vRange });

		return thresholdedMat;
	}

	cv::Mat morphOpenRed(cv::Mat& binaryMat)
	{
		auto erodeSize{ 3 };
		auto dilateSize{ 3 };

		auto morphedMat = POBR::erode(binaryMat, erodeSize);
		morphedMat = POBR::dilate(morphedMat, dilateSize);

		return morphedMat;
	}

	void filterRedBlobs(POBR::Blobs& blobs)
	{
		auto sizeThreshold = 100;
		blobs.filterBlobsBySize(sizeThreshold);

		// TODO
		auto huMin = POBR::HuMoments{ -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0 };
		auto huMax = POBR::HuMoments{ 10, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0 };
		blobs.filterBlobsByHuMoments(huMin, huMax);
	}
}