#include "QBNormalSimpleRough.hpp"

// Constructor / Destructor.
QBRT::QBNormal::QBNormalSimpleRough::QBNormalSimpleRough()
{
	std::random_device	randDevice;
	std::seed_seq		seed{ randDevice(), randDevice(), randDevice() };
	m_pRandom = std::make_shared<std::mt19937>(seed);
}

QBRT::QBNormal::QBNormalSimpleRough::~QBNormalSimpleRough()
{

}

// Function to compute the perturbation.
qbVector3<double> QBRT::QBNormal::QBNormalSimpleRough::ComputePerturbation(	const qbVector3<double>& vNormal,
																			const qbVector2<double>& vUVCoords)
{
	// Generate a uniformly distributed real random numbers between -m_fAmplitudeScale & m_fAmplitudeScale.
	std::uniform_real_distribution<double>	randomDistribution(-m_fAmplitudeScale, m_fAmplitudeScale);
	qbVector3<double> vPerturbation;
	vPerturbation.x = randomDistribution(*m_pRandom);
	vPerturbation.y = randomDistribution(*m_pRandom);
	vPerturbation.z = randomDistribution(*m_pRandom);

	return PerturbNormal(vNormal, vPerturbation);
}
