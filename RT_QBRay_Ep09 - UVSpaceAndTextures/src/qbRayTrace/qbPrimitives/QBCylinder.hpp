#pragma once
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	class QBCylinder : public QBObjectBase
	{
		public:
			// Default constructor.
			QBCylinder();

			// Override the destructor.
			virtual ~QBCylinder();

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector3<double>& vLocalColour);
		public:
		protected:
		private:
	};
}