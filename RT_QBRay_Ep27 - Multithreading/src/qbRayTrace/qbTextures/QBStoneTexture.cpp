#include "QBStoneTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBStoneTexture::QBStoneTexture()
{
	// Initial configuration.
	m_fAmplitude1 = 1.0;
	m_fAmplitude2 = 1.0;
	m_iScale1 = 32;
	m_iScale2 = 64;
	m_fMinValue = -2.0;
	m_fMaxValue = 2.0;

	// Configure the noise generators.
	m_NoiseGenerator1.SetupGrid(m_iScale1);
	m_NoiseGenerator2.SetupGrid(m_iScale2);

	// Configure the color map.
	auto stoneColourMap = std::make_shared<QBRT::QBTexture::QBColourMap>();
	{
		stoneColourMap->SetStop(0.0,	qbVector4<double>(0.2, 0.2, 0.2, 1.0));
		stoneColourMap->SetStop(0.25,	qbVector4<double>(0.8, 0.8, 0.8, 1.0));
		stoneColourMap->SetStop(0.5,	qbVector4<double>(0.5, 0.5, 0.5, 1.0));
		stoneColourMap->SetStop(0.75,	qbVector4<double>(0.1, 0.1, 0.1, 1.0));
		stoneColourMap->SetStop(1.0,	qbVector4<double>(0.2, 0.2, 0.2, 1.0));
	}
	SetColorMap(stoneColourMap);
}

QBRT::QBTexture::QBStoneTexture::~QBStoneTexture()
{

}
				
// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBStoneTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	qbVector4<double> vLocalColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!m_bHasColourMap)
	{
		vLocalColor = qbVector4<double>(1.0, 0.0, 1.0, 1.0);
	}
	else
	{
		// Generate the base function.
		double fMapPosition = GetValue(vUVCoords);
		vLocalColor = m_colorMap->GetColor(fMapPosition);
	}

	return vLocalColor;
}
				
// Function to return the value.
double QBRT::QBTexture::QBStoneTexture::GetValue(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector3<double> vInputLoc(vUVCoords.x, vUVCoords.y, 1.0);
	qbVector3<double> vNewLoc = ApplyTransform(vInputLoc);
	double fNewV = vNewLoc.y;
	double fNewU = vNewLoc.x;
	
	// Generate the base function.
	double fMapPosition =	m_NoiseGenerator1.GetValue(fNewU, fNewV) * m_fAmplitude1 
							+ 
							m_NoiseGenerator2.GetValue(fNewU, fNewV) * m_fAmplitude2;
	
	fMapPosition = std::clamp((fMapPosition - m_fMinValue) / (m_fMaxValue - m_fMinValue), 0.0, 1.0);
	return fMapPosition;
}
				
// Function to set the color map.
void QBRT::QBTexture::QBStoneTexture::SetColorMap(const std::shared_ptr<QBRT::QBTexture::QBColourMap>& colorMap)
{
	m_colorMap = colorMap;
	m_bHasColourMap = true;
}
				
// Function to set the amplitude.
void QBRT::QBTexture::QBStoneTexture::SetAmplitude(double fAmplitude)
{
	m_fAmplitude1 = fAmplitude;
}
				
// Function to set the scale.
void QBRT::QBTexture::QBStoneTexture::SetScale(int iScale)
{
	m_iScale1 = iScale;
	m_NoiseGenerator1.SetupGrid(m_iScale1);
}
