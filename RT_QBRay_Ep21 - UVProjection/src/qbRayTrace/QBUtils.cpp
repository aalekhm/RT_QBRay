#include "QBUtils.hpp"
#include "qbPrimitives/QBObjectPlane.hpp"
#include "qbPrimitives/QBObjectSphere.hpp"
#include "qbPrimitives/QBCylinder.hpp"
#include "qbPrimitives/QBCone.hpp"
#include "qbPrimitives/QBBox.hpp"
#include "qbRayMarch/QBRMSphere.hpp"
#include "qbRayMarch/QBRMTorus.hpp"
#include "qbRayMarch/QBRMCube.hpp"
#include "qbLights/QBPointLight.hpp"
#include "qbMaterials/QBSimpleMaterial.hpp"

uint32_t QBRT::QBUtils::m_iCurrentPixelX = 0;
uint32_t QBRT::QBUtils::m_iCurrentPixelY = 0;

std::string QBRT::QBUtils::GetProjectName()
{
	return std::string(__PROJECT_NAME__);
}

void QBRT::QBUtils::AddRMCube(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material,
								const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::RM::QBRMCube> objRMCube = std::make_shared<QBRT::RM::QBRMCube>();
	vObjectList.push_back(objRMCube);
	{
		QBRT::RM::QBRMCube* pObj = objRMCube.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

void QBRT::QBUtils::AddRMTorus(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material,
								double fRadii1, double fRadii2,
								const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::RM::QBRMTorus> objRMTorus = std::make_shared<QBRT::RM::QBRMTorus>();
	vObjectList.push_back(objRMTorus);
	{
		QBRT::RM::QBRMTorus* pObj = objRMTorus.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->SetRadii(fRadii1, fRadii2);
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

void QBRT::QBUtils::AddRMSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material,
									const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::RM::QBRMSphere> objRMSphere = std::make_shared<QBRT::RM::QBRMSphere>();
	vObjectList.push_back(objRMSphere);
	{
		QBRT::RM::QBRMSphere* pObj = objRMSphere.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

QBRT::QBObjectSphere* QBRT::QBUtils::AddSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												const qbVector3<double>& vTranslation,
												const qbVector3<double>& vRotation,
												const qbVector3<double>& vScaling,
												const std::shared_ptr<QBRT::QBMaterialBase>& material,
												const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::QBObjectSphere> objSphere = std::make_shared<QBRT::QBObjectSphere>();
	vObjectList.push_back(objSphere);
	{
		QBRT::QBObjectSphere* pObj = objSphere.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_iUVMapType = QBRT::uvSPHERE;
		pObj->m_sFriendlyName = sFriendlyName;

		return pObj;
	}
}

QBRT::QBObjectPlane* QBRT::QBUtils::AddPlane(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
												const qbVector3<double>& vTranslation,
												const qbVector3<double>& vRotation,
												const qbVector3<double>& vScaling,
												const std::shared_ptr<QBRT::QBMaterialBase>& material,
												const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::QBObjectPlane> objPlane = std::make_shared<QBRT::QBObjectPlane>();
	vObjectList.push_back(objPlane);
	{
		QBRT::QBObjectPlane* pObj = objPlane.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_iUVMapType = QBRT::uvPLANE;
		pObj->m_sFriendlyName = sFriendlyName;

		return pObj;
	}
}

void QBRT::QBUtils::AddCylinder(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material,
									const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::QBCylinder> objCylinder = std::make_shared<QBRT::QBCylinder>();
	vObjectList.push_back(objCylinder);
	{
		QBRT::QBCylinder* pObj = objCylinder.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_iUVMapType = QBRT::uvCYLINDER;
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

void QBRT::QBUtils::AddCone(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material,
								const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::QBCone> objCone = std::make_shared<QBRT::QBCone>();
	vObjectList.push_back(objCone);
	{
		QBRT::QBCone* pObj = objCone.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_iUVMapType = QBRT::uvCONE;
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

void QBRT::QBUtils::AddBox(		std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material,
								const std::string& sFriendlyName)
{
	std::shared_ptr<QBRT::QBBox> objBox = std::make_shared<QBRT::QBBox>();
	vObjectList.push_back(objBox);
	{
		QBRT::QBBox* pObj = objBox.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
		pObj->m_iUVMapType = QBRT::uvBOX;
		pObj->m_sFriendlyName = sFriendlyName;
	}
}

QBRT::QBPointLight* QBRT::QBUtils::AddLight(	std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
												const qbVector3<double>& vPosition,
												const qbVector4<double>& vColour)
{
	std::shared_ptr<QBRT::QBPointLight> objLight = std::make_shared<QBRT::QBPointLight>();
	vLightList.push_back(objLight);
	QBRT::QBPointLight* pObjLight = objLight.get();
	{	
		pObjLight->m_vLightPosition = vPosition;
		pObjLight->m_vLightColour = vColour;
	}

	return pObjLight;
}

void QBRT::QBUtils::PrintVector(const char* sString, const qbVector3<double>& inputVector)
{
	int nRows = inputVector.GetNumDims();
	std::cout << sString << " ";
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << " ";
	}
	std::cout << std::endl;
}

void QBRT::QBUtils::PrintVector(const uint32_t iX, const uint32_t iY, const char* sString, const qbVector3<double>& vInputVector)
{
	if (m_iCurrentPixelX == iX && m_iCurrentPixelY == iY)
	{
		PrintVector(sString, vInputVector);
	}
}

// Functions to handle interpolation.
double QBRT::QBUtils::LinearInterp(	const double& x0,
									const double& y0,
									const double& x1,
									const double& y1,
									const double& x)
{
	double fOutput;
	
	if ((x1-x0) == 0.0)
		fOutput = y0;
	else
		fOutput = y0 + ((x - x0)*((y1 - y0)/(x1 - x0)));
		
	return fOutput;
}

double QBRT::QBUtils::BilinearInterp(	const double &x0, const double &y0, const double &v0,
										const double &x1, const double &y1, const double &v1,
										const double &x2, const double &y2, const double &v2,
										const double &x3, const double &y3, const double &v3,
										const double &x, const double &y)
{
	double fP1 = LinearInterp(x0, v0, x1, v1, x);
	double fP2 = LinearInterp(x2, v2, x3, v3, x);
	double fP3 = LinearInterp(y0, fP1, y2, fP2, y);

	return fP3;
}