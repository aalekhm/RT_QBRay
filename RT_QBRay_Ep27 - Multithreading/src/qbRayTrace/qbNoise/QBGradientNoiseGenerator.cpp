
#include "QBGradientNoiseGenerator.hpp"
#include "qbRayTrace/QBUtils.hpp"
#include <cmath>
#include <iostream>

// Constructor.
QBRT::QBNoise::QBGradientNoiseGenerator::QBGradientNoiseGenerator()
{
	// Configure the default grid.
	SetupGrid(2);
}

// Destructor.
QBRT::QBNoise::QBGradientNoiseGenerator::~QBGradientNoiseGenerator()
{
	
}

// Function to get the value at a specific location.
double QBRT::QBNoise::QBGradientNoiseGenerator::GetValue(double fU, double fV)
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

	// Compute corner indices
	int c1Xi = std::max(minX, 0);
	int c1Yi = std::max(minY, 0);
	int c2Xi = std::min(minX + 1, m_iScale);
	int c2Yi = std::max(minY, 0);
	int c3Xi = std::max(minX, 0);
	int c3Yi = std::min(minY + 1, m_iScale);
	int c4Xi = std::min(minX + 1, m_iScale);
	int c4Yi = std::min(minY + 1, m_iScale);

	// Extract the four vectors.
	std::vector<double> v1{ m_vValueGridX.at(c1Xi).at(c1Yi), m_vValueGridY.at(c1Xi).at(c1Yi) };
	std::vector<double> v2{ m_vValueGridX.at(c2Xi).at(c2Yi), m_vValueGridY.at(c2Xi).at(c2Yi) };
	std::vector<double> v3{ m_vValueGridX.at(c3Xi).at(c3Yi), m_vValueGridY.at(c3Xi).at(c3Yi) };
	std::vector<double> v4{ m_vValueGridX.at(c4Xi).at(c4Yi), m_vValueGridY.at(c4Xi).at(c4Yi) };

	// Compute locations of the four corners.
	double c1X = static_cast<double>(c1Xi) * fGridSpacing;
	double c1Y = static_cast<double>(c1Yi) * fGridSpacing;
	double c2X = static_cast<double>(c2Xi) * fGridSpacing;
	double c2Y = static_cast<double>(c2Yi) * fGridSpacing;
	double c3X = static_cast<double>(c3Xi) * fGridSpacing;
	double c3Y = static_cast<double>(c3Yi) * fGridSpacing;
	double c4X = static_cast<double>(c4Xi) * fGridSpacing;
	double c4Y = static_cast<double>(c4Yi) * fGridSpacing;

	// Compute the displacement vectors from the 4 corners to the point of interest(u, v).
	std::vector<double> d1 = ComputeNormalDisplacement(fU, fV, c1X, c1Y);
	std::vector<double> d2 = ComputeNormalDisplacement(fU, fV, c2X, c2Y);
	std::vector<double> d3 = ComputeNormalDisplacement(fU, fV, c3X, c3Y);
	std::vector<double> d4 = ComputeNormalDisplacement(fU, fV, c4X, c4Y);

	// Compute the dot products.
	double dp1 = (v1.at(0) * d1.at(0)) + (v1.at(1) * d1.at(1));
	double dp2 = (v2.at(0) * d2.at(0)) + (v2.at(1) * d2.at(1));
	double dp3 = (v3.at(0) * d3.at(0)) + (v3.at(1) * d3.at(1));
	double dp4 = (v4.at(0) * d4.at(0)) + (v4.at(1) * d4.at(1));

	// And interpolate.
	double xWeight = localX * static_cast<double>(m_iScale);
	double yWeight = localY * static_cast<double>(m_iScale);
	double t1 = Lerp(dp1, dp3, yWeight);
	double t2 = Lerp(dp2, dp4, yWeight);

	return Lerp(t1, t2, xWeight);
}

// Function to setup the grid.
void QBRT::QBNoise::QBGradientNoiseGenerator::SetupGrid(int iScale)
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

	m_vValueGridX.clear();
	m_vValueGridY.clear();
	m_vValueGridX.resize(m_iScale + 1, std::vector<double>(m_iScale + 1, 0.0));
	m_vValueGridY.resize(m_iScale + 1, std::vector<double>(m_iScale + 1, 0.0));
	for (int32_t x = 0; x < m_iScale; x++)
	{
		for (int32_t y = 0; y < m_iScale; y++)
		{
			// Compute a random theta.
			double fTheta = randomDistribution(randGenerator) * 2 * M_PI;

			// Convert this to Cartessian coordinates (assuming r = 1.0).
			double fX = cos(fTheta);
			double fY = sin(fTheta);

			// And store at the appropriate grid location.
			m_vValueGridX.at(x).at(y) = fX;
			m_vValueGridY.at(x).at(y) = fY;
		}
	}

	if (m_bWrap)
	{
		for (int32_t x = 0; x < m_iScale; x++)
		{
			m_vValueGridX.at(x).at(m_iScale) = m_vValueGridX.at(x).at(0);
			m_vValueGridY.at(x).at(m_iScale) = m_vValueGridY.at(x).at(0);
		}

		for (int32_t y = 0; y < m_iScale; y++)
		{
			m_vValueGridX.at(m_iScale).at(y) = m_vValueGridX.at(0).at(y);
			m_vValueGridY.at(m_iScale).at(y) = m_vValueGridY.at(0).at(y);
		}
	}
}

// Function to compute the normalized displacement vector.
std::vector<double>	QBRT::QBNoise::QBGradientNoiseGenerator::ComputeNormalDisplacement(double fX1, double fY1, double fX2, double fY2)
{
	double fXComp = fX1 - fX2;
	double fYComp = fY1 - fY2;

	return std::vector<double>{fXComp, fYComp};
}
