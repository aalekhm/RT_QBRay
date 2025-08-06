#include "QBPointLight.hpp"

#define USE_COSINE

// The default constructor.
QBRT::QBPointLight::QBPointLight()
{
	m_vLightColour = qbVector4<double>(1.0, 1.0, 1.0, 1.0);
	m_fLightIntensity = 1.0;
}

// Override the default destructor.
QBRT::QBPointLight::~QBPointLight()
{

}

// Function to compute illumination.
bool QBRT::QBPointLight::ComputeIllumination(	const qbVector3<double>& vIntersectionPoint,
												const qbVector3<double>& vLocalNormal,
												const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
												qbVector4<double>& vColour,
												double& fLightIntensity)
{
	// Construct a vector pointing from the intersection point to the light.
	qbVector3<double> vLightDir = (m_vLightPosition - vIntersectionPoint);
	vLightDir.Normalize();

	// Distance of the light source from the point of intersection.
	double fLightDistance = (m_vLightPosition - vIntersectionPoint).norm();
	
	// Compute a starting point.
	qbVector3<double> vStartPoint = vIntersectionPoint;

	// Construct a ray from the point of intersection to the light.
	QBRT::QBRay	lighRay(vStartPoint, vStartPoint + vLightDir);

	// Check for intersections with all of the objects
	// in the scene, except for the current one.
	qbVector3<double>	vPointOfIntersection;
	qbVector3<double>	vPointOfIntersectionNormal;
	qbVector4<double>	vPointOfIntersectionColour;
	bool				bValidIntersection = false;

	// Check to see if there is any object between the intersection point & the light
	for (auto pSceneObject : vObjectList)
	{
		if(pSceneObject != pCurrentObject)
		{
			// Test if we have a valid intersection.
			bValidIntersection = pSceneObject->TestIntersection(	lighRay,
																	vPointOfIntersection, 
																	vPointOfIntersectionNormal, 
																	vPointOfIntersectionColour);

			// Check for valid intersection only if the p[oint of intersection lies IN-BETWEEN the object & the light source.
			// Object < POINT OF INTERSECTION < LIGHT SOURCE
			if (bValidIntersection)
			{
				double fDistance = (vPointOfIntersection - vStartPoint).norm();
				if (fDistance > fLightDistance)
				{
					bValidIntersection = false;
				}
			}	
		}

		// If we have an intersection, then there is no point checking further
		// so we can break out of the loop. In other words, this object is
		// blocking light from this light source.
		if (bValidIntersection)
			break;
	}

	// Only continue to compute illumination if the light ray didn't
	// intersect with any objects in the scene. Ie. no objects are
	// casting a shadow from this light source.
	if (bValidIntersection == false)
	{
#ifdef USE_COSINE
		// Compute the angle between the local normal and the light ray.
		// Note that we assume that localNormal is a unit vector.
		// Cos(THETA) = vSurfaceNormal * vLightDir => Cos(THETA) = Projection of LightVector on the SurfaceNormal 
		// => Lesser the angle between LightVector & SurfaceNormal, higher the value of Cos(THETA)
		// => Higher the Light Intensity at that particular point on the surface.
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
#else
		qbVector<double> localNormal{ 3 };
		{
			localNormal.SetElement(0, vLocalNormal.x);
			localNormal.SetElement(1, vLocalNormal.y);
			localNormal.SetElement(2, vLocalNormal.z);
		}
		qbVector<double> lightDir{ 3 };
		{
			lightDir.SetElement(0, vLightDir.x);
			lightDir.SetElement(1, vLightDir.y);
			lightDir.SetElement(2, vLightDir.z);
		}

		// Compute the angle between the local normal and the light ray.
		// Note that we assume that localNormal is a unit vector.
		double angle = acos(qbVector<double>::dot(localNormal, lightDir));
		
		// If the normal is pointing away from the light, then we have no illumination.
		if (angle > 1.5708)
		{
			// No illumination.
			vColour = m_vLightColour;
			fLightIntensity = 0.0;
			return false;
		}
		else
		{
			// We do have illumination.
			vColour = m_vLightColour;
			fLightIntensity = m_fLightIntensity * (1.0 - (angle / 1.5708));
			return true;
		}
#endif
	}
	else
	{
		// Shadow, so no illumination.
		vColour = m_vLightColour;
		fLightIntensity = 0.0;

		return false;
	}
}
