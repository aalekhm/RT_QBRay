#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"

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
	};
}