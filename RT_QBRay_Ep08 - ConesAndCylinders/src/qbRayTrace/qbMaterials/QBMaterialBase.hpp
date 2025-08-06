#pragma once
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
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
			virtual	qbVector3<double>	ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
														const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
														const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
														const qbVector3<double>& vIntersectionPoint,
														const qbVector3<double>& vLocalNormal,
														const QBRT::QBRay& vCameraRay);

			// Function to compute diffuse color.
			static qbVector3<double>	ComputeDiffuseColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																const qbVector3<double>& vIntersectionPoint,
																const qbVector3<double>& vLocalNormal,
																const qbVector3<double>& vBaseColour);

			// Function to compute the reflection color.
			qbVector3<double>			ComputeReflectionColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& vIncidentRay);
		public:
			// Counter for the number of relection rays.
			inline static uint32_t	m_iMaxReflectionRays = 3;
			inline static uint32_t	m_iMaxReflectionRayCount = 0;
		private:
	};
}