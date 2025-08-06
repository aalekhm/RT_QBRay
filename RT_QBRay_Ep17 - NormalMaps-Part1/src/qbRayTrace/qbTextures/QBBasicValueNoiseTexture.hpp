#pragma once

#include "QBTextureBase.hpp"
#include "QBColourMap.hpp"
#include "qbRayTrace/qbNoise/QBValueNoiseGenerator.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBBasicValueNoiseTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBBasicValueNoiseTexture();
				virtual ~QBBasicValueNoiseTexture() override;
				
				// Function to return the color.
				virtual qbVector4<double>	GetColor(const qbVector2<double> &vUVCoords) override;
				
				// *** Function to return the actual texture value at a given point in the (u,v) coordinate system.
				virtual double				GetValue(const qbVector2<double>& vUVCoords);

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
				QBRT::QBNoise::QBValueNoiseGenerator			m_NoiseGenerator;
				// Store the amplitude.
				double											m_fAmplitude = 8.0;
				
				// Store the scale.
				int												m_iScale = 3;
		};
	}
}
