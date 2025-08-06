#include "QBValueNoiseGenerator.hpp"
#include <vector>
#include <random>

#define USE_RANDOM_EVERYTIME 0

// Constructor destructor.
QBRT::QBNoise::QBValueNoiseGenerator::QBValueNoiseGenerator()
{
	// Configure the default grid.
	SetupGrid(2);
}

QBRT::QBNoise::QBValueNoiseGenerator::~QBValueNoiseGenerator()
{

}

// Function to get the value at a specific location.
double QBRT::QBNoise::QBValueNoiseGenerator::GetValue(double fU, double fV)
{
	// Ensure that x and y are cyclic.
	fU = fmod(fU, 1.0);
	fV = fmod(fV, 1.0);

	// Convert x and y to a range of 0 to 1.
	fU = (fU + 1.0) / 2.0;
	fV = (fV + 1.0) / 2.0;

	// Determine the spacing of the grid boundaries.
	double fGridSpacing = 1.0 / static_cast<double>(m_iScale);
	
	// Compute local x and y.
	double localX = fmod(fU, fGridSpacing);
	double localY = fmod(fV, fGridSpacing);
	
	// Compute the grid corner indices.
	int minX = static_cast<int>((fU - localX) * m_iScale);
	int minY = static_cast<int>((fV - localY) * m_iScale);
	
	int c1Xi = std::max(minX, 0);
	int c1Yi = std::max(minY, 0);
	int c2Xi = std::min(minX + 1, m_iScale);
	int c2Yi = std::max(minY, 0);
	
	int c3Xi = std::max(minX, 0);
	int c3Yi = std::min(minY + 1, m_iScale);
	int c4Xi = std::min(minX + 1, m_iScale);
	int c4Yi = std::min(minY + 1, m_iScale);
	
	// Extract the four values.
	double v1 = m_vValueGrid.at(c1Xi).at(c1Yi);
	double v2 = m_vValueGrid.at(c2Xi).at(c2Yi);
	double v3 = m_vValueGrid.at(c3Xi).at(c3Yi);
	double v4 = m_vValueGrid.at(c4Xi).at(c4Yi);		

	// And interpolate.
	double xWeight = localX * static_cast<double>(m_iScale);
	double yWeight = localY * static_cast<double>(m_iScale);
	double t1 = Lerp(v1, v3, yWeight);
	double t2 = Lerp(v2, v4, yWeight);

	return Lerp(t1, t2, xWeight);
}

// Function to setup the grid.
void QBRT::QBNoise::QBValueNoiseGenerator::SetupGrid(int iScale)
{
	m_iScale = iScale;

	// The random number generator

	/* Use the seed version if you want a different pattern everytime,
	or use without seed, or with a fixed seed, if you want the
	pattern to remain the same every time. */
	
	// Generate a seed for the random number generation.
#if (USE_RANDOM_EVERYTIME == 1)
	std::random_device randDevice;
	std::seed_seq seedSequence{ randDevice(), randDevice(), randDevice(), randDevice() };
	std::mt19937 randGenerator(seedSequence);
#else
	std::mt19937 randGenerator;
#endif
	// Setup the random number distribution.
	// (uniform real numbers betweeon 0 and 1).
	std::uniform_real_distribution<double> randomDistribution(0.0, 1.0);

	// Generate the grid of random vectors.
	/*
	'iScale' defines how many grid squares we want, so a scale of
	1 means a single grid square, 2 means a 2x2 grid, 3 a 3x3 grid
	and so on.
	*/

	m_vValueGrid.clear();
	m_vValueGrid.resize(m_iScale + 1, std::vector<double>(m_iScale + 1, 0.0));
	for (int32_t x = 0; x < m_iScale; x++)
	{
		for (int32_t y = 0; y < m_iScale; y++)
		{
			// Store a random value.
			m_vValueGrid.at(x).at(y) = randomDistribution(randGenerator);
		}
	}

	if (m_bWrap)
	{
		for (int32_t x = 0; x < m_iScale; x++)
		{
			m_vValueGrid.at(x).at(m_iScale) = m_vValueGrid.at(x).at(0);
		}

		for (int32_t y = 0; y < m_iScale; y++)
		{
			m_vValueGrid.at(m_iScale).at(y) = m_vValueGrid.at(0).at(y);
		}
	}
}
