#include "PrepareBlueBlobs.h"
#include "ColorThresholding.h"
#include "MorphologyOperations.h"
#include "BlobsDetection.h"
#include "HuMoments.h"

#include <opencv2/opencv.hpp>

namespace POBR
{
	cv::Mat thresholdBlue(cv::Mat& hsvMat);
	cv::Mat morphOpenBlue(cv::Mat& binaryMat);
	void filterBlueBlobs(POBR::Blobs& blobs);

	POBR::Blobs prepareBlueBlobs(cv::Mat& hsvMat)
	{
		auto thresholdedMat = thresholdBlue(hsvMat);
		auto morphedOpenMat = morphOpenBlue(thresholdedMat);
		cv::Mat resizedImg;
		cv::resize(morphedOpenMat, resizedImg, cv::Size{ 800, 600 });
		cv::imshow("MorphedProc", resizedImg);

		auto blobs = POBR::detectBlobs(morphedOpenMat);
		filterBlueBlobs(blobs);

		auto toDraw = hsvMat.clone();
		blobs.draw(toDraw);
		cv::imwrite("test_blue.jpg", toDraw);

		return blobs;
	}

	cv::Mat thresholdBlue(cv::Mat& hsvMat)
	{
		auto hRange = POBR::ColorRange{ 95, 130 };
		auto sRange = POBR::ColorRange{ 50, 255 };
		auto vRange = POBR::ColorRange{ 50, 255 };

		auto thresholdedMat = POBR::thresholdByHSV(hsvMat, { hRange, sRange, vRange });

		return thresholdedMat;
	}

	cv::Mat morphOpenBlue(cv::Mat& binaryMat)
	{
		auto erodeSize{ 3 };
		auto dilateSize{ 3 };

		auto morphedMat = POBR::erode(binaryMat, erodeSize);
		morphedMat = POBR::dilate(morphedMat, dilateSize);

		return morphedMat;
	}

	void filterBlueBlobs(POBR::Blobs& blobs)
	{
		auto sizeThreshold = 100;
		blobs.filterBlobsBySize(sizeThreshold);

		// TODO
		auto huMin = POBR::HuMoments{ -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0 };
		auto huMax = POBR::HuMoments{ 10, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0 };
		blobs.filterBlobsByHuMoments(huMin, huMax);
	}
}