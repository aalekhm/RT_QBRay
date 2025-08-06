#include "QBGradientTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBGradientTexture::QBGradientTexture()
{

}

QBRT::QBTexture::QBGradientTexture::~QBGradientTexture()
{

}

// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBGradientTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	double fNewU = GetValue(vUVCoords);
	return m_ColorMap.GetColor(fNewU);
}

// *** Function to return the value.
double QBRT::QBTexture::QBGradientTexture::GetValue(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector3<double> vInputLoc(vUVCoords.x, vUVCoords.y, 1.0);
	qbVector3<double> vNewLoc = ApplyTransform(vNewLoc);

	return std::min((vNewLoc.x + 1.0) / 2.0, 1.0);
}

// Function to set stops for the color map.
void QBRT::QBTexture::QBGradientTexture::SetStop(double fPosition, const qbVector4<double>& vValue)
{
	m_ColorMap.SetStop(fPosition, vValue);
}
