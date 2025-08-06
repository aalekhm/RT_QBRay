#pragma once

#include <vector>
#include <random>

namespace QBRT
{
	namespace QBNoise
	{
		class QBNoiseBase
		{
			public:
				// Constructor / destructor.
				QBNoiseBase();
				virtual ~QBNoiseBase();

				// Function to get the value at a specified location.
				virtual double	GetValue(double fU, double fV);

				// Function for linear interpolation.
				double			Lerp(double fV1, double fV2, double iPos);

				// Function to setup the grid.
				virtual void	SetupGrid(int iScale);
			public:
				// Store the scale.
				int				m_iScale;
		};
	}
}