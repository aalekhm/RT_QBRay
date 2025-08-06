#pragma once

#include <vector>
#include "QBNoiseBase.hpp"

namespace QBRT
{
	namespace QBNoise
	{
		class QBGradientNoiseGenerator : public QBNoiseBase
		{
			public:
				// Constructor destructor.
				QBGradientNoiseGenerator();
				virtual ~QBGradientNoiseGenerator() override;

				// Function to get the value at a specific location.
				virtual double	GetValue(double fU, double fV);

				// Function to setup the grid.
				virtual void	SetupGrid(int iScale);

			private:
				// Normalize vector.
				std::vector<double>	ComputeNormalDisplacement(double fX1, double fY1, double fX2, double fY2);

			/* Note that these are declared public for debug purposes only. */
			public:
				// Store the grid of vectors.
				std::vector<std::vector<double>>	m_vValueGridX;
				std::vector<std::vector<double>>	m_vValueGridY;

				bool								m_bWrap = false;
		};
	}
}