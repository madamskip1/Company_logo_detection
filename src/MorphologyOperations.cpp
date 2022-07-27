#include "MorphologyOperations.h"
#include <algorithm>

static cv::Mat morph(const cv::Mat& inMat, const int size, const int kernelValue)
{
    CV_Assert(inMat.channels() == 1);
    CV_Assert(size % 2 != 0);

    int rows = inMat.rows;
    int columns = inMat.cols;
    int kernelCenter = size / 2;

    auto outMat = inMat.clone();

    for (int y = 0; y < rows; ++y)
    {
        int inMatStartY = std::clamp(y - kernelCenter, 0, rows - 1);
        int inMatEndY = std::clamp(y + kernelCenter, 0, rows - 1);

        auto outMatRow = outMat.ptr<uchar>(y);

        for (int x = 0; x < columns; ++x)
        {
            if (outMatRow[x] != kernelValue)
            {
                int inMatStartX = std::clamp(x - kernelCenter, 0, columns - 1);
                int inMatEndX = std::clamp(x + kernelCenter, 0, columns - 1);

                for (auto kernelY = inMatStartY; kernelY <= inMatEndY; kernelY++)
                {
                    auto inMatRow = inMat.ptr<uchar>(kernelY);

                    for (auto kernelX = inMatStartX; kernelX <= inMatEndX; kernelX++)
                    {
                        if (inMatRow[kernelX] == kernelValue)
                        {
                            outMatRow[x] = kernelValue;

                            kernelY = inMatEndY + 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    return outMat;
}

cv::Mat erode(const cv::Mat& inMat, const int size)
{
    return morph(inMat, size, 0);
}

cv::Mat dilate(const cv::Mat& inMat, const int size)
{
    return morph(inMat, size, 255);
}

