#include "QBImage.hpp"

// The default constructor.
QBImage::QBImage()
{
	m_iXSize = 0;
	m_iYSize = 0;
	m_pTexture = nullptr;
	m_pPixelData = nullptr;
}

// The destructor.
QBImage::~QBImage()
{
	if (m_pTexture != nullptr)
	{
		SDL_DestroyTexture(m_pTexture);
	}

	// Destroy the pixel buffer.
	if (m_pPixelData != nullptr)
	{
		delete[] m_pPixelData;
	}
}

// Function to initialize
void QBImage::Initialize(const uint32_t iXSize, const uint32_t iYSize, SDL_Renderer* pRenderer)
{
	// Store the dimensions.
	m_iXSize = iXSize;
	m_iYSize = iYSize;

	m_ColourChannel = new qbVector3<double>[iXSize * iYSize];

	// Allocate memory for a pixel buffer.
	m_pPixelData = new uint32_t[iXSize * iYSize];

	// Store the pointer to the renderer.
	m_pRenderer = pRenderer;

	// Initialise the texture.
	InitTexture();
}

void QBImage::InitTexture()
{
	// Delete any previously created texture before we create a new one.
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);

	// Create the texture that will store the image.
	SDL_Surface* tempSurface = SDL_CreateSurface(m_iXSize, m_iYSize, SDL_PixelFormat::SDL_PIXELFORMAT_RGBA32);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_DestroySurface(tempSurface);
}

// Function to set pixels
void QBImage::SetPixel(const uint32_t iX, const uint32_t iY, const double fRed, const double fGreen, const double fBlue)
{
	int iPos = iX + (m_iXSize * iY);
	qbVector3<double>& vColour = m_ColourChannel[iPos];
	vColour.r = fRed;
	vColour.g = fGreen;
	vColour.b = fBlue;

	if (fRed > m_fMaxRed)				m_fMaxRed = fRed;
	if (fGreen > m_fMaxGreen)			m_fMaxGreen = fGreen;
	if (fBlue > m_fMaxBlue)				m_fMaxBlue = fBlue;
	
	if (m_fMaxRed > m_fOverallMax)		m_fOverallMax = m_fMaxRed;
	if (m_fMaxGreen > m_fOverallMax)	m_fOverallMax = m_fMaxGreen;
	if (m_fMaxBlue > m_fOverallMax)		m_fOverallMax = m_fMaxBlue;

	m_fOneOverOverallMax = 1.0 / m_fOverallMax;
}

void QBImage::RenderClear()
{
	m_fMaxRed = 0.0;
	m_fMaxGreen = 0.0;
	m_fMaxBlue = 0.0;
	m_fOverallMax = 0.0;
}

// Function to return the image for display.
void QBImage::Display()
{
	memset(m_pPixelData, 0, m_iXSize * m_iYSize * sizeof(uint32_t));

	for (uint32_t y = 0; y < m_iYSize; y++)
	{
		for (uint32_t x = 0; x < m_iXSize; x++)
		{
			int iPos = x + (m_iXSize * y);
			qbVector3<double> vColour = m_ColourChannel[iPos];
			m_pPixelData[iPos] = ConvertColor(vColour.r, vColour.g, vColour.b);
		}
	}

	// Update the texture with the pixel buffer.
	SDL_UpdateTexture(m_pTexture, NULL, m_pPixelData, m_iXSize * sizeof(uint32_t));

	// Copy the texture to the renderer.
	SDL_FRect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = static_cast<float>(m_iXSize);
	srcRect.h = static_cast<float>(m_iYSize);
	bounds = srcRect;
	SDL_RenderTexture(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

Uint32 QBImage::ConvertColor(const double fRed, const double fGreen, const double fBlue)
{
	// Convert colours to unsigned char.
	unsigned char r = static_cast<char>((fRed * m_fOneOverOverallMax) * 255.0f);
	unsigned char g = static_cast<char>((fGreen * m_fOneOverOverallMax) * 255.0f);
	unsigned char b = static_cast<char>((fBlue * m_fOneOverOverallMax) * 255.0f);
	unsigned char a = static_cast<char>(255.0f);

	return (a << 24) | (b << 16) | (g << 8) | r;
}

uint32_t QBImage::GetXSize()
{
	return m_iXSize;
}

uint32_t QBImage::GetYSize()
{
	return m_iYSize;
}

// Function to compute maximum values.
void QBImage::ComputeMaxValues()
{
	m_fMaxRed = 0.0;
	m_fMaxGreen = 0.0;
	m_fMaxBlue = 0.0;
	m_fOverallMax = 0.0;
	
	for (uint32_t x = 0; x < m_iXSize; x++)
	{
		for (uint32_t y = 0; y < m_iYSize; y++)
		{
			int iPos = x + (m_iXSize * y);
			qbVector3<double>& vColour = m_ColourChannel[iPos];

			if (vColour.r > m_fMaxRed)				m_fMaxRed = vColour.r;
			if (vColour.g > m_fMaxGreen)			m_fMaxGreen = vColour.g;
			if (vColour.b > m_fMaxBlue)				m_fMaxBlue = vColour.b;

			if (m_fMaxRed > m_fOverallMax)		m_fOverallMax = m_fMaxRed;
			if (m_fMaxGreen > m_fOverallMax)	m_fOverallMax = m_fMaxGreen;
			if (m_fMaxBlue > m_fOverallMax)		m_fOverallMax = m_fMaxBlue;
		}
	}
}
