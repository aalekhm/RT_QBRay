#pragma once
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/QBRay.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	// Forward-declare the material base class. 
	// This will be overriden later.
	class QBMaterialBase;

	class QBObjectBase
	{
		public:
			// Constructor and destructor.
			QBObjectBase();
			virtual ~QBObjectBase();

			// Function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector3<double>& vLocalColour);
			
			// Function to set the transform matrix.
			void			SetTransform(const QBRT::QBGeometricTransform& geomTransform);

			// Function to test whether two floating-point numbers are close to being equal.
			bool			CloseEnough(const double f1, const double f2);

			// Function to assign a material.
			bool			AssignMaterial(const std::shared_ptr<QBRT::QBMaterialBase>& pMaterial);

		// Public member variables.
		public:
			// The geometric transform applied to the object.
			QBGeometricTransform				m_GeomTransform;
			 
			// The base colour of the object.
			qbVector3<double>					m_vBaseColour;

			// A reference to the material assigned to this object.
			std::shared_ptr<QBRT::QBMaterialBase>	m_pMaterial;

			// A flag to indicate whether this object has a material or not.
			bool								m_bHasMaterial = false;
		protected:
		private:
	};
}