#pragma once
#include "QBScene.hpp"

// The constructor.
QBRT::QBScene::QBScene()
{

}

// Function to perform the renderering.
bool QBRT::QBScene::Render(QBImage& outputImage)
{
	// Get the dimensions of the output image.
	uint32_t xSize = outputImage.GetXSize();
	uint32_t ySize = outputImage.GetYSize();

	// Create some colour variations.
	// Create some colour variations.
	for (uint32_t y = 0; y < ySize; y++)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
	
		for (uint32_t x = 0; x < xSize; x++)
		{
			double red = (x * 1.0f / xSize);
			double green = (y * 1.0f / ySize);
			outputImage.SetPixel(x, y, red, green, 0);
		}
	}

	return true;
}

