#include "mergeBlobs.h"

POBR::Blobs POBR::mergeBlobs(const POBR::Blobs& redBlobs, const POBR::Blobs& blueBlobs)
{
	auto overlapError{ 5 };

	std::cout << "--POBR::Merge blobs --- start" << std::endl;
	auto newBlobs = POBR::Blobs{};
	auto& redBlobsVector = redBlobs.getBlobs();
	auto& blueBlobsVector = blueBlobs.getBlobs();

	for (const auto& redBlob : redBlobsVector)
	{
		auto redBlobCorners = redBlob.getCorners();
		auto redBlobLeftCorner = redBlobCorners.first;
		auto redBlobRightCorner = redBlobCorners.second;

		for (const auto& blueBlob : blueBlobsVector)
		{
			auto blueBlobCorners = blueBlob.getCorners();
			auto blueBlobLeftCorner = blueBlobCorners.first;
			auto blueBlobRightCorner = blueBlobCorners.second;

			// if overlap
			if (!(	(	(redBlobRightCorner.y + overlapError) < (blueBlobLeftCorner.y - overlapError)	) || (	(blueBlobRightCorner.y + overlapError) < (redBlobLeftCorner.y - overlapError)	) 
				|| ((redBlobRightCorner.x + overlapError) < (blueBlobLeftCorner.x - overlapError)) || ((blueBlobRightCorner.x + overlapError) < (redBlobLeftCorner.x - overlapError))))
			{
				auto newBlob = POBR::Blob::createBlobFromFew({ redBlob, blueBlob });
				newBlobs.addBlob(newBlob);
			}
		}
	}
	std::cout << "--POBR::Merge blobs --- end" << std::endl;
	return newBlobs;
}
