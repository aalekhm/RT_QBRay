#include "QBSimpleRefractive.hpp"
#include "qbRayTrace/QBScene.hpp"

// Constructor / destructor.
QBRT::QBSimpleRefractive::QBSimpleRefractive()
{

}

QBRT::QBSimpleRefractive::QBSimpleRefractive(	const qbVector3<double>& vColour,
												double fReflectivity, 
												double fShininess,
												double fTranslucency,
												double fIOR)
: m_vBaseColour(vColour)
, m_fReflectivity(fReflectivity)
, m_fShininess(fShininess)
, m_fTranslucency(fTranslucency)
, m_fIOR(fIOR)
{

}


QBRT::QBSimpleRefractive::~QBSimpleRefractive()
{

}

// Function to return the color of the material.
qbVector3<double> QBRT::QBSimpleRefractive::ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
															const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
															const qbVector3<double>& vIntersectionPoint,
															const qbVector3<double>& vLocalNormal,
															const QBRT::QBRay& cameraRay)
{
	// Define the initial material colors.
	qbVector3<double>	vMaterialColour;
	qbVector3<double>	vReflectionColour;
	qbVector3<double>	vDiffuseColour;
	qbVector3<double>	vSpecularColour;
	qbVector3<double>	vTranslucentColour;

	// Compute the diffuse component.
	if (!m_bHasTexture)
	{
		vDiffuseColour = ComputeDiffuseColour(	vObjectList, 
												vLightList, 
												pCurrentObject, 
												vIntersectionPoint, 
												vLocalNormal, 
												m_vBaseColour);
	}
	else 
	{
		vDiffuseColour = ComputeDiffuseColour(	vObjectList, 
												vLightList, 
												pCurrentObject, 
												vIntersectionPoint, 
												vLocalNormal, 
												m_vTextureList[0]->GetColor(pCurrentObject->m_vUVCoords));
	}

	// Compute the reflection component.
	if (m_fReflectivity > 0.0)
	{
		vReflectionColour = ComputeReflectionColour(	vObjectList, 
														vLightList, 
														pCurrentObject, 
														vIntersectionPoint, 
														vLocalNormal, 
														cameraRay);
	}

	// Combine the reflection and diffuse components.
	vMaterialColour = (vReflectionColour * m_fReflectivity) + (vDiffuseColour * (1.0 - m_fReflectivity));

	// Compute the refractive component.
	if (m_fTranslucency > 0.0)
	{
		vTranslucentColour = ComputeTranslucency(	vObjectList, 
													vLightList, 
													pCurrentObject, 
													vIntersectionPoint, 
													vLocalNormal, 
													cameraRay);
	}

	// And combine with the current color.
	vMaterialColour = (vTranslucentColour * m_fTranslucency) + (vMaterialColour * (1.0 - m_fTranslucency));

	// And compute the specular component.
	if (m_fShininess > 0.0)
	{
		vSpecularColour = ComputeSpecular(	vObjectList, 
											vLightList, 
											vIntersectionPoint, 
											vLocalNormal, 
											cameraRay);
	}

	// Finally, add the specular component.
	vMaterialColour = vMaterialColour + vSpecularColour;
	
	return vMaterialColour;

}

// Function to compute specular highlights.
qbVector3<double> QBRT::QBSimpleRefractive::ComputeSpecular(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																const qbVector3<double>& vIntersectionPoint,
																const qbVector3<double>& vLocalNormal,
																const QBRT::QBRay& cameraRay)
{
	qbVector3<double> vSpecularColour;
	double fRed = 0.0;
	double fGreen = 0.0;
	double fBlue = 0.0;
	
	// Loop through all of the lights in the scene.
	for (auto pCurrentLight : vLightList)
	{
		/* Check for intersections with all objects in the scene. */
		double fIntensity = 0.0;
		
		// Construct a vector pointing from the intersection point to the light.
		qbVector3<double> vLightDir = (pCurrentLight->m_vLightPosition - vIntersectionPoint).Normalized();
		
		// Compute a start point.
		qbVector3<double> vStartPoint = vIntersectionPoint + (vLightDir * 0.001);
		
		// Construct a ray from the point of intersection to the light.
		QBRT::QBRay lightRay (vStartPoint, vStartPoint + vLightDir);
		
		/* Loop through all objects in the scene to check if any
			obstruct light from this source. */
		qbVector3<double> vPointOfIntersection;
		qbVector3<double> vPointOfIntersectionNormal;
		qbVector3<double> vPointOfIntersectionColor;

		bool bValidInt = false;
		for (auto pSceneObject : vObjectList)
		{
			bValidInt = pSceneObject->TestIntersection(	lightRay, 
														vPointOfIntersection, 
														vPointOfIntersectionNormal, 
														vPointOfIntersectionColor);
			if (bValidInt)
				break;
		}
		
		// If no intersections were found, then proceed with
		// computing the specular component.
		if (bValidInt == false)
		{
			// Compute the reflection vector.
			qbVector3<double> d = lightRay.m_vDir;
			qbVector3<double> r = d - (2 * qbVector3<double>::dot(d, vLocalNormal) * vLocalNormal);
			r.Normalize();
			
			// Compute the dot product.
			qbVector3<double> v = cameraRay.m_vDir;
			v.Normalize();
			double fDotProduct = qbVector3<double>::dot(r, v);
			
			// Only proceed if the dot product is positive.
			if (fDotProduct > 0.0)
			{
				fIntensity = m_fReflectivity * std::pow(fDotProduct, m_fShininess);
			}
		}
		
		fRed	+= pCurrentLight->m_vLightColour.r * fIntensity;
		fGreen	+= pCurrentLight->m_vLightColour.g * fIntensity;
		fBlue	+= pCurrentLight->m_vLightColour.b * fIntensity;
	}
	
	vSpecularColour.r = fRed;
	vSpecularColour.g = fGreen;
	vSpecularColour.b = fBlue;

	return vSpecularColour;
}

// Function to compute translucency.
qbVector3<double> QBRT::QBSimpleRefractive::ComputeTranslucency(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& incidentRay)
{
	qbVector3<double> vTranslucencyColor;
	
	// Compute the refracted vector.
	// let r = n1/n2
	// c = cos(THETA1) = -vNormal.vIncident
	// vRefracted = r.vIncident + ( r.c - sqrt(1 - r^2(1 - c^2))).vNormal
	qbVector3<double> vIncident = incidentRay.m_vDir;
	vIncident.Normalize();
	qbVector3<double> vTempNormal = vLocalNormal;
	double r = 1.0 / m_fIOR;
	double c = -qbVector3<double>::dot(vTempNormal, vIncident);
	if (c < 0.0)
	{
		vTempNormal = vTempNormal * -1.0;
		c = -qbVector3<double>::dot(vTempNormal, vIncident);
	}
	
	qbVector3<double> vRefracted = r* vIncident + (r*c - sqrtf(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))) * vTempNormal;
	
	// Construct the refracted ray.
	QBRT::QBRay refractedRay (vIntersectionPoint + (vRefracted * 0.01), vIntersectionPoint + vRefracted);
	
	// Test for secondary intersection with this object.
	std::shared_ptr<QBRT::QBObjectBase>		pClosestObject;
	qbVector3<double> vClosestIntersectionPoint;
	qbVector3<double> vClosestLocalNormal;
	qbVector3<double> vClosestLocalColor;
	qbVector3<double> vNewIntersectionPoint;
	qbVector3<double> vNewLocalNormal;
	qbVector3<double> vNewLocalColor;

	bool bTest = pCurrentObject->TestIntersection(	refractedRay, 
													vNewIntersectionPoint, 
													vNewLocalNormal, 
													vNewLocalColor);
	bool bIntersectionFound = false;
	QBRT::QBRay finalRay;
	if (bTest)
	{
		// Compute the refracted vector.
		qbVector3<double> p2 = refractedRay.m_vDir;
		p2.Normalize();
		qbVector3<double> vTempNormal2 = vNewLocalNormal;
		double r2 = m_fIOR;
		double c2 = -qbVector3<double>::dot(vTempNormal2, p2);
		if (c2 < 0.0)
		{
			vTempNormal2 = vTempNormal2 * -1.0;
			c2 = -qbVector3<double>::dot(vTempNormal2, p2);
		}

		qbVector3<double> vRefractedVector2 = r2*p2 + (r2*c2 - sqrtf(1.0 - pow(r2, 2.0) * (1.0 - pow(c2, 2.0)))) * vTempNormal2;
		
		// Compute the refracted ray.
		QBRT::QBRay refractedRay2(vNewIntersectionPoint + (vRefractedVector2 * 0.01), vNewIntersectionPoint + vRefractedVector2);
		
		// Cast this ray into the scene.
		bIntersectionFound = QBRT::QBScene::CastRay(	refractedRay2, 
														vObjectList, 
														pCurrentObject, 
														pClosestObject, 
														vClosestIntersectionPoint, 
														vClosestLocalNormal, 
														vClosestLocalColor);
		finalRay = refractedRay2;
	}
	else
	{
		/* No secondary intersections were found, so continue the original refracted ray. */
		bIntersectionFound = QBRT::QBScene::CastRay(	refractedRay, 
														vObjectList, 
														pCurrentObject, 
														pClosestObject, 
														vClosestIntersectionPoint, 
														vClosestLocalNormal, 
														vClosestLocalColor);
		finalRay = refractedRay;
	}
	
	// Compute the color for closest object.
	qbVector3<double> vMaterialColor;
	if (bIntersectionFound)
	{
		// Check if a material has been assigned.
		if (pClosestObject -> m_bHasMaterial)
		{
			vMaterialColor = pClosestObject->m_pMaterial->ComputeColour(	vObjectList, 
																			vLightList, 
																			pClosestObject, 
																			vClosestIntersectionPoint, 
																			vClosestLocalNormal, 
																			finalRay);
		}
		else
		{
			vMaterialColor = QBRT::QBMaterialBase::ComputeDiffuseColour(	vObjectList, 
																			vLightList, 
																			pClosestObject, 
																			vClosestIntersectionPoint, 
																			vClosestLocalNormal, 
																			pClosestObject->m_vBaseColour);
		}
	}
	else
	{
		// Leave matColor as it is.
	}
	
	vTranslucencyColor = vMaterialColor;
	return vTranslucencyColor;
}
