#pragma once

#include <memory>
#include "qbLinAlg/qbVector3.hpp"
#include "QBRay.hpp"
#include "QBObjectBase.hpp"

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
												std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												std::shared_ptr<QBRT::QBObjectBase>& currentObject,
												qbVector3<double>& vColour,
												double& fLightIntensity);
		public:
			qbVector3<double>	m_vLightColour;
			qbVector3<double>	m_vLightPosition;
			double				m_fLightIntensity;
	};
}