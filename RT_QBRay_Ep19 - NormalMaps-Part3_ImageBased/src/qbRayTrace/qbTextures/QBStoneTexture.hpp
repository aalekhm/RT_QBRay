#pragma once

#include "qbRayTrace/qbNoise/QBValueNoiseGenerator.hpp"
#include "qbRayTrace/qbNormals/QBTextureNormal.hpp"
#include "QBColourMap.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBStoneTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBStoneTexture();
				virtual ~QBStoneTexture() override;
				
				// Function to return the color.
				virtual qbVector4<double>	GetColor(const qbVector2<double>& vUVCoords) override;
				
				// Function to return the value.
				virtual double				GetValue(const qbVector2<double>& vUVCoords) override;
				
				// Function to set the color map.
				void						SetColorMap(const std::shared_ptr<QBRT::QBTexture::QBColourMap>& colorMap);
				
				// Function to set the amplitude.
				void						SetAmplitude(double fAmplitude);
				
				// Function to set the scale.
				void						SetScale(int iScale);
				
			public:
				// Store the color map.
				std::shared_ptr<QBRT::QBTexture::QBColourMap>	m_colorMap;
				bool											m_bHasColourMap = false;
				
				// We need a NoiseGenerator instance.
				QBRT::QBNoise::QBValueNoiseGenerator			m_NoiseGenerator1;
				QBRT::QBNoise::QBValueNoiseGenerator			m_NoiseGenerator2;
				
				// Store the amplitude.
				double											m_fAmplitude2 = 4.0;
				double											m_fAmplitude1 = 8.0;
				
				// Store the scale.
				int												m_iScale1 = 6;
				int												m_iScale2 = 30;
				
				// Store the min and max values.
				double											m_fMinValue, m_fMaxValue;
				
		};
	}
}