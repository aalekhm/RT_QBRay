#pragma once
#include "QBScene.hpp"
#include "qbMaterials/QBSimpleMaterial.hpp"
#include "qbPrimitives/QBCylinder.hpp"
#include "qbPrimitives/QBCone.hpp"
#include "qbPrimitives/QBBox.hpp"
#include "qbRayMarch/QBRMSphere.hpp"
#include "qbRayMarch/QBRMTorus.hpp"
#include "qbRayMarch/QBRMCube.hpp"
#include "qbTextures/QBCheckeredTexture.hpp"
#include "qbTextures/QBImageTexture.hpp"
#include "qbMaterials/QBSimpleRefractive.hpp"
#include "qbTextures/QBBasicGradientNoiseTexture.hpp"
#include "qbTextures/QBBasicValueNoiseTexture.hpp"
#include "qbTextures/QBMarbleTexture.hpp"

// The constructor.
QBRT::QBScene::QBScene()
{
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_Camera.SetPosition(MAKE_POSITION(4.0, -8.0, -2.0));
	m_Camera.SetLookAt(MAKE_POSITION(-0.5, 0.0, 0.0));
	m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
	m_Camera.SetHorizontalSize(1.0);
	m_Camera.SetLength(3.0);
	m_Camera.SetAspect(ASPECT_RATIO);
	m_Camera.UpdateCameraGeometry();

	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
	QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

	// *****************************************************************
	// Create some colour maps.
	// *****************************************************************
	auto noiseMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		noiseMap->SetStop(0.0, MAKE_COLOUR(1.0, 0.4, 0.0, 1.0));
		noiseMap->SetStop(0.5, MAKE_COLOUR(0.2, 0.4, 0.8, 1.0));
		noiseMap->SetStop(1.0, MAKE_COLOUR(1.0, 0.8, 0.0, 1.0));
	}

	auto cloudMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		cloudMap->SetStop(0.0, MAKE_COLOUR(0.2, 0.4, 0.8, 1.0));
		cloudMap->SetStop(0.75, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		cloudMap->SetStop(1.0, MAKE_COLOUR(0.7, 0.7, 0.7, 1.0));
	}

	auto marbleMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		marbleMap->SetStop(0.0, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		marbleMap->SetStop(0.2, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		marbleMap->SetStop(0.5, MAKE_COLOUR(1.0, 0.4, 0.0, 1.0));
		marbleMap->SetStop(0.8, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		marbleMap->SetStop(1.0, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
	}

	auto candyMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		candyMap->SetStop(0.0, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		candyMap->SetStop(0.5, MAKE_COLOUR(1.0, 0.0, 0.0, 1.0));
		candyMap->SetStop(1.0, MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
	}

	auto woodMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		woodMap->SetStop(0.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
		woodMap->SetStop(0.5, MAKE_COLOUR(100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0));
		woodMap->SetStop(1.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
	}

	// *****************************************************************
	// Create some textures.
	// *****************************************************************

	auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
	{
		floorTexture->SetTransform(	MAKE_POSITION(0.0, 0.0, 0.0),
									0.0,
									MAKE_SCALE(16.0, 16.0, 0.0));
		floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
	}

	auto valueNoiseTexture = std::make_shared<QBRT::QBTexture::QBBasicValueNoiseTexture>();
	{
		valueNoiseTexture->SetColorMap(noiseMap);
		valueNoiseTexture->SetAmplitude(2.0);
		valueNoiseTexture->SetScale(16.0);
	}

	auto marbleTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
	{
		marbleTexture->SetColorMap(marbleMap);
		marbleTexture->SetAmplitude(4.0, 2.0);
		marbleTexture->SetScale(6.0, 40.0);
		marbleTexture->SetSine(1.0, 4.0);
		marbleTexture->SetMinMax(-1.0, 1.0);
	}

	auto cloudGradientNoiseTexture = std::make_shared<QBRT::QBTexture::QBBasicGradientNoiseTexture>();
	{
		cloudGradientNoiseTexture->SetColorMap(cloudMap);
		cloudGradientNoiseTexture->SetAmplitude(12.0);
		cloudGradientNoiseTexture->SetScale(10.0);
	}

	auto spiralTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
	{
		spiralTexture->SetColorMap(candyMap);
		spiralTexture->SetAmplitude(0.0, 0.0);
		spiralTexture->SetScale(1.0, 10.0);
		spiralTexture->SetSine(1.0, 8.0);
		spiralTexture->SetMinMax(-1.0, 1.0);
	}

	auto woodTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
	{
		woodTexture->SetColorMap(woodMap);
		woodTexture->SetAmplitude(8.0, 1.0);
		woodTexture->SetScale(2.0, 10.0);
		woodTexture->SetSine(1.0, 8.0);
		woodTexture->SetMinMax(-1.0, 1.0);
	}
	
	//*/
	std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
	{
		pMatFloor->AssignTexture(floorTexture);
	}

	auto pMatValueNoise = std::make_shared<QBRT::QBSimpleMaterial>();
	{
		pMatValueNoise->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
		pMatValueNoise->m_fReflectivity = 0.2;
		pMatValueNoise->m_fShininess = 32;
		pMatValueNoise->AssignTexture(valueNoiseTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatMarble = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.05, 32.0);
	{
		pMatMarble->AssignTexture(marbleTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatCloud = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.05, 32.0);
	{
		pMatCloud->AssignTexture(cloudGradientNoiseTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatCandy = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.05, 32.0);
	{
		pMatCandy->AssignTexture(spiralTexture);
	}

	std::shared_ptr<QBRT::QBSimpleMaterial> pMatWood = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.05, 32.0);
	{
		pMatWood->AssignTexture(woodTexture);
	}

	///*
	// Floor Plane
	QBRT::QBUtils::AddPlane(	m_vObjectList,
								MAKE_POSITION(0.0, 0.0, 0.5),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(16.0, 16.0, 1.0),
								pMatFloor);
	
	// Marble Sphere
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(-0.5, 0.0, -0.75),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 0.5, 0.5),
								pMatMarble);

	// Cloud Sphere
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(0.5, 0.0, -0.75),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 0.5, 0.5),
								pMatCloud);
	
	// Value Noise Sphere
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(1.0, 0.0, 0.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 0.5, 0.5),
								pMatValueNoise);
	
	// Candy Sphere
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(-1.0, 0.0, 0.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 0.5, 0.5),
								pMatCandy);
	
	// Wood Sphere
	QBRT::QBUtils::AddSphere(	m_vObjectList,
								MAKE_POSITION(0.0, 0.0, 0.0),
								MAKE_ROTATION(0.0, 0.0, 0.0),
								MAKE_SCALE(0.5, 0.5, 0.5),
								pMatWood);

	//*/
	// Construct a test light.
	QBRT::QBUtils::AddLight(	m_vLightList,	
								MAKE_POSITION(3.0, -10.0, -5.0),	
								MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
	QBRT::QBUtils::AddLight(	m_vLightList,	
								MAKE_POSITION(0.0, -10.0, -5.0),	
								MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
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
			qbVector4<double>					vClosestLocalColour;

			bool bIntersectionFound = CastRay(cameraRay, m_vObjectList, nullptr, pClosestObject, vClosestIntersectionPoint, vClosestLocalNormal, vClosestLocalColour);

			// Compute the illumination for the closest object, assuming that there
			// was a valid intersection.
			if (bIntersectionFound)
			{
				qbVector4<double> vFinalColour;

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
								qbVector4<double>& vClosestLocalColour)
{
	qbVector3<double>	vIntersectionPoint;
	qbVector3<double>	vLocalNormal;
	qbVector4<double>	vLocalColour;
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