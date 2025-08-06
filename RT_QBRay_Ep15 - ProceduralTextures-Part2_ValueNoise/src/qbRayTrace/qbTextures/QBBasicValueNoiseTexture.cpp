#include "QBBasicValueNoiseTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBBasicValueNoiseTexture::QBBasicValueNoiseTexture()
{
	// Configure the noise generator.
	m_NoiseGenerator.SetupGrid(m_iScale);
}

QBRT::QBTexture::QBBasicValueNoiseTexture::~QBBasicValueNoiseTexture()
{

}

// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBBasicValueNoiseTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector3<double>	vInputLocation(vUVCoords.x, vUVCoords.y, 1.0);
	qbVector3<double>	vNewLocation = ApplyTransform(vInputLocation);
	double fNewU = vNewLocation.x;
	double fNewV = vNewLocation.y;

	qbVector4<double> vLocalColour;
	// If no color map has been provided, then output purple. This should be
	// easily recognizable in the scene, indicating that something is wrong.
	if (!m_bHasColourMap)
	{
		vLocalColour = qbVector4<double>(1.0, 0.0, 1.0, 1.0);
	}
	else
	{
		// Generate the base function.
		double fMapPosition = std::clamp(m_NoiseGenerator.GetValue(fNewU, fNewV) * m_fAmplitude, 0.0, 1.0);
		vLocalColour = m_colorMap->GetColor(fMapPosition);
	}
	
	return vLocalColour;
}

// Function to set the color map.
void QBRT::QBTexture::QBBasicValueNoiseTexture::SetColorMap(const std::shared_ptr<QBRT::QBTexture::QBColourMap>& colorMap)
{
	m_colorMap = colorMap;
	m_bHasColourMap = true;
}

// Function to set the amplitude.
void QBRT::QBTexture::QBBasicValueNoiseTexture::SetAmplitude(double fAmplitude)
{
	m_fAmplitude = fAmplitude;
}

// Function to set the scale.
void QBRT::QBTexture::QBBasicValueNoiseTexture::SetScale(int iScale)
{
	m_iScale = iScale;
	m_NoiseGenerator.SetupGrid(iScale);
}
