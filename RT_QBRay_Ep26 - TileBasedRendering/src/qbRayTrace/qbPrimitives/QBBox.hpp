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
												QBRT::DATA::HitData& sHitData);

			// Overloaded version of TestIntersection for the specific bounding box case.
			bool			TestIntersectionFast(const QBRT::QBRay& castRay);
		private:
	};
}