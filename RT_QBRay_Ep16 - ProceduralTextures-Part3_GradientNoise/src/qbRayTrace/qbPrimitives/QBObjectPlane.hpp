#pragma once

#include "QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	class QBObjectPlane : public QBObjectBase
	{
		public:
			// Default constructor.
			QBObjectPlane();

			// Override the destructor.
			virtual ~QBObjectPlane() override;

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector4<double>& vLocalColour);
		private:
	};
}