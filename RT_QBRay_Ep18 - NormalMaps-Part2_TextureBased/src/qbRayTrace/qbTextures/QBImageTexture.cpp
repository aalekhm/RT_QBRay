#include "QBImageTexture.hpp"

QBRT::QBTexture::QBImageTexture::QBImageTexture()
: m_pImageSurface(nullptr)
, m_pPixels(nullptr)
, m_iWidth(0)
, m_iHeight(0)
, m_iPitch(0)
, m_bImageLoaded(false)
{

}

QBRT::QBTexture::QBImageTexture::~QBImageTexture()
{
	if (m_bImageLoaded)
	{
		SDL_DestroySurface(m_pImageSurface);
		m_pImageSurface = nullptr;
		m_pPixels = nullptr;
		m_bImageLoaded = false;
	}
}

qbVector4<double> QBRT::QBTexture::QBImageTexture::GetColourAtPosition(uint32_t x, uint32_t y)
{
	qbVector4<double> vOutPixelColour(1.0, 0.0, 1.0, 1.0);

	if (((x >= 0) && (x < m_iWidth) && (y >= 0) && (y < m_iHeight)))
	{
		uint32_t iPos = (x * m_iBpp) + (y * m_iPitch);

		// Calculate the address of the pixel
		uint32_t iPixel = *(uint32_t*)(m_pPixels + iPos);

		uint8_t iRed, iGreen, iBlue, iAlpha;
		SDL_GetRGBA(iPixel, m_pPixelFormatDetails, nullptr, &iRed, &iGreen, &iBlue, &iAlpha);

		vOutPixelColour.r = iRed * ONE_OVER_255;
		vOutPixelColour.g = iGreen * ONE_OVER_255;
		vOutPixelColour.b = iBlue * ONE_OVER_255;
		vOutPixelColour.a = iAlpha * ONE_OVER_255;
	}

	return vOutPixelColour;
}

// Function to retrun the color at a given point in the (u,v) coordinate system.
// Note that the color is returned as a 4-dimensional vector (RGBA).
qbVector4<double> QBRT::QBTexture::QBImageTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	qbVector4<double> vOutPixelColour(1.0, 0.0, 1.0, 1.0);

	if(m_bImageLoaded)
	{
		// Apply the local transform to the (u,v) coordinates.
		qbVector3<double> vInputCoords(vUVCoords.x, vUVCoords.y, 1.0);
		qbVector3<double> vNewLocalCoords = ApplyTransform(vInputCoords);

		double fNewU = vNewLocalCoords.x;
		double fNewV = vNewLocalCoords.y;

		// Convert (u,v) to image dimensions (x,y).
		//uint32_t iX = fNewU * m_iWidth;
		//uint32_t iY = m_iHeight - (fNewV * m_iHeight);
		// Stretch it over the entire width & height
		uint32_t iX = static_cast<int>(round(((fNewU + 1.0) / 2.0) * static_cast<double>(m_iWidth)));
		uint32_t iY = m_iHeight - (static_cast<int>(round(((fNewV + 1.0) / 2.0) * static_cast<double>(m_iHeight))));

		// Modulo arithmetic to account for possible tiling.
		iX = ((iX % m_iWidth) + m_iWidth) % m_iWidth;
		iY = ((iY % m_iHeight) + m_iHeight) % m_iHeight;

		vOutPixelColour = GetColourAtPosition(iX, iY);
	}

	return vOutPixelColour;
}

// Function to load the image to be used.
bool QBRT::QBTexture::QBImageTexture::LoadImage(std::string sFilename)
{
	if (m_bImageLoaded)
	{
		SDL_DestroySurface(m_pImageSurface);
	}

	m_sFilename = sFilename;
	m_pImageSurface = SDL_LoadBMP(sFilename.c_str());

	if (m_pImageSurface == nullptr)
	{
		SDL_Log("SDL_LoadBMP failed: %s", SDL_GetError());

		return false;
	}

	// Extract useful information.
	m_pPixelFormatDetails = (SDL_PixelFormatDetails*)SDL_GetPixelFormatDetails(m_pImageSurface->format);

	m_iWidth = m_pImageSurface->w;
	m_iHeight = m_pImageSurface->h;
	m_iPitch = m_pImageSurface->pitch;
	m_iBpp = m_pPixelFormatDetails->bytes_per_pixel;
	m_pPixels = (Uint8*)m_pImageSurface->pixels;
	m_bImageLoaded = true;

	return true;
}

uint32_t QBRT::QBTexture::QBImageTexture::GetWidth()
{
	return m_iWidth;
}

uint32_t QBRT::QBTexture::QBImageTexture::GetHeight()
{
	return m_iHeight;
}

bool QBRT::QBTexture::QBImageTexture::IsImageLoaded()
{
	return m_bImageLoaded;
}