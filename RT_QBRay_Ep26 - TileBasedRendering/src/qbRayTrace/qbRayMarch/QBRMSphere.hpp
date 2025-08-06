#pragma once

#include "QBRayMarchBase.hpp"

namespace QBRT
{
	namespace RM
	{
		class QBRMSphere : public QBRayMarchBase
		{
			public:
				// Constructor.
				QBRMSphere();

				// Destructor
				virtual ~QBRMSphere() override;
			private:
				// Private object function.
				double	ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams);
		};
	}
}