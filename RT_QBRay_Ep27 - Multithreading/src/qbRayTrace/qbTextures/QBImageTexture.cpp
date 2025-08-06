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
		double iWidth = GetWidth();
		double iHeight = GetHeight();

		// Apply the local transform to the (u,v) coordinates.
		qbVector3<double> vInputLoc(vUVCoords.x, vUVCoords.y, 1.0);
		qbVector3<double> vNewLoc = ApplyTransform(vInputLoc);
		double u = vNewLoc.x;
		double v = vNewLoc.y;

		// Modulo arithmatic to account for possible tiling.
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);

		// Convert (u,v) to image dimensions (x,y).
		// Stretch it over the entire width & height
		double fWidth = static_cast<double>(iWidth);
		double fHeight = static_cast<double>(iHeight);
		double xF = ((u + 1.0) / 2.0) * fWidth;
		double yF = fHeight - (((v + 1.0) / 2.0) * fHeight);

		// x, y are the positions with the particular square
		int x = static_cast<int>(round(xF));
		int y = static_cast<int>(round(yF));

#if (USE_BILINEARINTERPOLATION == 1)
		// Positions of the 4 corners around the above point(x, y)
		int xMin = static_cast<int>(floor(xF));
		int yMin = static_cast<int>(floor(yF));
		int xMax = static_cast<int>(ceil(xF));
		int yMax = static_cast<int>(ceil(yF));

		// Perform bilinear interpolation.
		// Get Colour values of the 4 corners
		qbVector4<double> vColour0 = GetColourAtPosition(xMin, yMin);
		qbVector4<double> vColour1 = GetColourAtPosition(xMax, yMin);
		qbVector4<double> vColour2 = GetColourAtPosition(xMin, yMax);
		qbVector4<double> vColour3 = GetColourAtPosition(xMax, yMax);

		double interpR = QBRT::QBUtils::BilinearInterp(xMin, yMin, vColour0.r, xMax, yMin, vColour1.r, xMin, yMax, vColour2.r, xMax, yMax, vColour3.r, xF, yF);
		double interpG = QBRT::QBUtils::BilinearInterp(xMin, yMin, vColour0.g, xMax, yMin, vColour1.g, xMin, yMax, vColour2.g, xMax, yMax, vColour3.g, xF, yF);
		double interpB = QBRT::QBUtils::BilinearInterp(xMin, yMin, vColour0.b, xMax, yMin, vColour1.b, xMin, yMax, vColour2.b, xMax, yMax, vColour3.b, xF, yF);

		vOutPixelColour.x = interpR;
		vOutPixelColour.y = interpG;
		vOutPixelColour.z = interpB;
#else
		vOutPixelColour = GetColourAtPosition(x, y);
#endif
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