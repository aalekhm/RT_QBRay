#pragma once

#include "QBLightBase.hpp"

namespace QBRT
{
	class QBPointLight : public QBLightBase
	{
		public:
			// The default constructor.
			QBPointLight();

			// Override the default destructor.
			virtual ~QBPointLight();

			// Function to compute illumination.
			virtual bool ComputeIllumination(	const qbVector3<double>& vIntersectionPoint,
												const qbVector3<double>& vLocalNormal,
												std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												std::shared_ptr<QBRT::QBObjectBase>& currentObject,
												qbVector3<double>& vColour,
												double& fLightIntensity);
	};
}