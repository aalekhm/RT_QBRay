#include "QBSimpleMaterial.hpp"


// Constructor / destructor.
QBRT::QBSimpleMaterial::QBSimpleMaterial()
{

}

QBRT::QBSimpleMaterial::QBSimpleMaterial(const qbVector4<double>& vColour, double fReflectivity, double fShininess)
: m_vBaseColour(vColour)
, m_fReflectivity(fReflectivity)
{
}

QBRT::QBSimpleMaterial::~QBSimpleMaterial()
{
	
}

// Function to return the color of the material.
qbVector4<double> QBRT::QBSimpleMaterial::ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
															const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
															const qbVector3<double>& vIntersectionPoint,
															const qbVector3<double>& vLocalNormal,
															const qbVector3<double>& vLocalIntersectionPoint,
															const qbVector2<double>& vUVCoords,
															const QBRT::QBRay& cameraRay)
{
	// Define the initial material colors.
	qbVector4<double>		vMaterialColour;
	qbVector4<double>		vReflectionColour;
	qbVector4<double>		vDiffuseAndSpecularColour;

	// *** Apply any normals maps that may have been assigned.
	qbVector3<double> vNewNormal = vLocalNormal;
	if (m_bHasNormalMap)
	{
		qbVector3<double> vUpVector = std::vector<double> {0.0, 0.0, -1.0};

		/* We modify this code to get the UV coords directly from the hitData structure,
			as they are no longer stored in the object itself. */
		vNewNormal = PerturbNormal(vNewNormal, vUVCoords, vUpVector);
	}
	
	// *** Store the current local normal, in case it is needed elsewhere.
	m_vLocalNormal = vNewNormal;	

	/* Note the change of localNormal to newNormal wherever the normal is used
	in the code below. */

	// Compute the diffuse component.
	if (m_bHasTexture)
	{
		vDiffuseAndSpecularColour = ComputeSpecularAndDiffuseColour(	vObjectList,
																		vLightList, 
																		pCurrentObject, 
																		vIntersectionPoint, 
																		vNewNormal, 
																		GetTextureColor(vUVCoords),
																		cameraRay);
	}
	else
	{
		vDiffuseAndSpecularColour = ComputeSpecularAndDiffuseColour(	vObjectList,
																		vLightList, 
																		pCurrentObject, 
																		vIntersectionPoint, 
																		vNewNormal, 
																		m_vBaseColour,
																		cameraRay);
	}

	// Compute the reflection component.
	if (m_fReflectivity > 0.0)
	{
		vReflectionColour = ComputeReflectionColour(vObjectList, vLightList, pCurrentObject, vIntersectionPoint, vNewNormal, cameraRay);
	}

	// Combine reflection and diffuse components.
	vMaterialColour = (vReflectionColour * m_fReflectivity) + (vDiffuseAndSpecularColour * (1 - m_fReflectivity));

	return vMaterialColour;
}

// Function to compute specular highlights.
qbVector4<double> QBRT::QBSimpleMaterial::ComputeSpecularColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& vCameraRay)
{
	qbVector4<double>		vSpecularColour;
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
		QBRT::DATA::HitData	sHitData;

		// Loop through all objects in the scene to check if any
		// obstruct light from this source.
		bool				bValidIntersection = false;
		for (auto pCurrentObject : vObjectList)
		{
			bValidIntersection = pCurrentObject->TestIntersection(vLightRay, sHitData);
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
	vSpecularColour.a = 1.0;

	return vSpecularColour;
}
