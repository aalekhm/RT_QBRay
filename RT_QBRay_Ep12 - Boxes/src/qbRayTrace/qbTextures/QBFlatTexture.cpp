#include "QBFlatTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBFlatTexture::QBFlatTexture()
{
	m_vColour.r = 1.0;
	m_vColour.g = 0.0;
	m_vColour.b = 0.0;
}

QBRT::QBTexture::QBFlatTexture::~QBFlatTexture()
{

}

// Function to return the color.
qbVector3<double> QBRT::QBTexture::QBFlatTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	return m_vColour;
}

// Function to set the color.
void QBRT::QBTexture::QBFlatTexture::SetColour(const qbVector3<double>& vInputColour)
{
	m_vColour = vInputColour;
}
