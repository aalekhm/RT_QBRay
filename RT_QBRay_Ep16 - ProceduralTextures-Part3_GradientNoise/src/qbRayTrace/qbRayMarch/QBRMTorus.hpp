#pragma once

#include "QBRayMarchBase.hpp"

namespace QBRT
{
	namespace RM
	{
		class QBRMTorus : public QBRayMarchBase
		{
			public:
				// Constructor.
				QBRMTorus();

				// Destructor
				virtual ~QBRMTorus() override;

				// Function to set the radii.
				void	SetRadii(double fR1, double fR2);
			private:
				// Private object function.
				double	ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams);
			
				// Function to update the bounding box.
				void	UpdateBounds();
			private:
				// Radii.
				double	m_fRadii1 = 1.0;
				double	m_fRadii2 = 0.25;
		};
	}
}