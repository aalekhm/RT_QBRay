#pragma once

#include "QBRayMarchBase.hpp"

namespace QBRT
{
	namespace RM
	{
		class QBRMCube : public QBRayMarchBase
		{
		public:
			// Constructor.
			QBRMCube();

			// Destructor
			virtual ~QBRMCube() override;
		private:
			// Private object function.
			double	ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams);
		};
	}
}