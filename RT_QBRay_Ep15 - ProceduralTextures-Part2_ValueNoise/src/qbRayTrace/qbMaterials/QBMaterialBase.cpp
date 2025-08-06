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
														const QBRT::QBRay& vCameraRay)
{
	// Define an initial material color.
	qbVector4<double> vMaterialColour;

	return vMaterialColour;
}

// Function to compute diffuse color.
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
	QBRT::QBRay			reflectionRay(vIntersectionPoint, vIntersectionPoint + vReflectionVector);

	// Cast this ray into the scene and find the closest object that it intersects with.
	std::shared_ptr<QBRT::QBObjectBase> pClosestObject;
	qbVector3<double>					vClosestIntersectionPoint;
	qbVector3<double>					vClosestLocalNormal;
	qbVector4<double>					vClosestLocalColour;

	bool bIntesectionFound = QBRT::QBScene::CastRay(	reflectionRay,
														vObjectList,
														pCurrentObject,
														pClosestObject,
														vClosestIntersectionPoint,
														vClosestLocalNormal,
														vClosestLocalColour);

	// Compute illumination for closest object assuming that there was a
	// valid intersection.
	qbVector4<double> vMaterialColour;
	if (bIntesectionFound && (m_iMaxReflectionRayCount < m_iMaxReflectionRays))
	{
		// Increment the reflectionRayCount.
		m_iMaxReflectionRayCount++;

		// Check if a material has been assigned.
		if (pClosestObject->m_bHasMaterial)
		{
			// Use the material to compute the color.
			vMaterialColour = pClosestObject->m_pMaterial->ComputeColour(	vObjectList, 
																			vLightList, 
																			pClosestObject, 
																			vClosestIntersectionPoint, 
																			vClosestLocalNormal, 
																			reflectionRay);
		}
		else
		{
			vMaterialColour = QBRT::QBMaterialBase::ComputeDiffuseColour(	vObjectList, 
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

	vReflectionColour = vMaterialColour;
	return vReflectionColour;
}

// Function to assign a texture.
void QBRT::QBMaterialBase::AssignTexture(const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& vInputTexture)
{
	m_vTextureList.push_back(vInputTexture);
	m_bHasTexture = true;
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

// Function to blend colors.
void QBRT::QBMaterialBase::BlendColors(qbVector4<double>& vColor1, const qbVector4<double>& vColor2)
{
	vColor1 = (vColor2 * vColor2.a) + (vColor1 * (1.0 - vColor2.a));
}
