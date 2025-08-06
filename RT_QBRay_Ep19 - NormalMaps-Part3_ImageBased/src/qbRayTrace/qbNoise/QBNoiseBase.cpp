#include "QBNoiseBase.hpp"

#include "qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/qbLinAlg/qbVector4.hpp"

// Constructor / destructor.
QBRT::QBNoise::QBNoiseBase::QBNoiseBase()
{

}

QBRT::QBNoise::QBNoiseBase::~QBNoiseBase()
{

}

// Function to get the value at a specified location.
double QBRT::QBNoise::QBNoiseBase::GetValue(double fU, double fV)
{
	// Return a default value.
	return 0.0;
}

// Function for linear interpolation.
double QBRT::QBNoise::QBNoiseBase::Lerp(double fV1, double fV2, double iPos)
{
	// Note that here we are assuming the iPos will always be
	// between 0 and 1. If we can't make that assumption, then
	// we should ensure that it is between 0 and 1 before using
	// it to compute fade.
		
	// Smoothstep fade.
	double fFade = iPos * iPos * (3 - 2 * iPos);
	
	// Linear fade.
	//double fFade = iPos;
	
	// Implement the actual linear interpolation.
	return fV1 + fFade * (fV2 - fV1);	
}

// Function to setup the grid.
void QBRT::QBNoise::QBNoiseBase::SetupGrid(int iScale)
{
	m_iScale = iScale;
}
