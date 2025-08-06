#pragma once
#include "QBScene.hpp"
#include "QBObjectSphere.hpp"
#include "QBPointLight.hpp"

void AddSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList, 
				const qbVector3<double>& vTranslation,
				const qbVector3<double>& vRotation,
				const qbVector3<double>& vScaling,
				const qbVector3<double>& vColour)
{
	std::shared_ptr<QBRT::QBObjectSphere> objSphere = std::make_shared<QBRT::QBObjectSphere>();
	vObjectList.push_back(objSphere);
	{
		QBRT::QBObjectSphere* pObj = objSphere.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->m_vBaseColour = vColour;
	}
}

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

	// Construct a test sphere.
	AddSphere(m_vObjectList, qbVector3<double>(-1.5, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.5, 0.5, 0.75),		qbVector3<double>(64.0/255.0, 128.0/255.0, 200.0/255.0));
	AddSphere(m_vObjectList, qbVector3<double>(0.0, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.75, 0.5, 0.5),		qbVector3<double>(255.0 / 255.0, 128.0 / 255.0, 0.0 / 255.0));
	AddSphere(m_vObjectList, qbVector3<double>(1.5, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.75, 0.75, 0.75),	qbVector3<double>(255.0 / 255.0, 200.0 / 255.0, 0.0 / 255.0));

	// Construct a test light.
	m_vLightList.push_back(std::make_shared<QBRT::QBPointLight>());
	{
		m_vLightList.at(0)->m_vLightPosition = qbVector3<double>(5.0, -10.0, -5.0);
		m_vLightList.at(0)->m_vLightColour = qbVector3<double>(1.0, 1.0, 1.0);
	}
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

			// Test for intersections with all objects in the scene.
			for (auto pCurrentObject : m_vObjectList)
			{
				// Test if we have a valid intersection.
				bool bValidIntersection = pCurrentObject->TestIntersection(	cameraRay, 
																			vIntersectionPoint, 
																			vLocalNormal, 
																			vLocalColour);
				
				// If we have a valid intersection, change pixel color as per the light intensity.
				if (bValidIntersection)
				{
					// Compute intensity of illumination.
					double				fLightIntensity = 0.0;
					qbVector3<double>	vColour;
					bool				bValidIllumination = false;

					for (auto pCurrentLight : m_vLightList)
					{
						bValidIllumination = pCurrentLight->ComputeIllumination(	vIntersectionPoint,
																					vLocalNormal, 
																					m_vObjectList, 
																					pCurrentObject,
																					vColour, 
																					fLightIntensity);
					}
					
					if (bValidIllumination)
					{
						outputImage.SetPixel(	x, y, 
												vLocalColour.r * fLightIntensity, 
												vLocalColour.g * fLightIntensity, 
												vLocalColour.b * fLightIntensity);
					}
				}
			}
		}
	}

	return true;
}

