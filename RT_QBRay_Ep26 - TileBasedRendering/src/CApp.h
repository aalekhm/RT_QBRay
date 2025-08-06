#pragma once

#include <SDL3/SDL.h>
#include "qbRayTrace/QBImage.hpp"
#include "qbRayTrace/QBScene.hpp"
#include "qbRayTrace/QBCamera.hpp"
#include "qbRayTrace/QBTimer.hpp"

//#define TEXTURE_RENDER_TEST
#if defined TEXTURE_RENDER_TEST
#include "qbRayTrace/qbTextures/QBCheckeredTexture.hpp"
#include "qbRayTrace/qbTextures/QBFlatTexture.hpp"
#include "qbRayTrace/qbTextures/QBImageTexture.hpp"
#endif

class CApp
{
	public:
		CApp();

		int		OnExecute();
		bool	OnInit();
		void	OnEvent(SDL_Event* pEvent);
		void	OnLoop();
		void	OnRender();
		void	OnPostRender();
		void	OnExit();
	private:
		void	RenderScene();
		void	RenderSceneTileBased();

		// Function to generate the tile grid.
		bool	GenerateTileGrid(int iTileSizeX, int iTileSizeY);
		// Function to handle destroying the tile grid.
		bool	DestroyTileGrid();

	private:
#if defined TEXTURE_RENDER_TEST
		void												RenderTextureTest();
		QBRT::QBTexture::QBCheckeredTexture					qbCheckeredTexture;
		QBRT::QBTexture::QBFlatTexture						qbFlatTexture;
		std::shared_ptr<QBRT::QBTexture::QBImageTexture>	qbImageTexture;
#endif
	private:
		// An instance of qbImage to store the image.
		QBImage			m_pImage;

		// An instance of the scene class.
		QBRT::QBScene	m_Scene;

		// SDL2 stuff.
		bool			m_bIsRunning;
		SDL_Window*		m_pWindow;
		SDL_Renderer*	m_pRenderer;

		QBRT::QBTimer	m_FPSTimer;

		// Array to store tiles.
		std::vector<QBRT::DATA::Tile>	m_vTiles;
		std::vector<int>				m_vTileStatusFlags;
		int								m_iNumTilesX, m_iNumTilesY;
		// Display configuration.
		uint32_t*						pTileSizedPixelData;

		uint32_t						m_iTileCounter = 0;
		uint32_t						m_iTileCountMax;

		// Function to convert tile image to texture.
		void			ConvertTileToTexture(QBRT::DATA::Tile& pTileRef);

		// Function to handle converting colors from RGB to UINT32.
		uint32_t		ConvertColor(const double fRed, const double fGreen, const double fBlue);

		void			ResetTileFlags();

		void			ClearTexture(SDL_Renderer* pRenderer, SDL_Texture* pTexture);

		// The value to be used for gamma-correction.
		double			m_fMaxLevel = 0.8;
};