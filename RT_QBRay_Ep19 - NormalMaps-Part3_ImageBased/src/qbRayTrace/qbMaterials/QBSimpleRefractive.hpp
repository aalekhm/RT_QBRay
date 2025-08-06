#pragma once

#include "QBMaterialBase.hpp"

namespace QBRT
{
	class QBSimpleRefractive : public QBMaterialBase
	{
		public:
			// Constructor / destructor.
			QBSimpleRefractive();
			QBSimpleRefractive(	const qbVector4<double>& vColour, 
								double fReflectivity, 
								double fShininess,
								double fTranslucency,
								double fIOR);
			virtual ~QBSimpleRefractive();

			// Function to return the color of the material.
			virtual	qbVector4<double>	ComputeColour(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
														const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
														const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
														const qbVector3<double>& vIntersectionPoint,
														const qbVector3<double>& vLocalNormal,
														const QBRT::QBRay& vCameraRay);

			// Function to compute specular highlights.
			qbVector4<double>			ComputeSpecular(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
															const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
															const qbVector3<double>& vIntersectionPoint,
															const qbVector3<double>& vLocalNormal,
															const QBRT::QBRay& cameraRay);

			// Function to compute translucency.
			qbVector4<double>			ComputeTranslucency(	const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
																const std::vector<std::shared_ptr<QBRT::QBLightBase>>& vLightList,
																const std::shared_ptr<QBRT::QBObjectBase>& pCurrentObject,
																const qbVector3<double>& vIntersectionPoint,
																const qbVector3<double>& vLocalNormal,
																const QBRT::QBRay& incidentRay);
		private:
			qbVector4<double>			m_vBaseColour{ 1.0, 1.0, 1.0, 1.0 };
			double						m_fReflectivity = 0.0;
			double						m_fShininess = 0.0;
			double						m_fTranslucency = 0.0;
			double						m_fIOR = 0.0;
	};
}