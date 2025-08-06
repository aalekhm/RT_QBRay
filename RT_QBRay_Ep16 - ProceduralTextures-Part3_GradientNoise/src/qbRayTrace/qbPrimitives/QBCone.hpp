#pragma once

#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"
#include "qbRayTrace/QBUtils.hpp"

namespace QBRT
{
	class QBCone : public QBObjectBase
	{
		public:
			// Default constructor.
			QBCone();

			// Override the destructor.
			virtual ~QBCone() override;

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector4<double>& vLocalColour);
		public:
		protected:
		private:
	};
}