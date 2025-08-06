#include "QBMaterialBase.hpp"
#include "qbRayTrace/QBScene.hpp"

// Constructor / destructor.
QBRT::QBMaterialBase::QBMaterialBase()
{
	m_iMaxReflectionRays = 3;
	m_iMaxReflectionRayCount = 0;
}

QBRT::QBMaterialBase::~QBMaterialBase()
{

}

// Function to return the color of the material.
qbVector4<double> QBRT::QBMaterialBase::ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
														const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
														const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
														const qbVector3<double>& vIntersectionPoint,
														const qbVector3<double>& vLocalNormal,
														const qbVector3<double>& vLocalIntersectionPoint,
														const qbVector2<double>& vUVCoords,
														const QBRT::QBRay& vCameraRay)
{
	// Define an initial material color.
	qbVector4<double> vMaterialColour;

	return vMaterialColour;
}

qbVector4<double> QBRT::QBMaterialBase::ComputeDiffuseColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																const qbVector3<double>& vIntersectionPoint,
																const qbVector3<double>& vLocalNormal,
																const qbVector4<double>& vBaseColour)
{
	// Compute the color due to diffuse illumination.
	qbVector4<double>	vDiffuseColour;
	double				fIntensity;
	qbVector4<double>	vColour;
	double				fRed = 0.0;
	double				fGreen = 0.0;
	double				fBlue = 0.0;
	bool				bValidIllumination = false;
	bool				bIlluminationFound = false;

	for (auto pCurrentLight : vLightList)
	{
		bValidIllumination = pCurrentLight->ComputeIllumination(	vIntersectionPoint, 
																	vLocalNormal, 
																	vObjectList, 
																	pCurrentObject, 
																	vColour, 
																	fIntensity);
		if (bValidIllumination)
		{
			bIlluminationFound = true;

			// The diffuse component.
			fRed += vColour.r * fIntensity;
			fGreen += vColour.g * fIntensity;
			fBlue += vColour.b * fIntensity;
		}
	}

	if (bIlluminationFound)
	{
		vDiffuseColour.r = fRed * vBaseColour.r;
		vDiffuseColour.g = fGreen * vBaseColour.g;
		vDiffuseColour.b = fBlue * vBaseColour.b;
		vDiffuseColour.a = 1.0;
	}
	else
	{
		// The ambient light condition.
		vDiffuseColour.r = (m_vAmbientColour.r * m_fAmbientIntensity) * vBaseColour.r;
		vDiffuseColour.g = (m_vAmbientColour.g * m_fAmbientIntensity) * vBaseColour.g;
		vDiffuseColour.b = (m_vAmbientColour.b * m_fAmbientIntensity) * vBaseColour.b;
		vDiffuseColour.a = 1.0;
	}

	// Return the material color.
	return vDiffuseColour;
}

// Function to compute diffuse color.
qbVector4<double> QBRT::QBMaterialBase::ComputeSpecularAndDiffuseColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																			const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																			const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																			const qbVector3<double>& vIntersectionPoint,
																			const qbVector3<double>& vLocalNormal,
																			const qbVector4<double>& vBaseColour,
																			const QBRT::QBRay& cameraRay)
{
	// Compute the color due to diffuse illumination and specular highlights.
	qbVector4<double>	vOutputColour;
	qbVector4<double>	vDiffuseColour;
	qbVector4<double>	vSpecularColour;
	double				fIntensity;
	double				fSpecularIntensity;
	qbVector4<double>	vColour;
	double				fRed = 0.0;
	double				fGreen = 0.0;
	double				fBlue = 0.0;
	double				fSpecularRed = 0.0;
	double				fSpecularGreen = 0.0;
	double				fSpecularBlue = 0.0;
	bool				bValidIllumination = false;
	bool				bIlluminationFound = false;

	for (auto pCurrentLight : vLightList)
	{
		bValidIllumination = pCurrentLight->ComputeIllumination(	vIntersectionPoint, 
																	vLocalNormal, 
																	vObjectList, 
																	nullptr, 
																	vColour, 
																	fIntensity);
		if (bValidIllumination)
		{
			bIlluminationFound = true;

			// The diffuse component.
			fRed += vColour.r * fIntensity;
			fGreen += vColour.g * fIntensity;
			fBlue += vColour.b * fIntensity;

			// The specular component.
			if ((m_fSpecular > 0.0) && (m_fShininess > 0.0))
			{
				fSpecularIntensity = 0.0;

				// Construct a vector pointing from the intersection point to the light.
				qbVector3<double>	vLightDirection = (pCurrentLight->m_vLightPosition - vIntersectionPoint).Normalized();

				// Compute a start point.
				qbVector3<double>	vStartPosition = vIntersectionPoint + (vLightDirection * 0.001);

				// Construct a ray from the point of intersection to the light.
				QBRT::QBRay			vLightRay(vStartPosition, vStartPosition + vLightDirection);

				// Compute the reflection vector.
				qbVector3<double> d = vLightRay.m_vDir;
				qbVector3<double> r = d - (2 * qbVector3<double>::dot(d, vLocalNormal) * vLocalNormal);
				
				// Compute the dot product.
				qbVector3<double> v = cameraRay.m_vDir;
				v.Normalize();

				double fDotProduct = qbVector3<double>::dot(r, v);

				// Only proceed if the dot product is positive.
				if (fDotProduct > 0.0)
				{
					fSpecularIntensity = m_fSpecular * std::pow(fDotProduct, m_fShininess);
				}

				fSpecularRed += pCurrentLight->m_vLightColour.r * fSpecularIntensity;
				fSpecularGreen += pCurrentLight->m_vLightColour.g * fSpecularIntensity;
				fSpecularBlue += pCurrentLight->m_vLightColour.b * fSpecularIntensity;
			}
		}
	}

	if (bIlluminationFound)
	{
		vDiffuseColour.r = fRed * vBaseColour.r;
		vDiffuseColour.g = fGreen * vBaseColour.g;
		vDiffuseColour.b = fBlue * vBaseColour.b;
		vDiffuseColour.a = 1.0;

		vSpecularColour.r = fSpecularRed;
		vSpecularColour.g = fSpecularGreen;
		vSpecularColour.b = fSpecularBlue;
		vSpecularColour.a = 1.0;
	}

	// The ambient light condition.
	vDiffuseColour.r = (vDiffuseColour.r + (m_vAmbientColour.r * m_fAmbientIntensity) * vBaseColour.r);
	vDiffuseColour.g = (vDiffuseColour.g + (m_vAmbientColour.g * m_fAmbientIntensity) * vBaseColour.g);
	vDiffuseColour.b = (vDiffuseColour.b + (m_vAmbientColour.b * m_fAmbientIntensity) * vBaseColour.b);
	vDiffuseColour.a = 1.0;

	// Compute the color due to specular highlights.
	vOutputColour = vDiffuseColour + vSpecularColour;

	// Return the material color.
	return vOutputColour;
}

// Function to compute the reflection color.
qbVector4<double> QBRT::QBMaterialBase::ComputeReflectionColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																	const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																	const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																	const qbVector3<double>& vIntersectionPoint,
																	const qbVector3<double>& vLocalNormal,
																	const QBRT::QBRay& vIncidentRay)
{
	qbVector4<double>	vReflectionColour;

	// Compute the reflection vector.
	qbVector3<double>	d = vIncidentRay.m_vDir;
	qbVector3<double>	vReflectionVector = d - (2 * qbVector3<double>::dot(d, vLocalNormal) * vLocalNormal);

	// Construct the reflection ray.
	qbVector3<double>	vStartPoint = vIntersectionPoint + (vLocalNormal * 0.001);
	QBRT::QBRay			reflectionRay(vStartPoint, vStartPoint + vReflectionVector);

	// Cast this ray into the scene and find the closest object that it intersects with.
	std::shared_ptr<QBRT::QBObjectBase> pClosestObject;
	QBRT::DATA::HitData					sClosestHitData;

	bool bIntesectionFound = QBRT::QBScene::CastRay(reflectionRay,
													vObjectList,
													pCurrentObject,
													pClosestObject,
													sClosestHitData);

	// Compute illumination for closest object assuming that there was a
	// valid intersection.
	qbVector4<double> vMaterialColour;
	if (bIntesectionFound && (m_iMaxReflectionRayCount < m_iMaxReflectionRays))
	{
		// Increment the reflectionRayCount.
		m_iMaxReflectionRayCount++;

		// Check if a material has been assigned.
		if (sClosestHitData.pHitObject->m_bHasMaterial)
		{
			// Use the material to compute the color.
			vMaterialColour = sClosestHitData.pHitObject->m_pMaterial->ComputeColour(	vObjectList,
																						vLightList, 
																						sClosestHitData.pHitObject, 
																						sClosestHitData.vPointOfIntersection, 
																						sClosestHitData.vNormalAtPointOfIntersection, 
																						sClosestHitData.vLocalPointOfIntersection,
																						sClosestHitData.vUVCoords,
																						reflectionRay);
		}
		else
		{
			vMaterialColour = QBRT::QBMaterialBase::ComputeDiffuseColour(	vObjectList, 
																			vLightList, 
																			sClosestHitData.pHitObject, 
																			sClosestHitData.vPointOfIntersection, 
																			sClosestHitData.vNormalAtPointOfIntersection, 
																			pClosestObject->m_vBaseColour);
		}
	}
	else
	{
		// Leave matColor as it is.
	}

	vReflectionColour = vMaterialColour;
	return vReflectionColour;
}

// Function to assign a texture.
void QBRT::QBMaterialBase::AssignTexture(const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& vInputTexture)
{
	m_vTextureList.push_back(vInputTexture);
	m_bHasTexture = true;
}

// *** Function to assign a normal map.
void QBRT::QBMaterialBase::AssignNormalMap(const std::shared_ptr<QBRT::QBNormal::QBNormalBase>& vInputNormalMap)
{
	m_vNormalMapList.push_back(vInputNormalMap);
	m_bHasNormalMap = true;
}

// Function to return the color due to textures at the given (u,v) coordinate.
qbVector4<double> QBRT::QBMaterialBase::GetTextureColor(const qbVector2<double> &uvCoords)
{
	qbVector4<double> vOutputColor;
	qbVector4<double> vFinalColor;
	
	if (m_vTextureList.size() > 1)
	{
		vOutputColor = m_vTextureList.at(0)->GetColor(uvCoords);
		for (int i=1; i< m_vTextureList.size(); ++i)
		{
			BlendColors(vOutputColor, m_vTextureList.at(i)->GetColor(uvCoords));
		}
	}
	else
	{
		vOutputColor = m_vTextureList.at(0)->GetColor(uvCoords);
	}
	
	vFinalColor.r = vOutputColor.r;
	vFinalColor.g = vOutputColor.g;
	vFinalColor.b = vOutputColor.b;
	vFinalColor.a = vOutputColor.a;

	return vFinalColor;
}

// *** Function to perturb the object normal to give the material normal.
qbVector3<double> QBRT::QBMaterialBase::PerturbNormal(	const qbVector3<double>& vNormal,
														const qbVector2<double>& vUVCoords,
														const qbVector3<double>& vUpVector)
{
	// Copy the original normal.
	qbVector3<double> vNewNormal = vNormal;
	
	// Perturb the new normal with each normal map in turn.
	for (int i = 0; i < m_vNormalMapList.size(); ++i)
	{
		vNewNormal = m_vNormalMapList.at(i)->ComputePerturbation(vNewNormal, vUVCoords);
	}

	// And return the output.
	return vNewNormal;
}

// Function to blend colors.
void QBRT::QBMaterialBase::BlendColors(qbVector4<double>& vColor1, const qbVector4<double>& vColor2)
{
	vColor1 = (vColor2 * vColor2.a) + (vColor1 * (1.0 - vColor2.a));
}
