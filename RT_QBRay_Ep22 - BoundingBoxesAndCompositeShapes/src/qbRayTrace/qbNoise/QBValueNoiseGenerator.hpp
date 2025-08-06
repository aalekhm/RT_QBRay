#pragma once

#include "QBNoiseBase.hpp"

namespace QBRT
{
	namespace QBNoise
	{
		class QBValueNoiseGenerator : public QBNoiseBase
		{
			public:
				// Constructor destructor.
				QBValueNoiseGenerator();
				virtual ~QBValueNoiseGenerator() override;
				
				// Function to get the value at a specific location.
				virtual double	GetValue(double fU, double fV) override;
				
				// Function to setup the grid.
				virtual void	SetupGrid(int iScale) override;				
			private:				
				
			/* Note that these are declared public for debug purposes only. */
			public:
				// Store the grid of vectors.
				std::vector<std::vector<double>>	m_vValueGrid;
				
				bool								m_bWrap = false;
		};
	}
}
