#pragma once
#include "QBScene.hpp"
#include "qbMaterials/QBSimpleMaterial.hpp"
#include "qbPrimitives/QBCylinder.hpp"
#include "qbPrimitives/QBCone.hpp"
#include "qbPrimitives/QBBox.hpp"
#include "qbTextures/QBCheckeredTexture.hpp"
#include "qbTextures/QBImageTexture.hpp"
#include "qbMaterials/QBSimpleRefractive.hpp"

// The constructor.
QBRT::QBScene::QBScene()
{
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_Camera.SetPosition(MAKE_POSITION(3.0, -5.0, 0.25));
	m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
	m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
	m_Camera.SetHorizontalSize(1.0);
	m_Camera.SetAspect(ASPECT_RATIO);
	m_Camera.UpdateCameraGeometry();

	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	QBRT::QBMaterialBase::m_vAmbientColour = qbVector3<double>(1.0, 1.0, 1.0);
	QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

	// Create some textures.
	auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
	{
		floorTexture->SetTransform(	MAKE_POSITION(0.0, 0.0, 0.0),
									0.0,
									MAKE_SCALE(16.0, 16.0, 0.0));
	}

	auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
	{
		imageTexture->LoadImage("C:\\GitHub\\aalekhm\\RayTracing\\RT_QBRay\\Content\\charlie.bmp");
		imageTexture->SetTransform(	MAKE_POSITION(0.0, 0.0, 0.0),
									0.0,
									MAKE_SCALE(1.0, 1.0, 0.0));
	}
	
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0), 0.25, 0.0);
	{
		pMatFloor->AssignTexture(floorTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125), 0.0, 0.0);
	{
		pMatImage->AssignTexture(imageTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereRed = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2), 0.8, 32.0);
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereGreen = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2), 0.8, 32.0);
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereBlue = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0), 0.8, 32.0);
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatConeBlue = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.7), 0.2, 1.0);
	std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass = MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2), 0.25, 32.0, 0.75, 1.33);
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatBoxYellow = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2), 0.15, 32.0);

	// Floor Plane
	QBRT::QBUtils::AddPlane(	m_vObjectList,
								MAKE_POSITION(0.0, 0.0, 1.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(16.0, 16.0, 1.0),
								pMatFloor);

	// Image Plane
	QBRT::QBUtils::AddPlane(	m_vObjectList,
								MAKE_POSITION(2.0, 5.0, -0.75),
								MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
								MAKE_SCALE(1.75, 1.75, 1.0),
								pMatImage);

	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(-2.0, -2.0, 0.25),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.75, 0.75, 0.75),
								pMatSphereRed);

	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(-2.0, -0.5, 0.25),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.75, 0.75, 0.75),
								pMatSphereGreen);

	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(-2.0, -1.25, -1.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.75, 0.75, 0.75),
								pMatSphereBlue);
	/*
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(2.0, -1.25, 0.25),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.75, 0.75, 0.75),
								pMatGlass);

	QBRT::QBUtils::AddCone(		m_vObjectList, 
								MAKE_POSITION(0.0, -3.0, 0.5),
								MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
								MAKE_SCALE(0.75, 0.75, 2.0),
								pMatConeBlue);
	//*/
	QBRT::QBUtils::AddBox(		m_vObjectList, 
								MAKE_POSITION(0.0, 0.0, 0.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 2.0, 1.0),
								pMatBoxYellow);

	// Construct a test light.
	QBRT::QBUtils::AddLight(	m_vLightList,	
								MAKE_POSITION(3.0, -10.0, -5.0),	
								MAKE_COLOUR(1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
	QBRT::QBUtils::AddLight(	m_vLightList,	
								MAKE_POSITION(0.0, -10.0, -5.0),	
								MAKE_COLOUR(1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
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
			QBUtils::m_iCurrentPixelX = x;
			QBUtils::m_iCurrentPixelY = y;

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

			bool bIntersectionFound = CastRay(cameraRay, m_vObjectList, nullptr, pClosestObject, vClosestIntersectionPoint, vClosestLocalNormal, vClosestLocalColour);

			// Compute the illumination for the closest object, assuming that there
			// was a valid intersection.
			if (bIntersectionFound)
			{
				qbVector3<double> vFinalColour;

				// Check if the object has a material.
				if (pClosestObject->m_bHasMaterial)
				{
					// Use the material to compute the color.
					QBRT::QBMaterialBase::m_iMaxReflectionRayCount = 0;
					vFinalColour = pClosestObject->m_pMaterial->ComputeColour(	m_vObjectList,
																				m_vLightList, 
																				pClosestObject, 
																				vClosestIntersectionPoint, 
																				vClosestLocalNormal, 
																				cameraRay);
				}
				else
				{
					// Use the basic method to compute the color.
					vFinalColour = QBRT::QBMaterialBase::ComputeDiffuseColour(	m_vObjectList,
																				m_vLightList, 
																				pClosestObject, 
																				vClosestIntersectionPoint, 
																				vClosestLocalNormal, 
																				pClosestObject->m_vBaseColour);
				}

				outputImage.SetPixel(	x, y, 
										vFinalColour.r,
										vFinalColour.g,
										vFinalColour.b);
			}
		}
	}


	return true;
}

bool QBRT::QBScene::CastRay(	QBRT::QBRay& castRay,
								const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const std::shared_ptr<QBRT::QBObjectBase>& pThisObject,
								std::shared_ptr<QBRT::QBObjectBase>& pClosestObject,
								qbVector3<double>& vClosestIntersectionPoint,
								qbVector3<double>& vClosestLocalNormal,
								qbVector3<double>& vClosestLocalColour)
{
	qbVector3<double>	vIntersectionPoint;
	qbVector3<double>	vLocalNormal;
	qbVector3<double>	vLocalColour;
	double				fMinDist = 1e6;
	bool				bIntersectionFound = false;

	for (auto pCurrentObject : vObjectList)
	{
		if(pCurrentObject != pThisObject)
		{
			// Test if we have a valid intersection.
			bool bValidIntersection = pCurrentObject->TestIntersection(	castRay,
																		vIntersectionPoint,
																		vLocalNormal,
																		vLocalColour);

			// If we have a valid intersection.
			if (bValidIntersection)
			{
				// Set the flag to indicate that we found an intersection.
				bIntersectionFound = true;

				// Compute the distance between the camera and the point of intersection.
				double fDistance = (vIntersectionPoint - castRay.m_vPoint1).norm();

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
	}

	return bIntersectionFound;
}