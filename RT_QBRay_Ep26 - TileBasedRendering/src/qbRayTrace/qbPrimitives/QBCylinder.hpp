#pragma once
#include "qbRayTrace/qbPrimitives/QBObjectBase.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	class QBCylinder : public QBObjectBase, public std::enable_shared_from_this<QBRT::QBCylinder>
	{
		public:
			// Default constructor.
			QBCylinder();

			// Override the destructor.
			virtual ~QBCylinder();

			// Override the function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												QBRT::DATA::HitData& sHitData);
		public:
		protected:
		private:
	};
}