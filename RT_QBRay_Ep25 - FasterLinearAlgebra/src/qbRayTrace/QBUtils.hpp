#pragma once
#include "qbLinAlg/qbVector2.hpp"
#include "qbLinAlg/qbVector3.hpp"
#include "qbLinAlg/qbMatrix44.hpp"

#include <cmath>
#include <array>

#define USE_BILINEARINTERPOLATION 0

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
#define	MAKE_POSITION2(_X_, _Y_)	qbVector2<double>(_X_, _Y_)
#define	MAKE_ROTATION2(_X_, _Y_)	qbVector2<double>(_X_, _Y_)
#define	MAKE_SCALE2(_X_, _Y_)		qbVector2<double>(_X_, _Y_)

#define ADD_PLANE(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_) QBRT::QBUtils::AddPlane(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_);
#define ADD_SPHERE(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_) QBRT::QBUtils::AddSphere(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_);
#define ADD_CYLINDER(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_, __ADDTOLIST__) QBRT::QBUtils::AddCylinder(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_, __ADDTOLIST__);
#define ADD_CONE(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_, __ADDTOLIST__) QBRT::QBUtils::AddCone(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_, __ADDTOLIST__);
#define ADD_BOX(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_) QBRT::QBUtils::AddBox(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_);
#define ADD_RM_CUBE(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_) QBRT::QBUtils::AddRMCube(		_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_);
#define ADD_RM_TORUS(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _RADII1_, _RADII2_, _FRIENDLY_NAME_) QBRT::QBUtils::AddRMTorus(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _RADII1_, _RADII2_, _FRIENDLY_NAME_);
#define ADD_RM_SPHERE(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_) QBRT::QBUtils::AddRMSphere(	_OBJLIST_, _TRANSLATION_, _ROTATION_, _SCALING_, _MATERIAL_, _FRIENDLY_NAME_);

namespace QBRT
{
	class QBObjectBase;
	class QBMaterialBase;
	class QBLightBase;
	class QBPointLight;

	namespace DATA
	{
		struct HitData
		{
			qbVector3<double>						vPointOfIntersection;
			qbVector3<double>						vNormalAtPointOfIntersection;
			qbVector4<double>						vColourAtPointOfIntersection;
			qbVector3<double>						vLocalPointOfIntersection;
			qbVector2<double>						vUVCoords;
			std::shared_ptr<QBRT::QBObjectBase>		pHitObject;
		};
	}

	class QBObjectBase;
	class QBObjectSphere;
	class QBObjectPlane;
	class QBBox;
	class QBCylinder;
	class QBCone;
	namespace RM
	{
		class QBRMCube;
		class QBRMTorus;
		class QBRMSphere;
	}

	class QBUtils
	{
		public:
			static uint32_t			m_iCurrentPixelX;
			static uint32_t			m_iCurrentPixelY;

			static std::string		GetProjectName();

			static void				PrintVector(const char* sString, const qbVector3<double>& inputVector);
			static void				PrintVector(const uint32_t iX, const uint32_t iY, const char* sString, const qbVector3<double>& vInputVector);

			static std::shared_ptr<QBRT::RM::QBRMCube> AddRMCube(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const qbVector3<double>& vTranslation,
																	const qbVector3<double>& vRotation,
																	const qbVector3<double>& vScaling,
																	const std::shared_ptr<QBRT::QBMaterialBase>& material,
																	const std::string& sFriendlyName = "");

			static std::shared_ptr<QBRT::RM::QBRMTorus> AddRMTorus(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const qbVector3<double>& vTranslation,
																	const qbVector3<double>& vRotation,
																	const qbVector3<double>& vScaling,
																	const std::shared_ptr<QBRT::QBMaterialBase>& material,
																	double fRadii1, double fRadii2,
																	const std::string& sFriendlyName = "");

			static std::shared_ptr<QBRT::RM::QBRMSphere> AddRMSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																		const qbVector3<double>& vTranslation,
																		const qbVector3<double>& vRotation,
																		const qbVector3<double>& vScaling,
																		const std::shared_ptr<QBRT::QBMaterialBase>& material,
																		const std::string& sFriendlyName = "");

			static std::shared_ptr<QBRT::QBObjectSphere> AddSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const qbVector3<double>& vTranslation,
																	const qbVector3<double>& vRotation,
																	const qbVector3<double>& vScaling,
																	const std::shared_ptr<QBRT::QBMaterialBase>& material,
																	const std::string& sFriendlyName = "");

			static std::shared_ptr<QBRT::QBObjectPlane> AddPlane(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const qbVector3<double>& vTranslation,
																	const qbVector3<double>& vRotation,
																	const qbVector3<double>& vScaling,
																	const std::shared_ptr<QBRT::QBMaterialBase>& material,
																	const std::string& sFriendlyName = "");

			static std::shared_ptr<QBRT::QBCylinder> AddCylinder(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const qbVector3<double>& vTranslation,
																	const qbVector3<double>& vRotation,
																	const qbVector3<double>& vScaling,
																	const std::shared_ptr<QBRT::QBMaterialBase>& material,
																	const std::string& sFriendlyName = "",
																	bool bAddToList = true);

			static std::shared_ptr<QBRT::QBCone> AddCone(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const qbVector3<double>& vTranslation,
															const qbVector3<double>& vRotation,
															const qbVector3<double>& vScaling,
															const std::shared_ptr<QBRT::QBMaterialBase>& material,
															const std::string& sFriendlyName = "",
															bool bAddToList = true);

			static std::shared_ptr<QBRT::QBBox> AddBox(		std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const qbVector3<double>& vTranslation,
															const qbVector3<double>& vRotation,
															const qbVector3<double>& vScaling,
															const std::shared_ptr<QBRT::QBMaterialBase>& material,
															const std::string& sFriendlyName = "");

			static QBRT::QBPointLight* AddLight(	std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
													const qbVector3<double>& vPosition,
													const qbVector4<double>& vColour);

			static void					CreateTexture(	const qbVector3<double>& vTranslation,
														const qbVector3<double>& vRotation,
														const qbVector3<double>& vScaling,
														const std::shared_ptr<QBRT::QBMaterialBase>& material);

			// Functions to handle interpolation.
			static double				LinearInterp(	const double &x0, 
														const double &y0, 
														const double &x1, 
														const double &y1, 
														const double &x);
			static double				BilinearInterp(	const double &x0, const double &y0, const double &v0,
														const double &x1, const double &y1, const double &v1,
														const double &x2, const double &y2, const double &v2,
														const double &x3, const double &y3, const double &v3,
														const double &x, const double &y);

	};
}
