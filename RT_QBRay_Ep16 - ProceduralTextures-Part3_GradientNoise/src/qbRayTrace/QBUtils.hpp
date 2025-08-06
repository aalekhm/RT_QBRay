#pragma once
#include "qbLinAlg/qbVector3.hpp"
#include "qbLinAlg/qbMatrix44.hpp"
#include "qbPrimitives/QBObjectBase.hpp"
#include "qbLights/QBLightBase.hpp"

#include <cmath>
#include <array>

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720
#define ASPECT_RATIO	16.0 / 9.0
#define ONE_OVER_255	1.0 / 255.0
//#define TEXTURE_RENDER_TEST

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define	MAKE_POSITION(_X_, _Y_, _Z_)	qbVector3<double>(_X_, _Y_, _Z_)
#define	MAKE_ROTATION(_X_, _Y_, _Z_)	qbVector3<double>(_X_, _Y_, _Z_)
#define	MAKE_SCALE(_X_, _Y_, _Z_)		qbVector3<double>(_X_, _Y_, _Z_)
#define MAKE_COLOUR(_R_, _G_, _B_, _A_)		qbVector4<double>(_R_, _G_, _B_, _A_)
#define MAKE_SIMPLE_MATERIAL(_MAT_COLOUR_, _REFLECTIVITY_, _SHININESS_) std::make_shared<QBRT::QBSimpleMaterial>(_MAT_COLOUR_, _REFLECTIVITY_, _SHININESS_)
#define MAKE_SIMPLE_REFRACTIVE_MATERIAL(_MAT_COLOUR_, _REFLECTIVITY_, _SHININESS_, __TRANSLUCENCY__, __IOR__) std::make_shared<QBRT::QBSimpleRefractive>(_MAT_COLOUR_, _REFLECTIVITY_, _SHININESS_, __TRANSLUCENCY__, __IOR__)

namespace QBRT
{
	class QBPointLight;
	class QBUtils
	{
		public:
			static uint32_t			m_iCurrentPixelX;
			static uint32_t			m_iCurrentPixelY;

			static std::string		GetProjectName();

			static void				PrintVector(const char* sString, const qbVector3<double>& inputVector);
			static void				PrintVector(const uint32_t iX, const uint32_t iY, const char* sString, const qbVector3<double>& vInputVector);

			static void	AddRMCube(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void	AddRMTorus(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material,
									double fRadii1, double fRadii2);

			static void AddRMSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
										const qbVector3<double>& vTranslation,
										const qbVector3<double>& vRotation,
										const qbVector3<double>& vScaling,
										const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void AddSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList, 
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void AddPlane(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void AddCylinder(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
										const qbVector3<double>& vTranslation,
										const qbVector3<double>& vRotation,
										const qbVector3<double>& vScaling,
										const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void AddCone(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static void AddBox(		std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material);

			static QBRT::QBPointLight* AddLight(	std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
													const qbVector3<double>& vPosition,
													const qbVector4<double>& vColour);

			static void					CreateTexture(	const qbVector3<double>& vTranslation,
														const qbVector3<double>& vRotation,
														const qbVector3<double>& vScaling,
														const std::shared_ptr<QBRT::QBMaterialBase>& material);
	};
}
