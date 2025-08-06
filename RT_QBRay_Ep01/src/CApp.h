#pragma once

#include <functional>
#include <SDL3/SDL.h>
#include "./qbRayTrace/qbImage.hpp"

#define RENDER_ONCE 0
#define	SAVE_FRAME_TO_DISK 1

class CApp
{
	public:
		CApp();

		int		OnExecute();
		bool	OnInit();
		void	OnEvent(SDL_Event* pEvent);
		void	OnLoop();
		void	OnRender();
		void	OnExit();

		void	RegisterBeforeRenderPresentCallback(std::function<void(void)>& fCallbackFunc) { m_pBeforeRenderPresentCallback = fCallbackFunc; }
		void	SaveFrameToDisk(const std::string& sFile);
	private:

		static std::string		GetProjectName();
	private:
		// An instance of qbImage to store the image.
		QBImage						m_pImage;

		// SDL2 stuff.
		bool						m_bIsRunning;
		SDL_Window*					m_pWindow;
		SDL_Renderer*				m_pRenderer;
		std::function<void(void)>	m_pBeforeRenderPresentCallback;
#if (RENDER_ONCE == 1)
		bool						m_bRenderOnce;
#endif
};