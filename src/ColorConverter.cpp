#include "ColorConverter.h"

cv::Mat ColorConverter::convertBGRToRGB(const cv::Mat& inMat)
{
    CV_Assert(inMat.channels() == 3);

    int rows = inMat.rows;
    int columns = inMat.cols * inMat.channels();

    cv::Mat RGBMat = inMat.clone();

    for (int y = 0; y < rows; y++)
    {
        uchar* row = RGBMat.ptr<uchar>(y);

        for (int x = 0; x < columns; x = x + 3)
        {
            uchar b = row[x];
            uchar g = row[x + 1];
            uchar r = row[x + 2];

            row[x] = r;
            row[x + 1] = g;
            row[x + 2] = b;
        }
    }

    return RGBMat;
}

cv::Mat ColorConverter::convertBGRToHSV(const cv::Mat& inMat)
{
    CV_Assert(inMat.channels() == 3);

    int rows = inMat.rows;
    int columns = inMat.cols * inMat.channels();

    cv::Mat HSVMat = inMat.clone();
    
    for (int y = 0; y < rows; y++)
    {
        uchar* row = HSVMat.ptr<uchar>(y);

        for (int x = 0; x < columns; x = x + 3)
        {
            double b = (double)row[x];
            double g = (double)row[x + 1];
            double r = (double)row[x + 2];

            double min = std::min({ b, g, r });
            double max = std::max({ b, g, r });
           
            double hue = calcHue(b, g, r, min, max);
            double saturation = calcSaturation(min, max);
            double value = max;

            row[x] = (uchar)hue;
            row[x + 1] = (uchar)saturation;
            row[x + 2] = (uchar)value;
        }
    }

    return HSVMat;
}

int ColorConverter::calcHue(const double& b, const double& g, const double& r, const double& min, const double& max)
{
    if (max == min)
    {
        return 0;
    }

    double hue{ 0.0 };
    double delta = max - min;

    if (max == r)
    {
        hue = (g - b) / delta;
    }
    else if (max == g)
    {
        hue = (b - r) / delta;
        hue += 2;
    }
    else if (max == b)
    {
        hue = (r - g) / delta;
        hue += 4;
    }

    hue *= 30;

    if (hue < 0)
    {
        hue += 180;
    }

    return static_cast<int>(hue);
}

int ColorConverter::calcSaturation(const double& min, const double& max)
{
    if (max == 0)
    {
        return 0;
    }

    double saturation = (max - min) / max * 255.0;
    return static_cast<int>(saturation);
}
