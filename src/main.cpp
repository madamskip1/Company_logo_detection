#include <opencv2/opencv.hpp>

#include "SampleClass.h"

int main()
{
    SampleClass sample;
    sample.testMe();

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    cv::waitKey(0);
    return 0;
}