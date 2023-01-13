#include "ColorThresholding.h"

namespace POBR
{
    static bool checkIfColorInRange(uchar color, const ColorRange& colorRange)
    {
        if (colorRange.min > colorRange.max)
        {
            if (color > colorRange.max && color < colorRange.min)
            {
                return false;
            }
            return true;
        }

        if (color < colorRange.min || color > colorRange.max)
        {
            return false;
        }

        return true;
    }

    cv::Mat thresholdByHSV(cv::Mat& inMat, const std::vector<ColorRange>& colorRanges)
    {
        assert(inMat.channels() == colorRanges.size());

        int rows = inMat.rows;
        int columns = inMat.cols;
        int channels = inMat.channels();

        cv::Mat thresholdedMat = cv::Mat1b::zeros(rows, columns);

        for (int y = 0; y < rows; y++)
        {
            uchar* inMatRow = inMat.ptr<uchar>(y);
            uchar* thresholdedMatRow = thresholdedMat.ptr<uchar>(y);

            for (int x = 0; x < columns; ++x)
            {
                int inMatX = x * channels;
                bool inRange = true;

                for (int channel = 0; channel < channels; ++channel)
                {
                    int index = inMatX + channel;
                    const ColorRange& colorRange = colorRanges[channel];

                    if (!checkIfColorInRange(inMatRow[index], colorRange))
                    {
                        inRange = false;
                        break;
                    }
                }

                if (inRange)
                {
                    thresholdedMatRow[x] = 255;
                }
                else
                {
                    thresholdedMatRow[x] = 0;
                }
            }
        }

        return thresholdedMat;
    }
}