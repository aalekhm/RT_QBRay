#pragma once

#include "QBTextureBase.hpp"
#include "QBColourMap.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBGradientTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBGradientTexture();
				virtual ~QBGradientTexture() override;

				// Function to return the color.
				virtual qbVector4<double>	GetColor(const qbVector2<double>& vUVCoords);

				// Function to set stops for the color map.
				void						SetStop(double fPosition, const qbVector4<double>& vValue);
			private:
				QBRT::QBTexture::QBColourMap	m_ColorMap;
		};
	}
}