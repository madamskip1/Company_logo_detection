#include <opencv2/opencv.hpp>
#include <iostream>

#include "ColorConverter.h"
#include "ColorThresholding.h"
#include "MorphologyOperations.h"
#include "BlobsDetection.h"
#include "HuMoments.h"
#include "MomentsCalculator.h"

int main()
{
    calcMumentsRange("img/moments_logo/niebieskie_1.jpg");
    //cv::Mat img = cv::imread("img/test.jpg"/*, cv::IMREAD_COLOR*/);
    //cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    //cv::imshow("test", img);

    //auto HSVMat = POBR::convertBGRToHSV(img);
    //auto thresholdedMoje = POBR::thresholdByHSV(img, { {10, 50}, {100, 150}, {100, 255} });
    //cv::imshow("moje", thresholdedMoje);

    //auto morphed = POBR::dilate(thresholdedMoje, 3);


    //cv::imshow("morph", morphed);

    //auto blobs = POBR::detectBlobs(morphed);

    //for (auto& blob : blobs)
    //{
    //    blob.draw(img);
    //}
    //cv::imshow("test2", img);


    //uchar arr[9][7][1] = {
    //        {0,0,0,0,0,0,0},
    //        {0,255,0,0,0,255,0},
    //        {0,255,0,0,255,0,0},
    //        {0,255,0,255,0,0,0},
    //        {0,255,255,0,0,0,0},
    //        {0,255,0,255,0,0,0},
    //        {0,255,0,0,255,0,0},
    //        {0,255,0,0,0,255,0},
    //        {0,0,0,0,0,0,0},
    //};
    //auto mat = cv::Mat(9, 7, CV_8UC1, &arr);
    //blobs = POBR::detectBlobs(mat);
    //auto blob = blobs[0];
    //auto huMoments = POBR::HuMoments::calcHuMoments(blob);
    //huMoments.print();

    //img = cv::imread("img/diamond.png", cv::IMREAD_COLOR);
    //cv::imshow("test", img);
    //auto imgHSV = POBR::convertBGRToHSV(img);
    //auto thresholdedDiamond = POBR::thresholdByHSV(img, { {100, 255}, {0, 255}, {0, 255} });
    //cv::imshow("DUPA", thresholdedDiamond);
    //cv::waitKey(0);
    //blobs = POBR::detectBlobs(thresholdedDiamond);
    //blob = blobs[0];
    //huMoments = POBR::HuMoments::calcHuMoments(blob);
    //huMoments.print();


    cv::waitKey(0);
    return 0;
}