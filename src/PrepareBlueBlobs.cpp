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
		std::cout << "--POBR::Prepare blue blobs --- start" << std::endl;
		
		auto thresholdedMat = thresholdBlue(hsvMat);
		auto morphedOpenMat = morphOpenBlue(thresholdedMat);
		auto blobs = POBR::detectBlobs(morphedOpenMat);
		filterBlueBlobs(blobs);
		
		std::cout << "--POBR::Prepare blue blobs --- end" << std::endl;

		return blobs;
	}

	cv::Mat thresholdBlue(cv::Mat& hsvMat)
	{
		std::cout << "----POBR::Prepare blue blobs::Threshold --- start" << std::endl;

		auto hRange = POBR::ColorRange{ 95, 130 };
		auto sRange = POBR::ColorRange{ 50, 254 };
		auto vRange = POBR::ColorRange{ 50, 254 };
		auto thresholdedMat = POBR::thresholdByHSV(hsvMat, { hRange, sRange, vRange });
		
		std::cout << "----POBR::Prepare blue blobs::Threshold --- end" << std::endl;

		return thresholdedMat;
	}

	cv::Mat morphOpenBlue(cv::Mat& binaryMat)
	{
		std::cout << "----POBR::Prepare blue blobs::Morphological operations --- start" << std::endl;
		
		auto erodeSize{ 5 };
		auto dilateSize{ 5 };
		auto morphedMat = POBR::erode(binaryMat, erodeSize);
		morphedMat = POBR::dilate(morphedMat, dilateSize);
		
		std::cout << "----POBR::Prepare blue blobs::Morphological operations --- end" << std::endl;
		
		return morphedMat;
	}

	void filterBlueBlobs(POBR::Blobs& blobs)
	{
		std::cout << "----POBR::Prepare blue blobs::filter --- start, blobs: " << blobs.getBlobs().size() << std::endl;
		
		std::cout << "------POBR::Prepare blue blobs::filter::by size --- start" << std::endl;
		auto sizeMin{ 300 };
		auto sizeMax{ 75000 };
		blobs.filterBySize(sizeMin, sizeMax);
		std::cout << "------POBR::Prepare blue blobs::filter::by size --- end, blobs: " << blobs.getBlobs().size() << std::endl;

		std::cout << "------POBR::Prepare blue blobs::filter::by edge ratio --- start" << std::endl;
		auto ratioMin{ 0.40 };
		auto ratioMax{ 0.95 };
		blobs.filterByEdgeRatio(ratioMin, ratioMax);
		std::cout << "------POBR::Prepare blue blobs::filter::by edge ratio --- end, blobs: " << blobs.getBlobs().size() << std::endl;


		auto huMin = POBR::HuMoments{
			0.2,			// Hu_0
			0.014, 			// Hu_1
			0.0015,			// Hu_2
			0.00015, 		// Hu_3
			-0.000015, 		// Hu_4
			-0.004, 		// Hu_5
			0.007, 			// Hu_6
			-0.0027, 		// Hu_7
			-0.000086, 		// Hu_8
			-0.0003 		// Hu_9
		};
		auto huMax = POBR::HuMoments{
			0.43,			// Hu_0
			0.135,			// Hu_1
			0.26,			// Hu_2
			0.0061,			// Hu_3
			0.00005,		// Hu_4
			0.0006,			// Hu_5
			0.015,			// Hu_6
			0.00001,		// Hu_7
			0.00001,		// Hu_8
			0.00033			// Hu_9
		};
		std::cout << "------POBR::Prepare blue blobs::filter::by HuMoments --- start" << std::endl;
		blobs.filterByHuMoments(huMin, huMax);
		std::cout << "------POBR::Prepare blue blobs::filter::by HuMoments --- end, blobs: " << blobs.getBlobs().size() << std::endl;


		std::cout << "----POBR::Prepare blue blobs::filter --- end, blobs: " << blobs.getBlobs().size() << std::endl;
	}
}