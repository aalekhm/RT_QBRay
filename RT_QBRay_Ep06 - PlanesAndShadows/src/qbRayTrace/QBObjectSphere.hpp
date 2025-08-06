#pragma once

#include "QBObjectBase.hpp"
#include "QBGeometricTransform.hpp"

namespace QBRT
{
	class QBObjectSphere : public QBObjectBase
	{
		public:
			/* The default constructor.	Note that this will define a unit sphere at the origin. */
			QBObjectSphere();

			// Override the destructor.
			~QBObjectSphere();

			// Override the function to test for intersections.
			virtual bool TestIntersection(	const QBRay& castRay, 
											qbVector3<double>& vIntersectionPoint, 
											qbVector3<double>& vLocalNormal, 
											qbVector3<double>& vLocalColour) override;
		private:
	};
}