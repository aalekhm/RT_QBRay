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
#include "qbNormals/QBNormalSimpleRough.hpp"
#include "qbTextures/QBStoneTexture.hpp"
#include "qbNormals/QBImageNormal.hpp"
#include "qbTextures/QBGradientTexture.hpp"
#include "qbPrimitives/QBCompositeBase.hpp"

#define EPISODE_TO_RENDER 22

void QBRT::QBScene::SetUpScene(uint32_t iEpisode)
{
	switch (iEpisode)
	{
		case 7:		// RT_QBRay_Ep07 - SimpleMaterials
		{
			// Configure the camera.
			m_Camera.SetPosition(MAKE_POSITION(0.0, -10.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(0.25);
			m_Camera.SetAspect(16.0 / 9.0);
			m_Camera.UpdateCameraGeometry();

			// Construct a test sphere.
			QBRT::QBUtils::AddSphere(	m_vObjectList, 
										MAKE_POSITION(-1.5, 0.0, 0.0),		
										MAKE_ROTATION(0.0, 0.0, 0.0),	
										MAKE_SCALE(0.5, 0.5, 0.5),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.5, 0.0, 1.0), 0.25, 10.0));

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.5, 0.5, 0.5),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.25, 0.5, 0.8, 1.0), 0.1, 10.0));

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(1.5, 0.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.5, 0.5, 0.5),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.8, 0.0, 1.0), 0.75, 10.0));

			// Construct a test plane.
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 0.75),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(4.0, 4.0, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0));

			// Construct a test light.
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(5.0, -10.0, -5.0),	MAKE_COLOUR(0.0, 0.0, 1.0, 1.0));
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(-5.0, -10.0, -5.0),	MAKE_COLOUR(1.0, 0.0, 0.0, 1.0));
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(0.0, -10.0, -5.0),	MAKE_COLOUR(0.0, 1.0, 0.0, 1.0));
		}
		break;
		case 8:		// RT_QBRay_Ep08 - ConesAndCylinders
		{
			// Configure the camera.
			m_Camera.SetPosition(MAKE_POSITION(3.0, -5.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(0.75);
			m_Camera.SetAspect(16.0 / 9.0);
			m_Camera.UpdateCameraGeometry();

			// Cone 1
			QBRT::QBUtils::AddCone(	m_vObjectList, 
									MAKE_POSITION(0.0, 0.0, -0.5),
									MAKE_ROTATION(0.0, 0.0, 0.0),
									MAKE_SCALE(1.0, 1.0, 2.0),
									MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.5, 0.5, 0.8, 1.0), 0.5, 20.0));

			// Left Sphere - BLUE
			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(1.5, -2.0, 0.5),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.5, 0.5, 0.5),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.8, 1.0), 0.05, 5.0));

			// Right Sphere - YELLOW
			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(1.5, 0.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2, 1.0), 0.05, 5.0));

			// Top Sphere - ORANGE
			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, -1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.5, 0.5, 0.5),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.5, 0.0, 1.0), 0.05, 5.0));
	
			// Floor
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.0, 0.0));

			// Left Wall
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(-4.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, -M_PI/2.0, -M_PI / 2.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.75, 0.0));
	
			// Back Wall
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 4.0, 0.0),
										MAKE_ROTATION(-M_PI/2.0, 0.0, -M_PI / 2.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.75, 0.0));
	
			// Cylinder 1 - GOLD METAL
			QBRT::QBUtils::AddCylinder(	m_vObjectList,
										MAKE_POSITION(-1.5, -2.0, 1.0),
										MAKE_ROTATION(0.0, -M_PI/2.0, 0.0),
										MAKE_SCALE(0.25, 0.25, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.3, 1.0), 0.25, 20.0));

			// Cylinder 2
			QBRT::QBUtils::AddCylinder(	m_vObjectList,
										MAKE_POSITION(-1.0, -2.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.25, 0.25, 1.0),
										MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.5, 0.5, 0.8, 1.0), 0.5, 20.0));

			// Cone 1
			QBRT::QBUtils::AddCone(	m_vObjectList,
									MAKE_POSITION(0.0, -1.0, 0.0),
									MAKE_ROTATION(M_PI/4.0, 0.0, 0.0),
									MAKE_SCALE(0.5, 0.5, 1.0),
									MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.3, 1.0), 0.25, 20.0));

			// Construct a test light.
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(3.0, -10.0, -5.0),	MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(0.0, -10.0, -5.0),	MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
		}
		break;
		case 9:		// RT_QBRay_Ep09 - UVSpaceAndTextures
		{
			// Configure the camera.
			m_Camera.SetPosition(MAKE_POSITION(2.0, -5.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}
			auto sphereTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				sphereTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.8, 1.0), MAKE_COLOUR(0.8, 0.8, 0.2, 1.0));
				sphereTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(16.0, 16.0));
			}
			auto cylinderTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				cylinderTexture->SetColour(MAKE_COLOUR(1.0, 0.5, 0.0, 1.0), MAKE_COLOUR(0.8, 0.8, 0.2, 1.0));
				cylinderTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(4.0*M_PI, 4.0));
			}
			auto coneTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				coneTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.8, 1.0), MAKE_COLOUR(1.0, 0.5, 0.0, 1.0));
				coneTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(8.0*(M_PI/2.0), 8.0));
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSilver = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.5, 0.5, 0.8, 1.0), 0.5, 20.0);

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatBlueDiffuse = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.5, 0.5, 0.8, 1.0), 0.5, 20.0);
			{
				pMatBlueDiffuse->AssignTexture(coneTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatYellowDiffuse = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2, 1.0), 0.05, 5.0);
			{
				pMatYellowDiffuse->AssignTexture(sphereTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatOrangeDiffuse = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.5, 0.0, 1.0), 0.05, 5.0);
			{
				pMatOrangeDiffuse->AssignTexture(cylinderTexture);
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			QBRT::QBUtils::AddCone(	m_vObjectList, 
									MAKE_POSITION(-1.0, -2.0, -2.0),
									MAKE_ROTATION(0.0, 0.0, 0.0),
									MAKE_SCALE(0.5, 0.5, 1.0),
									pMatBlueDiffuse,
									"Blue Cone");

			// Left Sphere - SILVER
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(1.0, -1.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatSilver,
						"Silver Sphere");

			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(2.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(1.0, 1.0, 1.0),
						pMatYellowDiffuse,
						"Yellow Diffuse Sphere");

			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 1.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						pMatFloor,
						"Floor Plane");

			// Left Wall
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(-4.0, 0.0, 1.0),
						MAKE_ROTATION(0.0, -M_PI/2.0, -M_PI / 2.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.75, 0.0),
						"Left Wall");
	
			// Back Wall
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 4.0, 0.0),
						MAKE_ROTATION(-M_PI/2.0, 0.0, -M_PI / 2.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.75, 0.0),
						"Back Wall");
	
			ADD_CYLINDER(	m_vObjectList,
							MAKE_POSITION(-1.0, -2.0, 0.0),
							MAKE_ROTATION(0.0, 0.0, 0.0),
							MAKE_SCALE(1.0, 1.0, 1.0),
							pMatOrangeDiffuse,
							"Orange Diffuse Cylinder", true);

			// Construct a test light.
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(3.0, -10.0, -5.0),	MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(0.0, -10.0, -5.0),	MAKE_COLOUR(1.0, 1.0, 1.0, 1.0));
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(-2.0, 2.0, 0.0),		MAKE_COLOUR(1.0, 0.8, 0.8, 1.0))->m_fLightIntensity = 0.5;
			QBRT::QBUtils::AddLight(m_vLightList,	MAKE_POSITION(4.0, 2.0, 0.0),		MAKE_COLOUR(1.0, 0.8, 0.8, 1.0))->m_fLightIntensity = 0.5;
		}
		break;
		case 91:	// RT_QBRay_Ep09a - ImageTextures
		{
			// Configure the camera.
			m_Camera.SetPosition(MAKE_POSITION(2.0, -5.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.25, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.0, 0.0);
			{
				pMatImage->AssignTexture(imageTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere2 =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere3 =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);

			// Floor Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										pMatFloor);

			// Image Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 5.0, -0.75),
										MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
										MAKE_SCALE(1.75, 1.75, 1.0),
										pMatImage);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -2.0, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -0.5, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere2);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -1.25, -1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere3);

			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 10:	// RT_QBRay_Ep10 - RefractiveMaterials
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(2.0, -5.0, 0.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.25, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.0, 0.0);
			{
				pMatImage->AssignTexture(imageTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere2 =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphere3 =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass =	MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33);

			// Floor Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										pMatFloor);

			// Image Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 5.0, -0.75),
										MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
										MAKE_SCALE(1.75, 1.75, 1.0),
										pMatImage);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -2.0, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -0.5, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere2);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(-2.0, -1.25, -1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatSphere3);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(2.0, -1.25, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										pMatGlass);

			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 11:	// RT_QBRay_Ep11 - FixingTheNormals
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(2.0, -5.0, 0.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.25, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.0, 0.0);
			{
				pMatImage->AssignTexture(imageTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereRed =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereGreen =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereBlue =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatConeBlue =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.7, 1.0), 0.2, 1.0);
			std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass =		MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33);

			// Floor Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										pMatFloor);

			// Image Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 5.0, -0.75),
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

			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 12:	// RT_QBRay_Ep12 - Boxes
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
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.25, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.0, 0.0);
			{
				pMatImage->AssignTexture(imageTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereRed =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereGreen =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereBlue =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatConeBlue =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.7, 1.0), 0.2, 1.0);
			std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass =		MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatBoxYellow =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2, 1.0), 0.15, 32.0);

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
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 13:	// RT_QBRay_Ep13 - RayTracingVsRayMarching
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
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>( 1.0, 1.0, 1.0, 1.0 );
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.25, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.0, 0.0);
			{
				pMatImage->AssignTexture(imageTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereRed =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereGreen =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereBlue =	MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatConeBlue =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.7, 1.0), 0.2, 1.0);
			std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass =		MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatBoxYellow =		MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2, 1.0), 0.15, 32.0);

			// Floor Plane
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 1.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						pMatFloor,
						"Floor Plane");

			// Image Plane
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(2.0, 5.0, -0.75),
						MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
						MAKE_SCALE(1.75, 1.75, 1.0),
						pMatImage,
						"Image Texture Plane");

			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-2.0, -2.0, 0.25),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.75, 0.75, 0.75),
						pMatSphereRed,
						"Red Sphere");

			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-2.0, -0.5, 0.25),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.75, 0.75, 0.75),
						pMatSphereGreen,
						"Green Sphere");

			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-2.0, -1.25, -1.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.75, 0.75, 0.75),
						pMatSphereBlue,
						"Blue Sphere");

			// RayMarch Sphere
			ADD_RM_SPHERE(	m_vObjectList, 
							MAKE_POSITION(0.0, 0.0, 0.0),
							MAKE_ROTATION(0.0, 0.0, 0.0),
							MAKE_SCALE(1.0, 1.0, 1.0),
							pMatBoxYellow,
							"RM Yellow Sphere");
			
			// RayMarch Torus
			ADD_RM_TORUS(	m_vObjectList, 
							MAKE_POSITION(2.0, 0.0, -0.25),
							MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
							MAKE_SCALE(1.0, 1.0, 1.0),
							pMatGlass, 
							0.7, 0.3,
							"RM Glass Torus");
			
			// RayMarch Cube
			ADD_RM_CUBE(	m_vObjectList, 
							MAKE_POSITION(3.5, 0.0, 0.0),
							MAKE_ROTATION(0.0, 0.0, -M_PI/4.0),
							MAKE_SCALE(0.5, 0.5, 0.5),
							pMatBoxYellow,
							"RM Yellow Cube");

			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 14:	// RT_QBRay_Ep14 - ProceduralTextures-Part1
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(4.0, -8.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(-0.5, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			auto gradientTexture = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				gradientTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));

				gradientTexture->SetStop(0.0, MAKE_COLOUR(1.0, 0.0, 0.0, 1.0));
				gradientTexture->SetStop(0.5, MAKE_COLOUR(0.2, 1.0, 0.0, 1.0));
				gradientTexture->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 1.0, 1.0));
			}

			auto smallChecksTexture1 = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				smallChecksTexture1->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													0.0,
													MAKE_SCALE2(8.0, 8.0));

				smallChecksTexture1->SetColour(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), MAKE_COLOUR(0.2, 0.2, 0.8, 1.0));
			}

			auto smallChecksTexture2 = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				smallChecksTexture2->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													-M_PI/4.0,
													MAKE_SCALE2(8.0, 8.0));

				smallChecksTexture2->SetColour(MAKE_COLOUR(0.0, 0.0, 0.0, 1.0), MAKE_COLOUR(1.0, 0.5, 0.1, 1.0));
			}

			auto layeredChecksTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				layeredChecksTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													0.0,
													MAKE_SCALE2(4.0, 4.0));

				layeredChecksTexture->SetColour(smallChecksTexture1, smallChecksTexture2);
			}

			auto alphaGradientTexture = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				alphaGradientTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													M_PI/4.0,
													MAKE_SCALE2(1.0, 1.0));

				alphaGradientTexture->SetStop(0.0, MAKE_COLOUR(0.0, 0.0, 1.0, 1.0, 1.0));
				alphaGradientTexture->SetStop(0.5, MAKE_COLOUR(1.0, 1.0, 1.0, 0.0, 0.0));
				alphaGradientTexture->SetStop(1.0, MAKE_COLOUR(1.0, 1.0, 0.0, 1.0, 1.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.2, 0.8);
			{
				pMatImage->AssignTexture(gradientTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatLayered = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.0, 0.0);
			{
				pMatLayered->AssignTexture(layeredChecksTexture);
				pMatLayered->AssignTexture(alphaGradientTexture);
			}

			///*
			// Floor Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 2.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										pMatFloor);

			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(-1.0, 0.0, 0.0),
										MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
										MAKE_SCALE(2.0, 2.0, 1.0),
										pMatLayered);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(2.5, 0.0, 1.0),
										MAKE_ROTATION(-M_PI/4.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatImage);

			QBRT::QBUtils::AddBox(		m_vObjectList,
										MAKE_POSITION(-5.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatImage);
			/*
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereRed = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereGreen = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 1.0, 0.2, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSphereBlue = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 1.0, 1.0), 0.8, 32.0);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatConeBlue = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.2, 0.2, 0.7, 1.0), 0.2, 1.0);
			std::shared_ptr<QBRT::QBSimpleRefractive> pMatGlass = MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(0.7, 0.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33);
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatBoxYellow = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(0.8, 0.8, 0.2, 1.0), 0.15, 32.0);

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

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(2.0, -1.25, 0.25),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(0.75, 0.75, 0.75),
										MAKE_SIMPLE_REFRACTIVE_MATERIAL(MAKE_COLOUR(1.0, 1.7, 0.2, 1.0), 0.25, 32.0, 0.75, 1.33));

			// RayMarch Sphere
			QBRT::QBUtils::AddRMSphere(	m_vObjectList, 
										MAKE_POSITION(0.0, 0.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatBoxYellow);
	
			// RayMarch Torus
			QBRT::QBUtils::AddRMTorus(	m_vObjectList, 
										MAKE_POSITION(2.0, 0.0, -0.25),
										MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatGlass, 
										0.7, 0.3);
	
			// RayMarch Cube
			QBRT::QBUtils::AddRMCube(	m_vObjectList, 
										MAKE_POSITION(3.5, 0.0, 0.0),
										MAKE_ROTATION(0.0, 0.0, -M_PI/4.0),
										MAKE_SCALE(0.5, 0.5, 0.5),
										pMatBoxYellow);
			//*/
			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 15:	// RT_QBRay_Ep15 - ProceduralTextures-Part2_ValueNoise
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(4.0, -8.0, -2.0));
			m_Camera.SetLookAt(MAKE_POSITION(-0.5, 0.0, 0.0));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.2;

			// Create some textures.
			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			auto noiseMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				noiseMap->SetStop(0.0, MAKE_COLOUR(1.0, 0.4, 0.0, 1.0));
				noiseMap->SetStop(0.5, MAKE_COLOUR(0.2, 0.4, 0.8, 1.0));
				noiseMap->SetStop(1.0, MAKE_COLOUR(1.0, 0.8, 0.0, 1.0));
			}

			auto valueNoiseTexture = std::make_shared<QBRT::QBTexture::QBBasicValueNoiseTexture>();
			{
				valueNoiseTexture->SetColorMap(noiseMap);
				valueNoiseTexture->SetAmplitude(1.0);
				valueNoiseTexture->SetScale(4.0);
			}

			auto gradientTexture = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				gradientTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));

				gradientTexture->SetStop(0.0, MAKE_COLOUR(1.0, 0.0, 0.0, 1.0));
				gradientTexture->SetStop(0.5, MAKE_COLOUR(0.2, 1.0, 0.0, 1.0));
				gradientTexture->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 1.0, 1.0));
			}

			auto smallChecksTexture1 = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				smallChecksTexture1->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													0.0,
													MAKE_SCALE2(8.0, 8.0));

				smallChecksTexture1->SetColour(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), MAKE_COLOUR(0.2, 0.2, 0.8, 1.0));
			}

			auto smallChecksTexture2 = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				smallChecksTexture2->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													-M_PI/4.0,
													MAKE_SCALE2(8.0, 8.0));

				smallChecksTexture2->SetColour(MAKE_COLOUR(0.0, 0.0, 0.0, 1.0), MAKE_COLOUR(1.0, 0.5, 0.1, 1.0));
			}

			auto layeredChecksTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				layeredChecksTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													0.0,
													MAKE_SCALE2(4.0, 4.0));

				layeredChecksTexture->SetColour(smallChecksTexture1, smallChecksTexture2);
			}

			auto alphaGradientTexture = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				alphaGradientTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
													M_PI/4.0,
													MAKE_SCALE2(1.0, 1.0));

				alphaGradientTexture->SetStop(0.0, MAKE_COLOUR(0.0, 0.0, 1.0, 1.0, 1.0));
				alphaGradientTexture->SetStop(0.5, MAKE_COLOUR(1.0, 1.0, 1.0, 0.0, 0.0));
				alphaGradientTexture->SetStop(1.0, MAKE_COLOUR(1.0, 1.0, 0.0, 1.0, 1.0));
			}

			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\charlie.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			auto pMatValueNoise = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMatValueNoise->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pMatValueNoise->m_fReflectivity = 0.2;
				pMatValueNoise->m_fShininess = 32;
				pMatValueNoise->AssignTexture(valueNoiseTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatFloor->AssignTexture(floorTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImage = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.125, 0.125, 1.0), 0.2, 0.8);
			{
				pMatImage->AssignTexture(gradientTexture);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatLayered = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 0.2, 0.2, 1.0), 0.0, 0.0);
			{
				pMatLayered->AssignTexture(layeredChecksTexture);
				pMatLayered->AssignTexture(alphaGradientTexture);
			}

			///*
			// Floor Plane
			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(0.0, 0.0, 2.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(16.0, 16.0, 1.0),
										pMatFloor);

			QBRT::QBUtils::AddPlane(	m_vObjectList,
										MAKE_POSITION(-1.0, 0.0, 0.0),
										MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
										MAKE_SCALE(2.0, 2.0, 1.0),
										pMatValueNoise);

			QBRT::QBUtils::AddSphere(	m_vObjectList,
										MAKE_POSITION(2.5, 0.0, 1.0),
										MAKE_ROTATION(-M_PI/4.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatValueNoise);

			QBRT::QBUtils::AddBox(		m_vObjectList,
										MAKE_POSITION(-5.0, 0.0, 1.0),
										MAKE_ROTATION(0.0, 0.0, 0.0),
										MAKE_SCALE(1.0, 1.0, 1.0),
										pMatValueNoise);

			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 16:	// RT_QBRay_Ep16 - ProceduralTextures-Part3_GradientNoise
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
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
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
		break;
		case 17:	// RT_QBRay_Ep17 - NormalMaps-Part1
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

			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto simpleRoughNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				simpleRoughNormalMap->m_fAmplitudeScale = 0.125;
			}

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
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
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
				pMatFloor->AssignNormalMap(simpleRoughNormalMap);
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
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						pMatFloor,
						"Floor Mat");
	
			// Marble Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatMarble,
						"Marble Sphere");

			// Cloud Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCloud,
						"Cloud Sphere");
	
			// Value Noise Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatValueNoise, "Value Noise Sphere");
	
			// Candy Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCandy, "Candy Sphere");
	
			// Wood Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatWood, "Wood Sphere");

			//*/
			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 18:	// RT_QBRay_Ep18 - NormalMaps-Part2_TextureBased
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
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			// An instance of the stone texture.
			auto stoneTexture = std::make_shared<QBRT::QBTexture::QBStoneTexture>();
			{
				stoneTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(4.0, 4.0));
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
	
			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto simpleRoughNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				simpleRoughNormalMap->m_fAmplitudeScale = 0.125;
			}

			auto stoneNormalMap = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				stoneNormalMap->AssignBaseTexture(stoneTexture);
				stoneNormalMap->m_fScale = 0.015;
			}

			// *****************************************************************
			// Create some materials.
			// *****************************************************************
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSimpleRoughFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatSimpleRoughFloor->AssignTexture(floorTexture);
				pMatSimpleRoughFloor->AssignNormalMap(simpleRoughNormalMap);
			}

			// Stone material.
			auto pMatStone = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.35, 32.0);
			{
				pMatStone->AssignTexture(stoneTexture);
				pMatStone->AssignNormalMap(stoneNormalMap);
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
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(16.0, 16.0, 1.0),
						pMatStone,
						"Floor Plane");
	
			// Marble Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatMarble,
						"Marble Sphere");

			// Cloud Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCloud,
						"Cloud Sphere");
	
			// Value Noise Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatValueNoise,
						"Value Noise Sphere");
	
			// Candy Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCandy,
						"Candy Sphere");
	
			// Wood Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatWood,
						"Wood Sphere");

			//*/
			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 19:	// RT_QBRay_Ep19 - NormalMaps-Part3_ImageBased
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
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			// An instance of the stone texture.
			auto stoneTexture = std::make_shared<QBRT::QBTexture::QBStoneTexture>();
			{
				stoneTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(4.0, 4.0));
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

			// An example image texture.
			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\Voronoi.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto simpleRoughNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				simpleRoughNormalMap->m_fAmplitudeScale = 0.125;
			}

			auto stoneNormalMap = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				stoneNormalMap->AssignBaseTexture(stoneTexture);
				stoneNormalMap->m_fScale = 0.015;
			}

			// An image based normal map.
			auto imageNormalMap = std::make_shared<QBRT::QBNormal::QBImageNormal>();
			{
				imageNormalMap->LoadImage("..\\Content\\Voronoi_normal.bmp");
				imageNormalMap->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			// *****************************************************************
			// Create some materials.
			// *****************************************************************
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSimpleRoughFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatSimpleRoughFloor->AssignTexture(floorTexture);
				pMatSimpleRoughFloor->AssignNormalMap(simpleRoughNormalMap);
			}

			// Stone material.
			auto pMatStone = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.35, 32.0);
			{
				pMatStone->AssignTexture(stoneTexture);
				pMatStone->AssignNormalMap(stoneNormalMap);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImageFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatImageFloor->AssignTexture(imageTexture);
				pMatImageFloor->AssignNormalMap(imageNormalMap);
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
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMatImageFloor, 
						"Floor Plane");
	
			// Marble Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatMarble, 
						"Marble Sphere");

			// Cloud Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCloud,
						"Cloud Sphere");
	
			// Value Noise Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatValueNoise,
						"Value Noise Sphere");
	
			// Candy Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCandy,
						"Candy Sphere");
	
			// Wood Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatWood,
						"Wood Sphere");

			//*/
			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 210:	// RT_QBRay_Ep21 - UVProjection - HitData refactor scene
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
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(16.0, 16.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			// An instance of the stone texture.
			auto stoneTexture = std::make_shared<QBRT::QBTexture::QBStoneTexture>();
			{
				stoneTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(4.0, 4.0));
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

			// An example image texture.
			auto imageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				imageTexture->LoadImage("..\\Content\\Voronoi.bmp");
				imageTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
	
			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto simpleRoughNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				simpleRoughNormalMap->m_fAmplitudeScale = 0.125;
			}

			auto stoneNormalMap = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				stoneNormalMap->AssignBaseTexture(stoneTexture);
				stoneNormalMap->m_fScale = 0.015;
			}

			// An image based normal map.
			auto imageNormalMap = std::make_shared<QBRT::QBNormal::QBImageNormal>();
			{
				imageNormalMap->LoadImage("..\\Content\\Voronoi_normal.bmp");
				imageNormalMap->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			// *****************************************************************
			// Create some materials.
			// *****************************************************************
			std::shared_ptr<QBRT::QBSimpleMaterial> pMatSimpleRoughFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatSimpleRoughFloor->AssignTexture(floorTexture);
				pMatSimpleRoughFloor->AssignNormalMap(simpleRoughNormalMap);
			}

			// Stone material.
			auto pMatStone = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.35, 32.0);
			{
				pMatStone->AssignTexture(stoneTexture);
				pMatStone->AssignNormalMap(stoneNormalMap);
			}

			std::shared_ptr<QBRT::QBSimpleMaterial> pMatImageFloor = MAKE_SIMPLE_MATERIAL(MAKE_COLOUR(1.0, 1.0, 1.0, 1.0), 0.5, 0.0);
			{
				pMatImageFloor->AssignTexture(imageTexture);
				pMatImageFloor->AssignNormalMap(imageNormalMap);
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

			// *****************************************************************
			// Create and setup objects.
			// *****************************************************************
			// Floor Plane
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMatImageFloor,
						"Floor Plane");

			// Marble Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatMarble,
						"Marble Sphere");

			// Cloud Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.5, 0.0, -0.75),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCloud,
						"Cloud Sphere");

			// Value Noise Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatValueNoise,
						"Value Noise Sphere");

			// Candy Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(-1.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatCandy,
						"Candy Sphere");

			// Wood Sphere
			ADD_SPHERE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pMatWood,
						"Wood Sphere");

			//*/
			// Construct a test light.
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(3.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -10.0, -5.0),	
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 2.0;
		}
		break;
		case 211:	// RT_QBRay_Ep21 - UVProjection
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(6.0, -10.0, -4.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.5));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetLength(3.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.25;

			// *****************************************************************
			// Create some colour maps.
			// *****************************************************************
			auto woodMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				woodMap->SetStop(0.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
				woodMap->SetStop(0.5, MAKE_COLOUR(100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0));
				woodMap->SetStop(1.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
			}

			auto noiseMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				noiseMap->SetStop(0.0, MAKE_COLOUR(1.0, 0.75, 0.0, 0.5));
				noiseMap->SetStop(0.5, MAKE_COLOUR(0.25, 0.25, 0.25, 0.25));
				noiseMap->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 0.0, 0.0));
			}

			auto fineMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				fineMap->SetStop(0.0, MAKE_COLOUR(100.0 / 255.0, 50.0 / 255.0, 30.0 / 255.0, 0.25));
				fineMap->SetStop(0.2, MAKE_COLOUR(200.0 / 255.0, 150.0 / 255.0, 120.0 / 255.0, 0.25));
				fineMap->SetStop(0.4, MAKE_COLOUR(0.0, 0.0, 0.0, 0.25));
				fineMap->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 0.0, 0.0));
			}

			// *****************************************************************
			// Create some textures.
			// *****************************************************************
			auto sprayTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				sprayTexture->LoadImage("..\\Content\\qbSpray1.bmp");
				sprayTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}

			auto woodBoxTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				woodBoxTexture->LoadImage("..\\Content\\WoodBoxTexture.bmp");
				woodBoxTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(8.0, 8.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			auto woodTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
			{
				woodTexture->SetColorMap(woodMap);
				woodTexture->SetAmplitude(8.0, 1.0);
				woodTexture->SetScale(2.0, 10.0);
				woodTexture->SetSine(1.0, 8.0);
				woodTexture->SetMinMax(-1.0, 1.0);
				woodTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}

			auto dirtTexture1 = std::make_shared<QBRT::QBTexture::QBBasicValueNoiseTexture>();
			{
				dirtTexture1->SetColorMap(noiseMap);
				dirtTexture1->SetAmplitude(2.0);
				dirtTexture1->SetScale(16.0);
			}

			auto vertGradTexture1 = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				vertGradTexture1->SetStop(0.0, MAKE_COLOUR(1.0, 0.75, 0.0, 1.0));
				vertGradTexture1->SetStop(0.5, MAKE_COLOUR(0.5, 0.5, 0.5, 0.25));
				vertGradTexture1->SetStop(1.0, MAKE_COLOUR(0.5, 0.5, 0.5, 0.0));
				vertGradTexture1->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto fineTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
			{
				fineTexture->SetColorMap(fineMap);
				fineTexture->SetAmplitude(2.0, 1.0);
				fineTexture->SetScale(20.0, 40.0);
				fineTexture->SetSine(64.0, 128.0);
				fineTexture->SetMinMax(-1.0, 1.0);
				fineTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
			
			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto woodBoxNormalMap = std::make_shared<QBRT::QBNormal::QBImageNormal>();
			{
				woodBoxNormalMap->LoadImage("..\\Content\\WoodBoxNormal.bmp");
				woodBoxNormalMap->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto woodNormalMap1 = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				woodNormalMap1->AssignBaseTexture(woodTexture);
				woodNormalMap1->m_fScale = 0.0001;
			}

			auto fineNormalMap1 = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				fineNormalMap1->AssignBaseTexture(fineTexture);
				fineNormalMap1->m_fScale = 0.001;
				fineNormalMap1->m_bReverse = false;
			}

			auto mirrorNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				mirrorNormalMap->m_fAmplitudeScale = 0.01;
			}

			// *****************************************************************
			// Create some materials.
			// *****************************************************************
			auto pFloorMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pFloorMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pFloorMaterial->m_fReflectivity = 0.75;
				pFloorMaterial->m_fShininess = 0.0;
				pFloorMaterial->AssignTexture(floorTexture);
			}

			auto pSprayBodyMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pSprayBodyMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pSprayBodyMaterial->m_fReflectivity = 0.1;
				pSprayBodyMaterial->m_fShininess = 16.0;
				pSprayBodyMaterial->AssignTexture(sprayTexture);
			}

			auto pMetalMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMetalMaterial->m_vBaseColour = qbVector4<double>(0.5, 0.5, 0.5, 0.5);
				pMetalMaterial->m_fReflectivity = 0.5;
				pMetalMaterial->m_fShininess = 64.0;
			}

			auto pWhitePlasticMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pWhitePlasticMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pWhitePlasticMaterial->m_fReflectivity = 0.0;
				pWhitePlasticMaterial->m_fShininess = 0.0;
			}

			auto pMirrorMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMirrorMaterial->m_vBaseColour = qbVector4<double>(0.0, 0.0, 1.0, 1.0);
				pMirrorMaterial->m_fReflectivity = 0.5;
				pMirrorMaterial->m_fShininess = 64.0;
				pMirrorMaterial->AssignNormalMap(mirrorNormalMap);
			}

			auto pMirrorMaterial2 = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMirrorMaterial2->m_vBaseColour = qbVector4<double>(1.0, 1.0, 0.0, 1.0);
				pMirrorMaterial2->m_fReflectivity = 0.5;
				pMirrorMaterial2->m_fShininess = 64.0;
				pMirrorMaterial2->AssignNormalMap(mirrorNormalMap);
			}

			auto pBoxMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pBoxMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pBoxMaterial->m_fReflectivity = 0.0;
				pBoxMaterial->m_fShininess = 32.0;
				pBoxMaterial->AssignTexture(woodBoxTexture);
				pBoxMaterial->AssignNormalMap(woodBoxNormalMap);
			}

			auto pWoodMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pWoodMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pWoodMaterial->m_fReflectivity = 0.0;
				pWoodMaterial->m_fShininess = 32.0;
				pWoodMaterial->AssignTexture(woodTexture);
				pWoodMaterial->AssignTexture(fineTexture);
				pWoodMaterial->AssignTexture(dirtTexture1);
				pWoodMaterial->AssignTexture(vertGradTexture1);
				pWoodMaterial->AssignNormalMap(woodNormalMap1);
				pWoodMaterial->AssignNormalMap(fineNormalMap1);
			}

			// *****************************************************************
			// Create and setup objects.
			// *****************************************************************
			double sprayX = 1.0;
			double sprayY = -1.75;
			ADD_CYLINDER(	m_vObjectList,
							MAKE_POSITION(sprayX, sprayY, -0.5),
							MAKE_ROTATION(0.0, 0.0, M_PI/5.0),
							MAKE_SCALE(0.4, 0.4, 1.0),
							pSprayBodyMaterial,
							"Spray Body Cylinder", true);
			
			ADD_CONE(	m_vObjectList,
						MAKE_POSITION(sprayX, sprayY, -2.0),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(0.4, 0.4, 0.5),
						pMetalMaterial,
						"Spray Top Cone", true);
			
			ADD_CYLINDER(	m_vObjectList,
							MAKE_POSITION(sprayX, sprayY, -1.5),
							MAKE_ROTATION(0.0, 0.0, 0.0),
							MAKE_SCALE(0.2, 0.2, 0.5),
							pWhitePlasticMaterial,
							"Spray Top Cylinder", true);
			
			ADD_BOX(	m_vObjectList,
						MAKE_POSITION(-1.0, -2.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, -M_PI/6.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pBoxMaterial,
						"Box");
			
			ADD_BOX(	m_vObjectList,
						MAKE_POSITION(-1.0, -0.75, -0.25),
						MAKE_ROTATION(M_PI/4.0, 0.0, M_PI/2.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pBoxMaterial,
						"Box2");
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(6.0, 6.0, 1.0),
						pFloorMaterial,
						"Floor Plane");
			
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 2.0, 0.0),
						MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMirrorMaterial,
						"Back Wall Plane");
			
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(-2.0, 0.0, 0.0),
						MAKE_ROTATION(-M_PI/2.0, -M_PI/2.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMirrorMaterial2,
						"Side Wall Plane");

			ADD_RM_TORUS(	m_vObjectList, 
							MAKE_POSITION(2.5, -2.0, 0.2),
							MAKE_ROTATION(0.0, 0.0, 0.0),
							MAKE_SCALE(1.0, 1.0, 1.0),
							pWoodMaterial, 
							0.7, 0.3,
							"RM Wood Torus");

			// *****************************************************************
			// Construct and setup lights.
			// *****************************************************************

			// Left Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -20.0, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			// Right Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(8.0, -20.0, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 6.0;
			// Top Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, 0.3, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 1.0;

		}
		break;
		case 22:	// RT_QBRay_Ep22 - BoundingBoxesAndCompositeShapes
		{
			// **************************************************************************************
			// Configure the camera.
			// **************************************************************************************	
			m_Camera.SetPosition(MAKE_POSITION(6.0, -10.0, -4.0));
			m_Camera.SetLookAt(MAKE_POSITION(0.0, 0.0, 0.5));
			m_Camera.SetUp(MAKE_POSITION(0.0, 0.0, 1.0));
			m_Camera.SetHorizontalSize(1.0);
			m_Camera.SetLength(3.0);
			m_Camera.SetAspect(ASPECT_RATIO);
			m_Camera.UpdateCameraGeometry();

			// **************************************************************************************
			// Setup ambient lightling.
			// **************************************************************************************		
			QBRT::QBMaterialBase::m_vAmbientColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
			QBRT::QBMaterialBase::m_fAmbientIntensity = 0.25;

			// *****************************************************************
			// Create some colour maps.
			// *****************************************************************
			auto woodMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				woodMap->SetStop(0.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
				woodMap->SetStop(0.5, MAKE_COLOUR(100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0));
				woodMap->SetStop(1.0, MAKE_COLOUR(200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0));
			}

			auto noiseMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				noiseMap->SetStop(0.0, MAKE_COLOUR(1.0, 0.75, 0.0, 0.5));
				noiseMap->SetStop(0.5, MAKE_COLOUR(0.25, 0.25, 0.25, 0.25));
				noiseMap->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 0.0, 0.0));
			}

			auto fineMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
			{
				fineMap->SetStop(0.0, MAKE_COLOUR(100.0 / 255.0, 50.0 / 255.0, 30.0 / 255.0, 0.25));
				fineMap->SetStop(0.2, MAKE_COLOUR(200.0 / 255.0, 150.0 / 255.0, 120.0 / 255.0, 0.25));
				fineMap->SetStop(0.4, MAKE_COLOUR(0.0, 0.0, 0.0, 0.25));
				fineMap->SetStop(1.0, MAKE_COLOUR(0.0, 0.0, 0.0, 0.0));
			}

			// *****************************************************************
			// Create some textures.
			// *****************************************************************
			auto sprayTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				sprayTexture->LoadImage("..\\Content\\qbSpray1.bmp");
				sprayTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}

			auto woodBoxTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
			{
				woodBoxTexture->LoadImage("..\\Content\\WoodBoxTexture.bmp");
				woodBoxTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto floorTexture = std::make_shared<QBRT::QBTexture::QBCheckeredTexture>();
			{
				floorTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(8.0, 8.0));
				floorTexture->SetColour(MAKE_COLOUR(0.2, 0.2, 0.2, 1.0), MAKE_COLOUR(0.4, 0.4, 0.4, 1.0));
			}

			auto woodTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
			{
				woodTexture->SetColorMap(woodMap);
				woodTexture->SetAmplitude(8.0, 1.0);
				woodTexture->SetScale(2.0, 10.0);
				woodTexture->SetSine(1.0, 8.0);
				woodTexture->SetMinMax(-1.0, 1.0);
				woodTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}

			auto dirtTexture1 = std::make_shared<QBRT::QBTexture::QBBasicValueNoiseTexture>();
			{
				dirtTexture1->SetColorMap(noiseMap);
				dirtTexture1->SetAmplitude(2.0);
				dirtTexture1->SetScale(16.0);
			}

			auto vertGradTexture1 = std::make_shared<QBRT::QBTexture::QBGradientTexture>();
			{
				vertGradTexture1->SetStop(0.0, MAKE_COLOUR(1.0, 0.75, 0.0, 1.0));
				vertGradTexture1->SetStop(0.5, MAKE_COLOUR(0.5, 0.5, 0.5, 0.25));
				vertGradTexture1->SetStop(1.0, MAKE_COLOUR(0.5, 0.5, 0.5, 0.0));
				vertGradTexture1->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto fineTexture = std::make_shared<QBRT::QBTexture::QBMarbleTexture>();
			{
				fineTexture->SetColorMap(fineMap);
				fineTexture->SetAmplitude(2.0, 1.0);
				fineTexture->SetScale(20.0, 40.0);
				fineTexture->SetSine(64.0, 128.0);
				fineTexture->SetMinMax(-1.0, 1.0);
				fineTexture->SetTransform(	MAKE_POSITION2(0.0, 0.0),
											0.0,
											MAKE_SCALE2(1.0, 1.0));
			}
			
			// **************************************************************************************
			// Setup normal maps.
			// **************************************************************************************		
			auto woodBoxNormalMap = std::make_shared<QBRT::QBNormal::QBImageNormal>();
			{
				woodBoxNormalMap->LoadImage("..\\Content\\WoodBoxNormal.bmp");
				woodBoxNormalMap->SetTransform(	MAKE_POSITION2(0.0, 0.0),
												0.0,
												MAKE_SCALE2(1.0, 1.0));
			}

			auto woodNormalMap1 = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				woodNormalMap1->AssignBaseTexture(woodTexture);
				woodNormalMap1->m_fScale = 0.0001;
			}

			auto fineNormalMap1 = std::make_shared<QBRT::QBNormal::QBTextureNormal>();
			{
				fineNormalMap1->AssignBaseTexture(fineTexture);
				fineNormalMap1->m_fScale = 0.001;
				fineNormalMap1->m_bReverse = false;
			}

			auto mirrorNormalMap = std::make_shared<QBRT::QBNormal::QBNormalSimpleRough>();
			{
				mirrorNormalMap->m_fAmplitudeScale = 0.01;
			}

			// *****************************************************************
			// Create some materials.
			// *****************************************************************
			auto pFloorMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pFloorMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pFloorMaterial->m_fReflectivity = 0.25;
				pFloorMaterial->m_fShininess = 0.0;
				pFloorMaterial->AssignTexture(floorTexture);
			}

			auto pSprayBodyMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pSprayBodyMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pSprayBodyMaterial->m_fReflectivity = 0.1;
				pSprayBodyMaterial->m_fShininess = 16.0;
				pSprayBodyMaterial->AssignTexture(sprayTexture);
			}

			auto pMetalMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMetalMaterial->m_vBaseColour = qbVector4<double>(0.5, 0.5, 0.5, 0.5);
				pMetalMaterial->m_fReflectivity = 0.5;
				pMetalMaterial->m_fShininess = 64.0;
			}

			auto pWhitePlasticMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pWhitePlasticMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pWhitePlasticMaterial->m_fReflectivity = 0.0;
				pWhitePlasticMaterial->m_fShininess = 0.0;
			}

			auto pMirrorMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMirrorMaterial->m_vBaseColour = qbVector4<double>(0.0, 0.0, 1.0, 1.0);
				pMirrorMaterial->m_fReflectivity = 0.5;
				pMirrorMaterial->m_fShininess = 64.0;
				pMirrorMaterial->AssignNormalMap(mirrorNormalMap);
			}

			auto pMirrorMaterial2 = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pMirrorMaterial2->m_vBaseColour = qbVector4<double>(1.0, 1.0, 0.0, 1.0);
				pMirrorMaterial2->m_fReflectivity = 0.5;
				pMirrorMaterial2->m_fShininess = 64.0;
				pMirrorMaterial2->AssignNormalMap(mirrorNormalMap);
			}

			auto pBoxMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pBoxMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pBoxMaterial->m_fReflectivity = 0.0;
				pBoxMaterial->m_fShininess = 32.0;
				pBoxMaterial->AssignTexture(woodBoxTexture);
				pBoxMaterial->AssignNormalMap(woodBoxNormalMap);
			}

			auto pWoodMaterial = std::make_shared<QBRT::QBSimpleMaterial>();
			{
				pWoodMaterial->m_vBaseColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
				pWoodMaterial->m_fReflectivity = 0.0;
				pWoodMaterial->m_fShininess = 32.0;
				pWoodMaterial->AssignTexture(woodTexture);
				pWoodMaterial->AssignTexture(fineTexture);
				pWoodMaterial->AssignTexture(dirtTexture1);
				pWoodMaterial->AssignTexture(vertGradTexture1);
				pWoodMaterial->AssignNormalMap(woodNormalMap1);
				pWoodMaterial->AssignNormalMap(fineNormalMap1);
			}

			// *****************************************************************
			// Create and setup objects.
			// *****************************************************************
			double sprayX = 0.0;
			double sprayY = 0.0;
			bool bDonNotAddtoParent = false;
			auto sprayCanCylinderBody = ADD_CYLINDER(	m_vObjectList,
														MAKE_POSITION(sprayX, sprayY, -0.5),
														MAKE_ROTATION(0.0, 0.0, 0.0),
														MAKE_SCALE(0.4, 0.4, 1.0),
														pSprayBodyMaterial,
														"Spray Body Cylinder",
														bDonNotAddtoParent);
			
			auto sprayCanCone = ADD_CONE(	m_vObjectList,
											MAKE_POSITION(sprayX, sprayY, -2.0),
											MAKE_ROTATION(0.0, 0.0, 0.0),
											MAKE_SCALE(0.4, 0.4, 0.5),
											pMetalMaterial,
											"Spray Top Cone", 
											bDonNotAddtoParent);
			
			auto sprayCanCylinderTop = ADD_CYLINDER(	m_vObjectList,
														MAKE_POSITION(sprayX, sprayY, -1.5),
														MAKE_ROTATION(0.0, 0.0, 0.0),
														MAKE_SCALE(0.2, 0.2, 0.5),
														pWhitePlasticMaterial,
														"Spray Top Cylinder", 
														bDonNotAddtoParent);
			
			auto sprayCan = std::make_shared<QBRT::SHAPES::QBCompositeBase>();
			{
				sprayCan->AddSubShape(sprayCanCylinderBody);
				sprayCan->AddSubShape(sprayCanCone);
				sprayCan->AddSubShape(sprayCanCylinderTop);
				QBRT::QBGeometricTransform xForm(	MAKE_POSITION(1.0, -1.75, 0.0),
													MAKE_ROTATION(0.0, -M_PI/4.0, 0.0),
													MAKE_SCALE(1.0, 1.0, 1.0));
				sprayCan->SetTransform(xForm);
			}
			m_vObjectList.push_back(sprayCan);

			ADD_BOX(	m_vObjectList,
						MAKE_POSITION(-1.0, -2.0, 0.0),
						MAKE_ROTATION(0.0, 0.0, -M_PI/6.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pBoxMaterial,
						"Box");
			
			ADD_BOX(	m_vObjectList,
						MAKE_POSITION(-1.0, -0.75, -0.25),
						MAKE_ROTATION(M_PI/4.0, 0.0, M_PI/2.0),
						MAKE_SCALE(0.5, 0.5, 0.5),
						pBoxMaterial,
						"Box2");
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 0.0, 0.5),
						MAKE_ROTATION(0.0, 0.0, 0.0),
						MAKE_SCALE(6.0, 6.0, 1.0),
						pFloorMaterial,
						"Floor Plane");
			
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(0.0, 2.0, 0.0),
						MAKE_ROTATION(-M_PI/2.0, 0.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMirrorMaterial,
						"Back Wall Plane");
			
			ADD_PLANE(	m_vObjectList,
						MAKE_POSITION(-2.0, 0.0, 0.0),
						MAKE_ROTATION(-M_PI/2.0, -M_PI/2.0, 0.0),
						MAKE_SCALE(4.0, 4.0, 1.0),
						pMirrorMaterial2,
						"Side Wall Plane");

			ADD_RM_TORUS(	m_vObjectList, 
							MAKE_POSITION(2.5, -2.0, 0.2),
							MAKE_ROTATION(0.0, 0.0, 0.0),
							MAKE_SCALE(1.0, 1.0, 1.0),
							pWoodMaterial, 
							0.7, 0.3,
							"RM Wood Torus");

			// *****************************************************************
			// Construct and setup lights.
			// *****************************************************************

			// Left Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, -20.0, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 4.0;
			// Right Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(8.0, -20.0, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 6.0;
			// Top Light
			QBRT::QBUtils::AddLight(	m_vLightList,	
										MAKE_POSITION(0.0, 0.3, -20.0),
										MAKE_COLOUR(1.0, 1.0, 1.0, 1.0))->m_fLightIntensity = 1.0;

		}
		break;
	}
}

// The constructor.
QBRT::QBScene::QBScene()
{
	SetUpScene(EPISODE_TO_RENDER);
}

// Function to perform the renderering.
bool QBRT::QBScene::Render(QBImage& outputImage)
{
	// Get the dimensions of the output image.
	uint32_t xSize = outputImage.GetXSize();
	uint32_t ySize = outputImage.GetYSize();

	// Loop over each pixel in our image.
	QBRT::QBRay cameraRay;
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
			QBRT::DATA::HitData					sClosestHitData;

			bool bIntersectionFound = CastRay(	cameraRay, 
												m_vObjectList,
												nullptr,
												pClosestObject, 
												sClosestHitData);

			// Compute the illumination for the closest object, assuming that there
			// was a valid intersection.
			if (bIntersectionFound)
			{
				qbVector4<double> vFinalColour;

				// Check if the object has a material.
				if (sClosestHitData.pHitObject->m_bHasMaterial)
				{
					// Use the material to compute the color.
					QBRT::QBMaterialBase::m_iMaxReflectionRayCount = 0;
					vFinalColour = sClosestHitData.pHitObject->m_pMaterial->ComputeColour(	m_vObjectList,
																							m_vLightList, 
																							sClosestHitData.pHitObject, 
																							sClosestHitData.vPointOfIntersection, 
																							sClosestHitData.vNormalAtPointOfIntersection, 
																							sClosestHitData.vLocalPointOfIntersection,
																							sClosestHitData.vUVCoords,
																							cameraRay);
				}
				else
				{
					// Use the basic method to compute the color.
					vFinalColour = QBRT::QBMaterialBase::ComputeDiffuseColour(	m_vObjectList,
																				m_vLightList, 
																				sClosestHitData.pHitObject, 
																				sClosestHitData.vPointOfIntersection,
																				sClosestHitData.vNormalAtPointOfIntersection,
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
								QBRT::DATA::HitData& sClosestHitData)
{
	QBRT::DATA::HitData	sHitData;

	double				fMinDist = 1e6;
	bool				bIntersectionFound = false;

	for (auto pCurrentObject : vObjectList)
	{
		if(pCurrentObject != pThisObject)
		{
			// Test if we have a valid intersection.
			bool bValidIntersection = pCurrentObject->TestIntersection(	castRay,
																		sHitData);

			// If we have a valid intersection.
			if (bValidIntersection)
			{
				// Set the flag to indicate that we found an intersection.
				bIntersectionFound = true;

				// Compute the distance between the camera and the point of intersection.
				double fDistance = (sHitData.vPointOfIntersection - castRay.m_vPoint1).norm();

				// If this object is closer to the camera than any one that we have
				// seen before, then store a reference to it.
				if (fDistance < fMinDist)
				{
					fMinDist = fDistance;
					pClosestObject = pCurrentObject;
					sClosestHitData = sHitData;
				}
			}
		}
	}

	return bIntersectionFound;
}