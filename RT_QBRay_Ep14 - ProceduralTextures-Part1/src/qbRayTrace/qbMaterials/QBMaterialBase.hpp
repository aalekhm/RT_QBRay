#pragma once
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/qbTextures/QBTextureBase.hpp"
#include "qbRayTrace/qbLights/QBLightBase.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/QBRay.hpp"


namespace QBRT
{
	class QBMaterialBase
	{
		public:
			QBMaterialBase();
			virtual ~QBMaterialBase();

			// Function to return the color of the material.
			virtual	qbVector4<double>	ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
														const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
														const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
														const qbVector3<double>& vIntersectionPoint,
														const qbVector3<double>& vLocalNormal,
														const QBRT::QBRay& vCameraRay);

			// Function to compute diffuse color.
			static qbVector4<double>	ComputeDiffuseColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																const qbVector3<double>& vIntersectionPoint,
																const qbVector3<double>& vLocalNormal,
																const qbVector4<double>& vBaseColour);

			// Function to compute the reflection color.
			qbVector4<double>			ComputeReflectionColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& vIncidentRay);

			// Function to assign a texture.
			void						AssignTexture(const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& vInputTexture);

			// Function to return the color due to the textures at the given (u,v) coordinate.
			qbVector4<double>			GetTextureColor(const qbVector2<double>& vUVCoords);

			// Function to blend RGBA colors (blends into color1).
			void						BlendColors(qbVector4<double>& vColor1, const qbVector4<double>& vColor2);
		public:
			// Counter for the number of relection rays.
			inline static uint32_t	m_iMaxReflectionRays = 3;
			inline static uint32_t	m_iMaxReflectionRayCount = 0;

			// The ambient lighting conditions.
			inline static qbVector4<double>		m_vAmbientColour{ 1.0, 1.0, 1.0, 1.0 };
			inline static double				m_fAmbientIntensity = 0.2;

			// List of texures assigned to this material.
			std::vector<std::shared_ptr<QBRT::QBTexture::QBTextureBase>>	m_vTextureList;

			// Flat to indicate whether at least one texture has been assigned.
			bool															m_bHasTexture = false;
		private:
	};
}