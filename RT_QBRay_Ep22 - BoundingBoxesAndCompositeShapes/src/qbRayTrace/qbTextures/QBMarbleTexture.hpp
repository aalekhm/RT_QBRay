#pragma once

#include "qbRayTrace/qbNoise/QBGradientNoiseGenerator.hpp"
#include "QBTextureBase.hpp"
#include "QBColourMap.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBMarbleTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBMarbleTexture();
				virtual ~QBMarbleTexture() override;

				// Function to return the color.
				virtual qbVector4<double>	GetColor(const qbVector2<double>& vUVCoords);

				// Function to set the color map.
				void						SetColorMap(const std::shared_ptr<QBRT::QBTexture::QBColourMap>& colourMap);

				// Function to set the amplitude.
				void						SetAmplitude(double fAmplitude1, double fAmplitude2);

				// Function to set the scale.
				void						SetScale(int iScale1, int iScale2);

				// Function to set the min and max values.
				void						SetMinMax(double fMinValue, double fMaxValue);

				// Function to set the sine wave parameters.
				void						SetSine(double fAmplitude, double fFrequency);

			public:
				// Store the color map.
				std::shared_ptr<QBRT::QBTexture::QBColourMap>		m_colorMap;
				bool												m_bHasColourMap = false;

				// Store a list of noise generator instances.
				// Layering of Noise Generators, if required. Currently 2 are used.
				std::vector<QBRT::QBNoise::QBGradientNoiseGenerator> m_NoiseGeneratorList;

				// Store the amplitude.
				double												m_fAmplitude1 = 8.0;
				double												m_fAmplitude2 = 8.0;

				// Store the scale.
				int													m_iScale1 = 4;
				int													m_iScale2 = 40;

				// Define min and max values.
				double												m_fMaxValue = 1.0;
				double												m_fMinValue = -1.0;

				// Define underlying sine wave parameters.
				double												m_fSineAmplitude = 0.25;
				double												m_fSineFrequency = 4.0;
		};
	}
}