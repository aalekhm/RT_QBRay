#pragma once
#include "QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	class QBBox : public QBObjectBase, public std::enable_shared_from_this<QBRT::QBBox>
	{
		public:
			// The default constructor.
			// Note that this will define a unit sphere at the origin.
			QBBox();

			// Override the destructor.
			virtual ~QBBox() override;

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector4<double>& vLocalColour);
		private:
			// For 6 faces. t @ PointOfIntersection & UnitVetors
			//std::array<double, 6> t;
			//std::array<double, 6> u;
			//std::array<double, 6> v;
	};
}