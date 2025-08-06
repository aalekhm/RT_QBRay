#pragma once
#include "qbLinAlg/qbVector3.hpp"
#include "QBRay.hpp"
#include "QBGeometricTransform.hpp"

namespace QBRT
{
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

		// Public member variables.
		public:
			// The geometric transform applied to the object.
			QBGeometricTransform	m_GeomTransform;
			 
			// The base colour of the object.
			qbVector3<double>		m_vBaseColour;
		protected:
		private:
	};
}