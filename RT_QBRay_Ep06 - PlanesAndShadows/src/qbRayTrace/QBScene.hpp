#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"
#include "QBCamera.hpp"
#include "QBObjectBase.hpp"
#include "QBLightBase.hpp"
#include "QBObjectPlane.hpp"

namespace QBRT
{
	class QBScene
	{
		public:
			// The default constructor.
			QBScene();

			// Function to perform the rendering.
			bool Render(QBImage& outputImage);
		
		// Helper Functions.
		public:
			static void PrintVector(const char* sString, const qbVector3<double>& inputVector);
			static void PrintVector(const uint32_t iX, const uint32_t iY, const char* sString, const qbVector3<double>& vInputVector);

		// Private functions.
		private:

		// Private members.
		private:
			// The camera that we will use.
			QBRT::QBCamera										m_Camera;

			// The list of objects in the scene.
			std::vector<std::shared_ptr<QBRT::QBObjectBase>>	m_vObjectList;

			// The list of lights in the scene.
			std::vector<std::shared_ptr<QBRT::QBLightBase>>		m_vLightList;

		private:
			static uint32_t										m_iCurrentPixelX;
			static uint32_t										m_iCurrentPixelY;
	};
}