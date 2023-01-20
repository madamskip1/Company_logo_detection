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

	POBR::Blobs prepareRedBlobs(cv::Mat& hsvMat)
	{
		std::cout << "--POBR::Prepare red blobs --- start" << std::endl;

		auto thresholdedMat = thresholdRed(hsvMat);
		auto morphedOpenMat = morphOpenRed(thresholdedMat);
		auto blobs = POBR::detectBlobs(morphedOpenMat);
		filterRedBlobs(blobs);

		std::cout << "--POBR::Prepare red blobs --- end" << std::endl;
		return blobs;
	}

	cv::Mat thresholdRed(cv::Mat& hsvMat)
	{
		std::cout << "----POBR::Prepare red blobs::Threshold --- start" << std::endl;
		auto hRange = POBR::ColorRange{ 165, 10 };
		auto sRange = POBR::ColorRange{ 70, 255 };
		auto vRange = POBR::ColorRange{ 70, 255 };

		auto thresholdedMat = POBR::thresholdByHSV(hsvMat, { hRange, sRange, vRange });
		std::cout << "----POBR::Prepare red blobs::Threshold --- end" << std::endl;
		return thresholdedMat;
	}

	cv::Mat morphOpenRed(cv::Mat& binaryMat)
	{
		std::cout << "----POBR::Prepare red blobs::Morphological operations --- start" << std::endl;
		auto erodeSize{ 3 };
		auto dilateSize{ 3 };

		auto morphedMat = POBR::erode(binaryMat, erodeSize);
		morphedMat = POBR::dilate(morphedMat, dilateSize);
		std::cout << "----POBR::Prepare red blobs::Morphological operations --- end" << std::endl;
		return morphedMat;
	}

	void filterRedBlobs(POBR::Blobs& blobs)
	{
		std::cout << "----POBR::Prepare red blobs::filter --- start, blobs: " << blobs.getBlobs().size() << std::endl;

		std::cout << "------POBR::Prepare red blobs::filter::by size --- start" << std::endl;
		auto sizeMin{ 1000 };
		auto sizeMax{ 200000 };
		blobs.filterBySize(sizeMin, sizeMax);
		std::cout << "------POBR::Prepare red blobs::filter::by size --- end, blobs: " << blobs.getBlobs().size() << std::endl;

		std::cout << "------POBR::Prepare red blobs::filter::by edge ratio --- start" << '\n';;
		auto ratioMin{ 0.65 };
		auto ratioMax{ 1.0 };
		blobs.filterByEdgeRatio(ratioMin, ratioMax);
		std::cout << "------POBR::Prepare red blobs::filter::by edge ratio --- end, blobs: " << blobs.getBlobs().size() << std::endl;


		// TODO
		std::cout << "------POBR::Prepare red blobs::filter::by HuMoments --- start" << std::endl;
		auto huMin = POBR::HuMoments{
			0.16,			// Hu_0
			0.00013,		// Hu_1
			0.00008,		// Hu_2
			0.00000082,		// Hu_3
			-0.000000015,	// Hu_4
			-0.0000018,		// Hu_5
			0.0064,			// Hu_6
			-0.0012,			// Hu_7
			-0.00012,			// Hu_8
			-0.000053			// Hu_9
		};
		auto huMax = POBR::HuMoments{
			0.43,			// Hu_0
			0.097,			// Hu_1
			0.02,			// Hu_2
			0.009,			// Hu_3
			0.00015,		// Hu_4
			0.0031,			// Hu_5
			0.021,			// Hu_6
			0.00001,		// Hu_7
			0.00001,		// Hu_8
			0.0000039		// Hu_9
		};
		blobs.filterByHuMoments(huMin, huMax);
		std::cout << "------POBR::Prepare red blobs::filter:by HuMoments --- end, blobs: " << blobs.getBlobs().size() << std::endl;

		std::cout << "----POBR::Prepare red blobs::filter --- end" << std::endl;
	}
}