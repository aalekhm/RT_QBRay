#pragma once
#include "QBScene.hpp"

// The constructor.
QBRT::QBScene::QBScene()
{
	// Configure the camera.
	m_Camera.SetPosition(qbVector3<double>(0.0, -10.0, 0.0));
	m_Camera.SetLookAt(qbVector3<double>(0.0, 0.0, 0.0));
	m_Camera.SetUp(qbVector3<double>(0.0, 0.0, 1.0));
	m_Camera.SetHorizontalSize(0.25);
	m_Camera.SetAspect(16.0 / 9.0);
	m_Camera.UpdateCameraGeometry();
}

// Function to perform the renderering.
bool QBRT::QBScene::Render(QBImage& outputImage)
{
	// Get the dimensions of the output image.
	uint32_t xSize = outputImage.GetXSize();
	uint32_t ySize = outputImage.GetYSize();

	// Loop over each pixel in our image.
	QBRT::QBRay cameraRay;
	qbVector3<double> vIntersectionPoint;
	qbVector3<double> vLocalNormal;
	qbVector3<double> vLocalColour;
	double xPixelFactor = 1.0 / (static_cast<double>(xSize) / 2.0);	// Screen Pixel value between: 0.0 < pixelX < 2.0
	double yPixelFactor = 1.0 / (static_cast<double>(ySize) / 2.0);	// Screen Pixel value between: 0.0 < pixelY < 2.0
	double minDist = 1e6;
	double maxDist = 0.0;

	for (uint32_t y = 0; y < ySize; y++)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
	
		for (uint32_t x = 0; x < xSize; x++)
		{
			// Normalize the x and y coordinates between: -1.0 < pixel < 1.0
			double normPixelX = (static_cast<double>(x) * xPixelFactor) - 1.0; // Normalized screen pixel value between: -1.0 < pixelX < 1.0
			double normPixelY = (static_cast<double>(y) * yPixelFactor) - 1.0; // Normalized screen pixel value between: -1.0 < pixelX < 1.0

			// Generate the ray for this pixel.
			m_Camera.GenerateRay(static_cast<float>(normPixelX), static_cast<float>(normPixelY), cameraRay);

			// Test if we have a valid intersection.
			bool bValidIntersection = m_TestSphere.TestIntersection(cameraRay, vIntersectionPoint, vLocalNormal, vLocalColour);

			// If we have a valid intersection, change pixel color to red.
			if (bValidIntersection)
			{
				// Compute the distance between the camera and the point of intersection.
				double fIntersectionDistance = (vIntersectionPoint - cameraRay.m_vPoint1).norm();
				if (fIntersectionDistance > maxDist)
				{
					maxDist = fIntersectionDistance;
				}

				if (fIntersectionDistance < minDist)
				{
					minDist = fIntersectionDistance;
				}

				// Since camera is set at 10 units away from the unit sphere at the origin,
				// normalize value of 'R' related to some factor of intersection distance
				double r = 1.0 - ((fIntersectionDistance - 9.0) / 0.94605);
				outputImage.SetPixel(x, y, r, 0.0, 0.0);
			}
			else
			{
				outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}
	}

	std::cout << "Minimum Distance: " << minDist << std::endl;
	std::cout << "Maximum Distance: " << maxDist << std::endl;

	return true;
}

