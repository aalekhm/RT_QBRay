#include "QBSimpleMaterial.hpp"


// Constructor / destructor.
QBRT::QBSimpleMaterial::QBSimpleMaterial()
{

}

QBRT::QBSimpleMaterial::QBSimpleMaterial(const qbVector3<double>& vColour, double fReflectivity, double fShininess)
: m_vBaseColour(vColour)
, m_fReflectivity(fReflectivity)
, m_fShininess(fShininess)
{
}

QBRT::QBSimpleMaterial::~QBSimpleMaterial()
{
	
}

// Function to return the color of the material.
qbVector3<double> QBRT::QBSimpleMaterial::ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
															const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
															const qbVector3<double>& vIntersectionPoint,
															const qbVector3<double>& vLocalNormal,
															const QBRT::QBRay& vCameraRay)
{
	// Define the initial material colors.
	qbVector3<double>		vMaterialColour;
	qbVector3<double>		vReflectionColour;
	qbVector3<double>		vDiffuseColour;
	qbVector3<double>		vSpecularColour;

	// Compute the diffuse component.
	vDiffuseColour = ComputeDiffuseColour(vObjectList, vLightList, pCurrentObject, vIntersectionPoint, vLocalNormal, m_vBaseColour);

	// Compute the reflection component.
	if (m_fReflectivity > 0.0)
	{
		vReflectionColour = ComputeReflectionColour(vObjectList, vLightList, pCurrentObject, vIntersectionPoint, vLocalNormal, vCameraRay);
	}

	// Combine reflection and diffuse components.
	vMaterialColour = (vReflectionColour * m_fReflectivity) + (vDiffuseColour * (1 - m_fReflectivity));

	// Compute the specular component.
	if (m_fShininess > 0.0)
	{
		vSpecularColour = ComputeSpecularColour(vObjectList, vLightList, vIntersectionPoint, vLocalNormal, vCameraRay);
	}

	// Add the specular component to the final color.
	vMaterialColour = vMaterialColour + vSpecularColour;

	return vMaterialColour;
}

// Function to compute specular highlights.
qbVector3<double> QBRT::QBSimpleMaterial::ComputeSpecularColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& vCameraRay)
{
	qbVector3<double>		vSpecularColour;
	double					fRed = 0.0;
	double					fGreen = 0.0;
	double					fBlue = 0.0;

	// Loop through all of the lights in the scene.
	for (auto pCurrentLight : vLightList)
	{
		/* Check for intersections with all objects in the scene. */
		double	fIntensity = 0.0;

		// Construct a vector pointing from the intersection point to the light.
		qbVector3<double>	vLightDirection = (pCurrentLight->m_vLightPosition - vIntersectionPoint).Normalized();

		// Compute a start point.
		qbVector3<double>	vStartPosition = vIntersectionPoint + (vLightDirection * 0.001);

		// Construct a ray from the point of intersection to the light.
		QBRT::QBRay			vLightRay(vStartPosition, vStartPosition + vLightDirection);

		// Loop through all objects in the scene to check if any
		// obstruct light from this source.
		qbVector3<double>	vPointOfIntersection;
		qbVector3<double>	vPointOfIntersectionNormal;
		qbVector3<double>	vPointOfIntersectionColour;
		bool				bValidIntersection = false;
		for (auto pCurrentObject : vObjectList)
		{
			bValidIntersection = pCurrentObject->TestIntersection(vLightRay, vPointOfIntersection, vPointOfIntersectionNormal, vPointOfIntersectionColour);
			if (bValidIntersection)
				break;
		}

		// If no intersections were found, then proceed with
		// computing the specular component.
		if (bValidIntersection == false)
		{
			// Compute the reflection vector.
			qbVector3<double> d = vLightRay.m_vDir;
			qbVector3<double> r = d - (2 * qbVector3<double>::dot(d, vLocalNormal) * vLocalNormal);
			r.Normalize();

			// Compute the dot product.
			qbVector3<double> v = vCameraRay.m_vDir;
			v.Normalize();

			double fDotProduct = qbVector3<double>::dot(r, v);

			// Only proceed if the dot product is positive.
			if (fDotProduct > 0.0)
			{
				fIntensity = m_fReflectivity * std::pow(fDotProduct, m_fShininess);
			}
		}

		fRed += pCurrentLight->m_vLightColour.r * fIntensity;
		fGreen += pCurrentLight->m_vLightColour.g * fIntensity;
		fBlue += pCurrentLight->m_vLightColour.b * fIntensity;
	}

	vSpecularColour.r = fRed;
	vSpecularColour.g = fGreen;
	vSpecularColour.b = fBlue;

	return vSpecularColour;
}
