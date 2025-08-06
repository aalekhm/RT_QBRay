#include "CApp.h"

#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720

std::string CApp::GetProjectName()
{
	return std::string(__PROJECT_NAME__);
}

// The constructor (default)
CApp::CApp()
{
	m_bIsRunning = true;
	m_pWindow = NULL;
	m_pRenderer = NULL;
#if (RENDER_ONCE == 1)
	m_bRenderOnce = true;
#endif

	std::function<void(void)> fOnBeforePresentCallback = [=](void)
	{
#if (RENDER_ONCE == 1 && SAVE_FRAME_TO_DISK == 1)
		std::string sOutFileName = "..\\Content\\OutFrames\\";
		{
			sOutFileName.append(CApp::GetProjectName());
			sOutFileName.append(".bmp");
		}
		SaveFrameToDisk(sOutFileName);
#endif
	};

	RegisterBeforeRenderPresentCallback(fOnBeforePresentCallback);
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
		
		// Initialise the qbImage instance.
		m_pImage.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, m_pRenderer);
	}
	else
	{
		return false;
	}

	return true;
}

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

#if (RENDER_ONCE == 1)
		if (m_bRenderOnce)
		{
#endif
		OnLoop();
		OnRender();
#if (RENDER_ONCE == 1)
			m_bRenderOnce = false;
		}
#endif
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
}

void CApp::OnRender()
{
	RenderScene();
}

void CApp::RenderScene()
{
	// Set the background colour to white.
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(m_pRenderer);

	// Render the scene.
	m_Scene.Render(m_pImage);

	// Display the image.
	m_pImage.Display();

	if (m_pBeforeRenderPresentCallback)
	{
		m_pBeforeRenderPresentCallback();
	}

	// Show the result.
	SDL_RenderPresent(m_pRenderer);
}

void CApp::SaveFrameToDisk(const std::string& sFile)
{
	SDL_Rect outRect { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// Read pixels from the texture into the surface
	SDL_Surface* pSurface = SDL_RenderReadPixels(m_pImage.GetRenderer(), &outRect);
	if (pSurface != nullptr)
	{
		SDL_SaveBMP(pSurface, sFile.c_str());
	}
}

void CApp::OnExit()
{
	// Tidy up SDL2 stuff.
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = NULL;
	SDL_Quit();
}

// PRIVATE FUNCTION
void CApp::PrintVector(const char* sString, const qbVector3<double>& vInputVector)
{
	std::cout
		<< std::fixed
		<< std::setprecision(3)
		<< sString
		<< vInputVector.x
		<< ", "
		<< vInputVector.y
		<< ", "
		<< vInputVector.z
		<< std::endl;
}














