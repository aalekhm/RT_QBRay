#pragma once

#include <functional>
#include "QBSDFFunc.hpp"
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/qbPrimitives/QBBox.hpp"
#include "qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/qbLinAlg/qbVector4.hpp"

namespace QBRT
{
	namespace RM
	{
		class QBRayMarchBase : public QBObjectBase, public std::enable_shared_from_this<QBRT::RM::QBRayMarchBase>
		{
			public:
				// Default constructor.
				QBRayMarchBase();
				
				// Destructor.
				virtual ~QBRayMarchBase() override;
				
				// Override the function to test for intersections.
				virtual bool	TestIntersection(	const QBRay& castRay, 
													qbVector3<double>& vIntersectionPoint, 
													qbVector3<double>& vLocalNormal, 
													qbVector4<double>& vLocalColour);
				
				// Function to set the object function.
				void			SetObjectFunc(	std::function<double(qbVector3<double>*, qbVector3<double>*)> objectFunc);
				
				// Function to evaluate the Signed Distance Function (SDF) at the given coordinates.
				double			EvaluateSDF(	qbVector3<double>* vLocation, 
												qbVector3<double>* vParms);												
			public:
				// Bounding box.
				QBRT::QBBox			m_BoundingBox = QBRT::QBBox();
				
				// Parameters.
				qbVector3<double>	m_vParms;
				
			private:
				// Pointer to object function.
				std::function<double(qbVector3<double>*, qbVector3<double>*)> m_ObjectFunc;
			
				bool				m_bHaveObjectFunc = false;
				double				m_fEpsilon;
				int					m_iMaxSteps;
				
				const double		m_fH = 0.001;
				qbVector3<double>	m_vXDisp {m_fH, 0.0, 0.0};
				qbVector3<double>	m_vYDisp{0.0, m_fH, 0.0};
				qbVector3<double>	m_vZDisp{0.0, 0.0, m_fH};
		};
	}
}