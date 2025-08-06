#include "QBUtils.hpp"
#include "qbPrimitives/QBObjectPlane.hpp"
#include "qbPrimitives/QBObjectSphere.hpp"
#include "qbPrimitives/QBCylinder.hpp"
#include "qbPrimitives/QBCone.hpp"
#include "qbPrimitives/QBBox.hpp"
#include "qbLights/QBPointLight.hpp"
#include "qbMaterials/QBSimpleMaterial.hpp"

uint32_t QBRT::QBUtils::m_iCurrentPixelX = 0;
uint32_t QBRT::QBUtils::m_iCurrentPixelY = 0;

std::string QBRT::QBUtils::GetProjectName()
{
	return std::string(__PROJECT_NAME__);
}


void QBRT::QBUtils::AddSphere(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material)
{
	std::shared_ptr<QBRT::QBObjectSphere> objSphere = std::make_shared<QBRT::QBObjectSphere>();
	vObjectList.push_back(objSphere);
	{
		QBRT::QBObjectSphere* pObj = objSphere.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
	}
}

void QBRT::QBUtils::AddPlane(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material)
{
	std::shared_ptr<QBRT::QBObjectPlane> objPlane = std::make_shared<QBRT::QBObjectPlane>();
	vObjectList.push_back(objPlane);
	{
		QBRT::QBObjectPlane* pObj = objPlane.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
	}
}

void QBRT::QBUtils::AddCylinder(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling,
									const std::shared_ptr<QBRT::QBMaterialBase>& material)
{
	std::shared_ptr<QBRT::QBCylinder> objCylinder = std::make_shared<QBRT::QBCylinder>();
	vObjectList.push_back(objCylinder);
	{
		QBRT::QBCylinder* pObj = objCylinder.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
	}
}

void QBRT::QBUtils::AddCone(	std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material)
{
	std::shared_ptr<QBRT::QBCone> objCone = std::make_shared<QBRT::QBCone>();
	vObjectList.push_back(objCone);
	{
		QBRT::QBCone* pObj = objCone.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
	}
}

void QBRT::QBUtils::AddBox(		std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
								const qbVector3<double>& vTranslation,
								const qbVector3<double>& vRotation,
								const qbVector3<double>& vScaling,
								const std::shared_ptr<QBRT::QBMaterialBase>& material)
{
	std::shared_ptr<QBRT::QBBox> objBox = std::make_shared<QBRT::QBBox>();
	vObjectList.push_back(objBox);
	{
		QBRT::QBBox* pObj = objBox.get();
		pObj->SetTransform(QBRT::QBGeometricTransform(vTranslation, vRotation, vScaling));
		pObj->AssignMaterial(material);
	}
}

QBRT::QBPointLight* QBRT::QBUtils::AddLight(	std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
												const qbVector3<double>& vPosition,
												const qbVector3<double>& vColour)
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

