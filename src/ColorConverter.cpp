#include "ColorConverter.h"

cv::Mat ColorConverter::convertBGRToRGB(const cv::Mat& inMat)
{
    CV_Assert(inMat.channels() == 3);

    int rows = inMat.rows;
    int columns = inMat.cols * inMat.channels();

    cv::Mat newMat = inMat.clone();
    uchar* row;

    for (int y = 0; y < rows; y++)
    {
        row = newMat.ptr<uchar>(y);

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

    return newMat;
}
