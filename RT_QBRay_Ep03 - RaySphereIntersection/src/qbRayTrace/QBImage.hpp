#pragma once

#include <string>
#include <vector>
#include "qbLinAlg/qbVector3.hpp"
#include <SDL3/SDL.h>

class QBImage
{
	public:
		QBImage();
		~QBImage();

		// Function to initialize
		void	Initialize(const uint32_t iXSize, const uint32_t iYSize, SDL_Renderer* pRenderer);

		// Function to set pixels
		void	SetPixel(const uint32_t iX, const uint32_t iY, const double fRed, const double fGreen, const double fBlue);

		// Function to return the image for display.
		void	Display();

		// Functions to return the dimensions of the image.
		uint32_t GetXSize();
		uint32_t GetYSize();

		SDL_Renderer* GetRenderer() { return m_pRenderer; }
	protected:
	private:
		Uint32	ConvertColor(const double fRed, const double fGreen, const double fBlue);
		void	InitTexture();
	private:
		// Arrays to store image data.
		qbVector3<double>*	m_ColourChannel;

		uint32_t*			m_pPixelData;

		qbVector3<double>	m_rChannel;
		qbVector3<double>	m_gChannel;
		qbVector3<double>	m_bChannel;

		// And store the size of the image.
		uint32_t			m_iXSize, m_iYSize;

		// SDL2 stuff.
		SDL_Renderer*		m_pRenderer;
		SDL_Texture*		m_pTexture;
};