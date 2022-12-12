#include <opencv2/opencv.hpp>
#include <iostream>

#include "ColorConverter.h"
#include "ColorThresholding.h"
#include "MorphologyOperations.h"
#include "BlobsDetection.h"


int main()
{
    cv::Mat img = cv::imread("img/test.jpg"/*, cv::IMREAD_COLOR*/);
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("test", img);

    auto HSVMat = POBR::convertBGRToHSV(img);
    auto thresholdedMoje = POBR::thresholdByHSV(img, { {10, 50}, {100, 150}, {100, 255} });
    cv::imshow("moje", thresholdedMoje);
 
    auto morphed = POBR::dilate(thresholdedMoje, 3);


    cv::imshow("morph", morphed);

    auto blobs = POBR::detectBlobs(morphed);

    for (auto& blob : blobs)
    {
        blob.draw(img);
    }
    cv::imshow("test2", img);
    cv::waitKey(0);
    return 0;
}