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

    ColorConverter colorConverter;
    ColorThresholding colorThresholding;
    auto HSVMat = colorConverter.convertBGRToHSV(img);
    auto thresholdedMoje = colorThresholding.threshold(img, { {10, 50}, {100, 150}, {100, 255} });
    cv::imshow("moje", thresholdedMoje);

    MorphologyOperations morph;
  

    auto dupa = morph.dilate(thresholdedMoje, 3);


    cv::imshow("dupa", dupa);

    auto blobs = detectBlobs(dupa);

    for (auto& blob : blobs)
    {
        blob.draw(img);
    }
    cv::imshow("test2", img);
    cv::waitKey(0);
    return 0;
}