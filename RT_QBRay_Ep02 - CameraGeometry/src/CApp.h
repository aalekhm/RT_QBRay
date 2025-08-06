#pragma once

#include <functional>
#include <SDL3/SDL.h>
#include "qbRayTrace/QBImage.hpp"
#include "qbRayTrace/QBScene.hpp"
#include "qbRayTrace/QBCamera.hpp"

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
		void	PrintVector(const char* sString, const qbVector3<double>& vInputVector);

		static std::string		GetProjectName();
	private:
		// An instance of qbImage to store the image.
		QBImage						m_pImage;

		// An instance of the scene class.
		QBRT::QBScene				m_Scene;

		// SDL2 stuff.
		bool						m_bIsRunning;
		SDL_Window*					m_pWindow;
		SDL_Renderer*				m_pRenderer;
		std::function<void(void)>	m_pBeforeRenderPresentCallback;
#if (RENDER_ONCE == 1)
		bool						m_bRenderOnce;
#endif
};