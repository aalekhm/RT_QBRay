#include "QBGradient.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBGradient::QBGradient()
{

}

QBRT::QBTexture::QBGradient::~QBGradient()
{

}

// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBGradient::GetColor(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector3<double> vInputLoc(vUVCoords.x, vUVCoords.y, 1.0);
	qbVector3<double> vNewLoc = ApplyTransform(vInputLoc);
	double fNewU = std::min((vNewLoc.y + 1.0) / 2.0, 1.0);
	return m_ColorMap.GetColor(fNewU);
}

// Function to set stops for the color map.
void QBRT::QBTexture::QBGradient::SetStop(double fPosition, const qbVector4<double>& vValue)
{
	m_ColorMap.SetStop(fPosition, vValue);
}
