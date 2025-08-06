#pragma once

#include "QBTextureBase.hpp"
#include <SDL3/SDL.h>

namespace QBRT
{
	namespace QBTexture
	{
		class QBImageTexture : public QBTextureBase
		{
			public:
				QBImageTexture();
				virtual ~QBImageTexture() override;

				// Function to retrun the color at a given point in the (u,v) coordinate system.
				// Note that the color is returned as a 4-dimensional vector (RGBA).
				virtual qbVector3<double>	GetColor(const qbVector2<double>& vUVCoords);
				
				// Function to load the image to be used.
				bool						LoadImage(std::string sFilename);

				qbVector3<double>			GetColourAtPosition(uint32_t x, uint32_t y);

				uint32_t					GetWidth();
				uint32_t					GetHeight();
			private:
				std::string					m_sFilename;
				SDL_Surface*				m_pImageSurface;
				SDL_PixelFormatDetails*		m_pPixelFormatDetails;
				Uint8*						m_pPixels;
				uint32_t					m_iPitch;
				uint32_t					m_iBpp;
				bool						m_bImageLoaded;
				uint32_t					m_iWidth, m_iHeight;
		};
	}
}