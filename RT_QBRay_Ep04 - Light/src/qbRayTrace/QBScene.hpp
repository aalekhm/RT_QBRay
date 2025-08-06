#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"
#include "QBCamera.hpp"
#include "QBObjectBase.hpp"
#include "QBLightBase.hpp"

namespace QBRT
{
	class QBScene
	{
		public:
			// The default constructor.
			QBScene();

			// Function to perform the rendering.
			bool Render(QBImage& outputImage);

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
	};
}