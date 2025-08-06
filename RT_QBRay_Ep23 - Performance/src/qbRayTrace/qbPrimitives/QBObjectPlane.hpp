#pragma once

#include "QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	class QBObjectPlane : public QBObjectBase, public std::enable_shared_from_this<QBRT::QBObjectPlane>
	{
		public:
			// Default constructor.
			QBObjectPlane();

			// Override the destructor.
			virtual ~QBObjectPlane() override;

			// Override the function to test for intersections.
			virtual bool TestIntersection(	const QBRay& castRay,
											QBRT::DATA::HitData& sHitData) override;
		private:
	};
}