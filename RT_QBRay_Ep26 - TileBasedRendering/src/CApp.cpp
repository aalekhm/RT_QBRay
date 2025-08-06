#include "CApp.h"
#include "qbRayTrace/QBUtils.hpp"
#include <chrono>

#define __FPS_GRAB__	m_FPSTimer.GrabTime();

#if defined(TEXTURE_RENDER_TEST)
#include <SDL3/SDL.h>
void CApp::RenderTextureTest()
{
	uint32_t iImageWidth = 0, iImageHeight = 0;
	if (qbImageTexture == nullptr)
	{
		qbImageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();		
		qbImageTexture->LoadImage("..\\Content\\charlie.bmp");
	}

	if (qbImageTexture)
	{
		iImageWidth = qbImageTexture->GetWidth();
		iImageHeight = qbImageTexture->GetHeight();
	}

	qbCheckeredTexture.SetTransform(	qbVector3<double>(0.0, 0.0, 0.0),
										M_PI / 4.0, 
										qbVector3<double>(4.0, 4.0, 4.0));

	// Render the texture.
	for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (uint32_t x = 0; x < SCREEN_WIDTH; ++x)
		{
			qbVector3<double> vPixelColour;

			// Compute u,v
			double u = (static_cast<double>(x) / (SCREEN_WIDTH >> 1)) - 1.0;
			double v = (static_cast<double>(y) / (SCREEN_HEIGHT >> 1)) - 1.0;
			qbVector2<double> vUVCoords(u, v);

			// Get the colour from the texture.
			if (x < qbImageTexture->GetWidth() && y < iImageHeight)
			{
				// Normalized between [0-1]
				vUVCoords.x = (static_cast<double>(x) / iImageWidth);
				vUVCoords.y = (static_cast<double>(y) / iImageHeight);

				vPixelColour = qbImageTexture->GetColor(vUVCoords);
			}
			else
			{			
				vPixelColour = qbCheckeredTexture.GetColor(vUVCoords);
			}	

			// Update this pixel of the image.
			m_pImage.SetPixel(	x, y, 
								vPixelColour.r, 
								vPixelColour.g,
								vPixelColour.b
							);
		}
	}
}
#endif

// The constructor (default)
CApp::CApp()
{
	m_bIsRunning = true;
	m_pWindow = NULL;
	m_pRenderer = NULL;

	m_FPSTimer.SetFPSCaptureTimeEveryNSecs(2.0);
}

bool CApp::OnInit()
{
	SDL_InitFlags sdlInitFlags = 0;
	if (SDL_Init(sdlInitFlags) == false)
	{
		return false;
	}

	SDL_WindowFlags sdlWindowFlags = 0;
	m_pWindow = SDL_CreateWindow("qbRayTracer", SCREEN_WIDTH, SCREEN_HEIGHT, sdlWindowFlags);

	if (m_pWindow != NULL)
	{
		// Initialise the renderer.
		m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL);
		
		// We now initialize the scene with the window dimensions and
		// then generate a tile grid with tiles of the specified size.
		// Initialize the scene.
		m_Scene.m_iXSize = SCREEN_WIDTH;
		m_Scene.m_iYSize = SCREEN_HEIGHT;

		// Initialize the tile grid.
		if (GenerateTileGrid(128, 90) == false)
		{
			std::cout << "Failed to generate tile grid." << std::endl;
			return false;
		}
		
		// Set the background colour to white.
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
		SDL_RenderClear(m_pRenderer);

		// Show the result.
		SDL_RenderPresent(m_pRenderer);
	}
	else
	{
		return false;
	}

	return true;
}

static int iFrameCount = 0;

int CApp::OnExecute()
{
	SDL_Event event;

	if (OnInit() == false)
	{
		return -1;
	}

	while (m_bIsRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}

		OnLoop();
		OnRender();
		OnPostRender();

		/*
			The delay here seems counterintuitive, but it actually makes the
			rendering faster (with multi-threading). The reason for this,
			I think, is that it reduces the load imposed by looping through
			this code allowing more of the CPU time to be used for actual
			rendering. I have tried different values, reducing it below 1
			seems to slow things down and increasing it above 4 also slows
			things down. It would seem that somewhere between 1 and 4 is the
			'sweet spot', so I have left it at 1.
		*/
		SDL_Delay(50);

		__FPS_GRAB__
	}

	OnExit();
	return 0;
}

void CApp::OnEvent(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		m_bIsRunning = false;
	}
}

void CApp::OnLoop()
{
	/*
		The actual rendering is now handled here, each time we come through
		this loop. At the moment, before implementing multi-threading, we
		proceed by looping through all of the tiles and finding the first
		one that has not been rendered yet (as indicated by m_tileFlags).
		We then call the RenderTile function from the scene base class and
		pass a reference to the relevent tile as the only parameter. Finally,
		we update m_tileFlags for this tile to indicate that it has now been
		rendered and then break out of the loop. We don't want to end up
		rendering every tile all at once, we want to one tile each time
		we come through the OnLoop() function.
	*/
	// Loop through all tiles and find the first one that hasn't been rendered yet.
	{
		QBRT::DATA::Tile& pTileRef = m_vTiles[m_iTileCounter];

		if (m_vTileStatusFlags[m_iTileCounter] == 0)
		{
			// This tile has not been rendered, so render it now.
			m_Scene.RenderTile(&pTileRef);
			
			// Set the tile flag to indicate that this tile has been rendered.
			m_vTileStatusFlags[m_iTileCounter] = 2;
		}
	}
}

void CApp::OnRender()
{
	RenderSceneTileBased();
}

void CApp::RenderSceneTileBased()
{
	// Converstion factors from screen width/height to window width/height.
	// For future versions.
	double widthFactor = 1.0;
	double heightFactor = 1.0;
	
	/*
		The actual display is now generated here. We loop over all of the tiles
		and wherever we find one that has been rendered (tileFlags == 2), then
		we check if we have already display this tile (textureComplete) and if
		not we convert the image data to an SDL texture and then use SDL_RenderCopy
		to copy that texture to the right place in the window.
		
		In a single-thread implementation, this approach doesn't necessarily make
		much sense, but it forms the foundation on which we can build our multi-threaded
		version.
	*/
	
	// Render the tiles.
	for (int i = 0; i <= m_iTileCounter && i < m_iTileCountMax; ++i)
	{
		QBRT::DATA::Tile& pTileRef = m_vTiles[i];
		{
			SDL_FRect srcRect, dstRect;
			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = m_vTiles.at(i).iXSize;
			srcRect.h = m_vTiles.at(i).iYSize;

			dstRect.x = static_cast<int>(std::round(static_cast<double>(m_vTiles.at(i).iX) * widthFactor));
			dstRect.y = static_cast<int>(std::round(static_cast<double>(m_vTiles.at(i).iY) * heightFactor));
			dstRect.w = static_cast<int>(std::round(static_cast<double>(m_vTiles.at(i).iXSize) * widthFactor));
			dstRect.h = static_cast<int>(std::round(static_cast<double>(m_vTiles.at(i).iYSize) * heightFactor));
			
			/*
				If the textureComplete flag for this tile is not set, then it means that the tile
				has been rendered, but not yet converted to a texture. So we do that here and
				then set the textureComplete flag and blit the texture into the renderer.
				Note that once this is done, we don't do this again for this tile meaning
				that we don't keep updating each tile every time we go through this loop.
				This helps to keep things as efficient as possible.
			*/
			if(pTileRef.bIsTextureComplete == false)
			{
				ConvertTileToTexture(pTileRef);
			}

			SDL_RenderTexture(m_pRenderer, pTileRef.pTexture, &srcRect, &dstRect);
		}
	}
	
	// Show the result.
	SDL_RenderPresent(m_pRenderer);
}

void CApp::RenderScene()
{
	// Set the background colour to white.
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(m_pRenderer);
	m_pImage.RenderClear();

	// Render the scene.
#if defined TEXTURE_RENDER_TEST
	RenderTextureTest();
#else
	m_Scene.Render(m_pImage);
#endif

	// Display the image.
	m_pImage.Display();

	// Show the result.
	SDL_RenderPresent(m_pRenderer);
}

// Function to generate the tile grid.
bool CApp::GenerateTileGrid(int iTileSizeX, int iTileSizeY)
{
	// How many tiles will fit horizontally?
	int iNumTilesX = std::floor(SCREEN_WIDTH / iTileSizeX);
	m_iNumTilesX = iNumTilesX;
	
	// How many tiles will fit vertically?
	int iNumTilesY = std::floor(SCREEN_HEIGHT / iTileSizeY);
	m_iNumTilesY = iNumTilesY;
	
	// Create the texture that will store the image.
	SDL_Surface* pTempSurface = SDL_CreateSurface(iTileSizeX, iTileSizeY, SDL_PixelFormat::SDL_PIXELFORMAT_RGBA32);
	
	// Allocate memory for a pixel buffer for a size of a Tile.
	pTileSizedPixelData = new uint32_t[iTileSizeX * iTileSizeY];

	// Generate the actual tiles.
	for (int y = 0; y < iNumTilesY; ++y)
	{
		for (int x = 0; x < iNumTilesX; ++x)
		{
			QBRT::DATA::Tile sTempTile;
			{
				sTempTile.iX = x * iTileSizeX;
				sTempTile.iY = y * iTileSizeY;
				sTempTile.iXSize = iTileSizeX;
				sTempTile.iYSize = iTileSizeY;
				sTempTile.iRenderComplete = 0;
				sTempTile.pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
				sTempTile.vRGBData.resize(sTempTile.iXSize * sTempTile.iYSize);
			}
			m_vTiles.push_back(sTempTile);		
		}
	}
	
	m_iTileCounter = 0;
	m_iTileCountMax = m_vTiles.size();

	// Set all the tile flags to zero.
	for (int i = 0; i < m_iTileCountMax; ++i)
	{
		m_vTileStatusFlags.push_back(0);
	}
			
	// Tidy up before returning.
	SDL_DestroySurface(pTempSurface);	
	return true;				
}

// Function to destroy the tile grid.
bool CApp::DestroyTileGrid()
{
	for (int i = 0; i < m_vTiles.size(); ++i)
	{
		if (m_vTiles.at(i).pTexture != NULL)
		{
			SDL_DestroyTexture(m_vTiles.at(i).pTexture);
		}
	
	}

	return true;
}

// Function to convert an RGB image to a texture.
void CApp::ConvertTileToTexture(QBRT::DATA::Tile& pTileRef)
{
	//// Clear the pixel buffer.
	memset(pTileSizedPixelData, 0, pTileRef.iXSize * pTileRef.iYSize * sizeof(uint32_t));
	
	// Copy the image into tempPixels.
	for (int i = 0; i < pTileRef.iXSize * pTileRef.iYSize; ++i)
	{
		pTileSizedPixelData[i] = ConvertColor(	pTileRef.vRGBData.at(i).x,
												pTileRef.vRGBData.at(i).y, 
												pTileRef.vRGBData.at(i).z);
	}
	
	// Update the texture with the pixel buffer.
	SDL_UpdateTexture(pTileRef.pTexture, NULL, pTileSizedPixelData, pTileRef.iXSize * sizeof(uint32_t));

	pTileRef.bIsTextureComplete = true;
}

// Function to convert colours to Uint32
uint32_t CApp::ConvertColor(const double fRed, const double fGreen, const double fBlue)
{
	// Convert the colours to unsigned integers.
	double fNewRed		= std::max(std::min(std::pow(fRed,		m_fMaxLevel), 1.0), 0.0);
	double fNewGreen	= std::max(std::min(std::pow(fGreen,	m_fMaxLevel), 1.0), 0.0);
	double fNewBlue		= std::max(std::min(std::pow(fBlue,		m_fMaxLevel), 1.0), 0.0);
	
	unsigned char r = static_cast<unsigned char>(fNewRed * 255.0);
	unsigned char g = static_cast<unsigned char>(fNewGreen * 255.0);
	unsigned char b = static_cast<unsigned char>(fNewBlue * 255.0);
	unsigned char a = static_cast<char>(255.0f);

	return (a << 24) | (b << 16) | (g << 8) | r;
}

void CApp::OnPostRender()
{
	if (m_iTileCounter >= m_iTileCountMax)
	{
		ResetTileFlags();
	}
	else
	{
		m_iTileCounter++;
	}
}


// Function to reset the tile flags.
void CApp::ResetTileFlags()
{
	m_iTileCounter = 0;
	for (int i = 0; i < m_iTileCountMax; ++i)
	{
		QBRT::DATA::Tile& pTileRef = m_vTiles[i];
		{
			m_vTileStatusFlags[i] = 0;
			pTileRef.bIsTextureComplete = false;

			ClearTexture(m_pRenderer, pTileRef.pTexture);
		}
	}
}

void CApp::ClearTexture(SDL_Renderer* pRenderer, SDL_Texture* pTexture)
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
	SDL_RenderClear(pRenderer);
	SDL_SetRenderTarget(pRenderer, pTexture);

	// Show the result.
	SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
	// Tidy up the tile grid.
	bool bResult = DestroyTileGrid();

	// Tidy up SDL2 stuff.
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_Quit();
}