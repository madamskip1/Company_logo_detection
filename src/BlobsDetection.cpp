#include "BlobsDetection.h"

#include <queue>
#include "Blob.h"

namespace POBR
{
    static void addPixelNeighborsToCheck(const cv::Point2i pixel, std::queue<cv::Point2i>& pixelsToCheck, cv::Mat& inMat)
    {
        int rows = inMat.rows;
        int columns = inMat.cols;

        for (int y = pixel.y - 1; y <= pixel.y + 1; ++y)
        {
            if (y >= 0 && y < rows)
            {
                auto inMatRow = inMat.ptr<uchar>(y);

                for (int x = pixel.x - 1; x <= pixel.x + 1; ++x)
                {
                    if (x >= 0 && x < columns)
                    {
                        if (inMatRow[x] == 255)
                        {
                            inMatRow[x] = 0;
                            pixelsToCheck.emplace(cv::Point2i(x, y));
                        }
                    }
                }
            }
        }
    }

    POBR::Blobs detectBlobs(cv::Mat inMat)
    {
        CV_Assert(inMat.channels() == 1);
        std::cout << "--POBR::Blobs detection --- start" << std::endl;
        auto blobs = POBR::Blobs{};

        std::queue<cv::Point2i> pixelsToCheck;

        int rows = inMat.rows;
        int columns = inMat.cols;

        for (int y = 0; y < rows; y++)
        {
            auto inMatRow = inMat.ptr<uchar>(y);

            for (int x = 0; x < columns; ++x)
            {
                if (inMatRow[x] == 255)
                {
                    Blob blob;
                    pixelsToCheck.emplace(cv::Point2i(x, y));
                    inMatRow[x] = 0;

                    while (!pixelsToCheck.empty())
                    {
                        auto pixel = pixelsToCheck.front();
                        pixelsToCheck.pop();
                        blob.addPoint(pixel);

                        addPixelNeighborsToCheck(pixel, pixelsToCheck, inMat);
                    }

                    blobs.addBlob(blob);
                }
            }
        }
        std::cout << "--POBR::Blobs detection --- end" << std::endl;
        return blobs;
    }
}
