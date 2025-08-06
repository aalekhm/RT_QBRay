#pragma once

#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"
#include "qbRayTrace/QBUtils.hpp"

namespace QBRT
{
	class QBCone : public QBObjectBase, public std::enable_shared_from_this<QBRT::QBCone>
	{
		public:
			// Default constructor.
			QBCone();

			// Override the destructor.
			virtual ~QBCone() override;

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												QBRT::DATA::HitData& sHitData);
		public:
		protected:
		private:
	};
}