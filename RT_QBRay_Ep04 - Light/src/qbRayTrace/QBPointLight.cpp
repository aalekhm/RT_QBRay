#include "QBPointLight.hpp"

// The default constructor.
QBRT::QBPointLight::QBPointLight()
{
	m_vLightColour = qbVector3<double>(1.0, 1.0, 1.0);
	m_fLightIntensity = 1.0;
}

// Override the default destructor.
QBRT::QBPointLight::~QBPointLight()
{

}

// Function to compute illumination.
bool QBRT::QBPointLight::ComputeIllumination(	const qbVector3<double>& vIntersectionPoint,
												const qbVector3<double>& vLocalNormal,
												std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												std::shared_ptr<QBRT::QBObjectBase>& currentObject,
												qbVector3<double>& vColour,
												double& fLightIntensity
) {
	// Construct a vector pointing from the intersection point to the light.
	qbVector3<double> vLightDir = (m_vLightPosition - vIntersectionPoint).Normalized();
	
	// Compute a starting point.
	qbVector3<double> vStartPoint = vIntersectionPoint;

	// Compute the angle between the local normal and the light ray.
	// Note that we assume that localNormal is a unit vector.
	double fCosineAngle = qbVector3<double>::dot(vLocalNormal, vLightDir);

	// If the normal is pointing away from the light, then we have no illumination.
	// No Angle, cos(0) = 1.0
	// Right Angle, cos(90) = 0.0
	if (fCosineAngle > 0)
	{
		// We do have illumination.
		vColour = m_vLightColour;

		// Normalize the light intensity wrt the angle. 
		fLightIntensity = m_fLightIntensity * fCosineAngle;

		return true;
	}
	else
	{
		// No illumination.
		vColour = m_vLightColour;
		fLightIntensity = 0.0;

		return false;
	}

	return true;
}
