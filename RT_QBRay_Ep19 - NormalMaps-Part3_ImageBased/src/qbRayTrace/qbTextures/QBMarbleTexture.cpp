#include "QBMarbleTexture.hpp"
#include <algorithm>

// Constructor / destructor.
QBRT::QBTexture::QBMarbleTexture::QBMarbleTexture()
{
	// Configure the noise generators.
	m_NoiseGeneratorList.push_back(QBRT::QBNoise::QBGradientNoiseGenerator());
	m_NoiseGeneratorList.push_back(QBRT::QBNoise::QBGradientNoiseGenerator());
	
	m_NoiseGeneratorList.at(0).SetupGrid(4);
	m_NoiseGeneratorList.at(1).SetupGrid(40);
	
	m_fMinValue = -3.0;
	m_fMaxValue = 3.0;
}

QBRT::QBTexture::QBMarbleTexture::~QBMarbleTexture()
{

}

// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBMarbleTexture::GetColor(const qbVector2<double>& vUVCoords)

{
	// Apply the local transform to the (u,v) coordinates.
	qbVector3<double> vInputLoc(vUVCoords.x, vUVCoords.y, 1.0);
	qbVector3<double> vNewLoc = ApplyTransform(vInputLoc);
	double newU = vNewLoc.x;
	double newV = vNewLoc.y;
	
	qbVector4<double> vLocalColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!m_bHasColourMap)
	{
		vLocalColor = qbVector4<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}};
	}
	else
	{
		// Generate the base function.
		double fAngleTheta = m_fSineFrequency * M_PI;
		double fPerturbTheta1 = (m_NoiseGeneratorList.at(0).GetValue(newU, newV) * m_fAmplitude1);
		double fPerturbTheta2 = (m_NoiseGeneratorList.at(1).GetValue(newU, newV) * m_fAmplitude2);

		double fMapPosition = 	m_fSineAmplitude 
								* 
								sin(fAngleTheta * (((newU + newV) / 2.0) + fPerturbTheta1 + fPerturbTheta2));
													
		// Normalize to min and max values.
		fMapPosition = std::clamp((fMapPosition - m_fMinValue) / (m_fMaxValue - m_fMinValue), 0.0, 1.0);
		
		vLocalColor = m_colorMap->GetColor(fMapPosition);
	}
	
	return vLocalColor;
}

// Function to set the color map.
void QBRT::QBTexture::QBMarbleTexture::SetColorMap(const std::shared_ptr<QBRT::QBTexture::QBColourMap>& colourMap)
{
	m_colorMap = colourMap;
	m_bHasColourMap = true;
}

// Function to set the ammplitude.
void QBRT::QBTexture::QBMarbleTexture::SetAmplitude(double fAmplitude1, double fAmplitude2)
{
	m_fAmplitude1 = fAmplitude1;
	m_fAmplitude2 = fAmplitude2;
}

// Function to set the scale.
void QBRT::QBTexture::QBMarbleTexture::SetScale(int iScale1, int iScale2)
{
	m_iScale1 = iScale1;
	m_iScale2 = iScale2;
	m_NoiseGeneratorList.at(0).SetupGrid(m_iScale1);
	m_NoiseGeneratorList.at(1).SetupGrid(m_iScale2);
}

// Function to set the min and max values.
void QBRT::QBTexture::QBMarbleTexture::SetMinMax(double fMinValue, double fMaxValue)
{
	m_fMinValue = fMinValue;
	m_fMaxValue = fMaxValue;
}

// Function to set the sine wave parameters.
void QBRT::QBTexture::QBMarbleTexture::SetSine(double fAmplitude, double fFrequency)
{
	m_fSineAmplitude = fAmplitude;
	m_fSineFrequency = fFrequency;
}
