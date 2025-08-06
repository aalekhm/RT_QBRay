#pragma once
#include "QBScene.hpp"
#include "QBObjectSphere.hpp"
#include "QBPointLight.hpp"

uint32_t QBRT::QBScene::m_iCurrentPixelX = 0;
uint32_t QBRT::QBScene::m_iCurrentPixelY = 0;

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

void AddPlane(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
				const qbVector3<double>& vTranslation,
				const qbVector3<double>& vRotation,
				const qbVector3<double>& vScaling,
				const qbVector3<double>& vColour)
{
	std::shared_ptr<QBRT::QBObjectPlane> objPlane = std::make_shared<QBRT::QBObjectPlane>();
	vObjectList.push_back(objPlane);
	{
		QBRT::QBObjectPlane* pObj = objPlane.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->m_vBaseColour = vColour;
	}
}

void AddLight(	std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
				const qbVector3<double>& vPosition,
				const qbVector3<double>& vColour)
{
	std::shared_ptr<QBRT::QBPointLight> objLight = std::make_shared<QBRT::QBPointLight>();
	vLightList.push_back(objLight);
	{
		QBRT::QBPointLight* pObjLight = objLight.get();
		pObjLight->m_vLightPosition = vPosition;
		pObjLight->m_vLightColour = vColour;
	}
}

// The constructor.
QBRT::QBScene::QBScene()
{
	// Configure the camera.
	m_Camera.SetPosition(qbVector3<double>(0.0, -10.0, -1.0));
	m_Camera.SetLookAt(qbVector3<double>(0.0, 0.0, 0.0));
	m_Camera.SetUp(qbVector3<double>(0.0, 0.0, 1.0));
	m_Camera.SetHorizontalSize(0.25);
	m_Camera.SetAspect(16.0 / 9.0);
	m_Camera.UpdateCameraGeometry();

	// Construct a test sphere.
	AddSphere(m_vObjectList, qbVector3<double>(-1.5, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.5, 0.5, 0.75),		qbVector3<double>(0.25, 0.5, 0.8));
	AddSphere(m_vObjectList, qbVector3<double>(0.0, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.75, 0.5, 0.5),		qbVector3<double>(1.0, 0.5, 0.0));
	AddSphere(m_vObjectList, qbVector3<double>(1.5, 0.0, 0.0),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(0.75, 0.75, 0.75),	qbVector3<double>(1.0, 0.8, 0.0));

	// Construct a test plane.
	AddPlane(m_vObjectList, qbVector3<double>(0.0, 0.0, 0.75),		qbVector3<double>(0.0, 0.0, 0.0),	qbVector3<double>(4.0, 4.0, 1.0),		qbVector3<double>(0.5, 0.5, 0.5));

	// Construct a test light.
	AddLight(m_vLightList,	qbVector3<double>(5.0, -10.0, -5.0),		qbVector3<double>(0.0, 0.0, 1.0));
	AddLight(m_vLightList,	qbVector3<double>(-5.0, -10.0, -5.0),		qbVector3<double>(1.0, 0.0, 0.0));
	AddLight(m_vLightList,	qbVector3<double>(0.0, -10.0, -5.0),		qbVector3<double>(0.0, 1.0, 0.0));
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
			m_iCurrentPixelX = x;
			m_iCurrentPixelY = y;

			// Normalize the x and y coordinates between: -1.0 < pixel < 1.0
			double normPixelX = (static_cast<double>(x) * xPixelFactor) - 1.0; // Normalized screen pixel value between: -1.0 < pixelX < 1.0
			double normPixelY = (static_cast<double>(y) * yPixelFactor) - 1.0; // Normalized screen pixel value between: -1.0 < pixelX < 1.0

			// Generate the ray for this pixel.
			m_Camera.GenerateRay(static_cast<float>(normPixelX), static_cast<float>(normPixelY), cameraRay);

			// Test for intersections with all objects in the scene.
			std::shared_ptr<QBRT::QBObjectBase> pClosestObject;
			qbVector3<double>					vClosestIntersectionPoint;
			qbVector3<double>					vClosestLocalNormal;
			qbVector3<double>					vClosestLocalColour;
			double fMinDist = 1e6;
			bool bIntersectionFound = false;

			for (auto pCurrentObject : m_vObjectList)
			{
				// Test if we have a valid intersection.
				bool bValidIntersection = pCurrentObject->TestIntersection(	cameraRay,
																			vIntersectionPoint,
																			vLocalNormal,
																			vLocalColour);

				// If we have a valid intersection.
				if (bValidIntersection)
				{
					// Set the flag to indicate that we found an intersection.
					bIntersectionFound = true;

					// Compute the distance between the camera and the point of intersection.
					double fDistance = (vIntersectionPoint - cameraRay.m_vPoint1).norm();

					// If this object is closer to the camera than any one that we have
					// seen before, then store a reference to it.
					if (fDistance < fMinDist)
					{
						fMinDist = fDistance;
						pClosestObject = pCurrentObject;
						vClosestIntersectionPoint = vIntersectionPoint;
						vClosestLocalNormal = vLocalNormal;
						vClosestLocalColour = vLocalColour;
					}
				}
			}

			// Compute the illumination for the closest object, assuming that there
			// was a valid intersection.
			if (bIntersectionFound)
			{
				// Compute intensity of illumination.
				double				fLightIntensity = 0.0;
				qbVector3<double>	vColour;
				bool				bValidIllumination = false;
				bool				bIlluminationFound = false;
				double				fRed = 0.0, fGreen = 0.0, fBlue = 0.0;

				for (auto pCurrentLight : m_vLightList)
				{
					bValidIllumination = pCurrentLight->ComputeIllumination(	vClosestIntersectionPoint,
																				vClosestLocalNormal, 
																				m_vObjectList, 
																				pClosestObject,
																				vColour, 
																				fLightIntensity);
					if (bValidIllumination)
					{
						bIlluminationFound = true;
						fRed	+= vColour.r * fLightIntensity;
						fGreen	+= vColour.g * fLightIntensity;
						fBlue	+= vColour.b * fLightIntensity;
					}
					else
					{
						bool b = true;
					}
				}

				if (bIlluminationFound)
				{
					fRed	*= vClosestLocalColour.r;
					fGreen	*= vClosestLocalColour.g;
					fBlue	*= vClosestLocalColour.b;

					outputImage.SetPixel(	x, y, 
											fRed, 
											fGreen, 
											fBlue);

				}
			}
		}
	}


	return true;
}

void QBRT::QBScene::PrintVector(const char* sString, const qbVector3<double>& inputVector)
{
	int nRows = inputVector.GetNumDims();
	std::cout << sString << " ";
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << " ";
	}
	std::cout << std::endl;
}

void QBRT::QBScene::PrintVector(const uint32_t iX, const uint32_t iY, const char* sString, const qbVector3<double>& vInputVector)
{
	if (m_iCurrentPixelX == iX && m_iCurrentPixelY == iY)
	{
		PrintVector(sString, vInputVector);
	}
}