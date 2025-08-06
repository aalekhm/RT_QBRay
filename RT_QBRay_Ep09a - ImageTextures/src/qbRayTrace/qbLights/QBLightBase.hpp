#pragma once

#include <memory>
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/QBRay.hpp"
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"

namespace QBRT
{
	class QBLightBase
	{
		public:
			// Constructor / destructor.
			QBLightBase();
			virtual ~QBLightBase();

			// Function to compute illumination contribution.
			virtual bool ComputeIllumination(	const qbVector3<double>& vIntersectionPoint,
												const qbVector3<double>& vLocalNormal,
												const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												const std::shared_ptr<QBRT::QBObjectBase>& currentObject,
												qbVector3<double>& vColour,
												double& fLightIntensity);
		public:
			qbVector3<double>	m_vLightColour;
			qbVector3<double>	m_vLightPosition;
			double				m_fLightIntensity;
	};
}