#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"
#include "QBCamera.hpp"
#include "QBObjectSphere.hpp"

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
			QBRT::QBCamera			m_Camera;

			// A unit sphere on the origin, for testing.
			QBRT::QBObjectSphere	m_TestSphere;
	};
}