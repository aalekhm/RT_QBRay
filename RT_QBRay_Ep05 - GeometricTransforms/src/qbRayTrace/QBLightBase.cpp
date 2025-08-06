#include "QBLightBase.hpp"

// Constructor.
QBRT::QBLightBase::QBLightBase()
{

}

// Destructor.
QBRT::QBLightBase::~QBLightBase()
{

}

// Function to compute illumination contribution.
bool QBRT::QBLightBase::ComputeIllumination(	const qbVector3<double>& vIntersectionPoint,
												const qbVector3<double>& vLocalNormal,
												std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												std::shared_ptr<QBRT::QBObjectBase>& currentObject,
												qbVector3<double>& vColour,
												double& fLightIntensity
) {
	return false;
}
