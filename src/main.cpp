#include <opencv2/opencv.hpp>

#include "ColorConverter.h"
#include "Blobs.h"
#include "MomentsCalculator.h"
#include "FilterImage.h"
#include "FilterMasks.h"
#include "MedianFilter.h"
#include "PrepareRedBlobs.h"
#include "PrepareBlueBlobs.h"
#include "mergeBlobs.h"

int main()
{
    auto imagesNames = { "all_in_one", "all_in_one_90", "all_in_one_180", "all_in_one_mirror" };

    for (const auto& imageName : imagesNames)
    {
        std::cout << "POBR::" + std::string(imageName) + "--- start" << std::endl;

        auto filePath = "img/pepsi_logo/" + std::string(imageName) + ".jpg";
        cv::Mat img = cv::imread(filePath/*, cv::IMREAD_COLOR*/);

        auto medianImg = POBR::filterMedian(img, 3);
        auto sharpenMask = POBR::getSharpenMask();
        auto sharpenImg = POBR::filterImage(medianImg, sharpenMask);
        auto HSVMat = POBR::convertBGRToHSV(sharpenImg);
        auto blueBlobs = POBR::prepareBlueBlobs(HSVMat);
        auto redBlobs = POBR::prepareRedBlobs(HSVMat);
        auto mergedBlobs = POBR::mergeBlobs(redBlobs, blueBlobs);
        mergedBlobs.draw(img);

        auto saveFilePath = "img/results/final_detections/" + std::string(imageName) + ".jpg";
        cv::imwrite(saveFilePath, img);

        std::cout << "POBR::" + std::string(imageName) + "--- end" << std::endl;
        std::cout << "_____________________" << std::endl;
    }

    cv::waitKey(0);
    return 0;
}