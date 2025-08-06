#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"
#include "QBCamera.hpp"
#include "qbRayTrace/qbPrimitives/QBObjectSphere.hpp"
#include "qbPrimitives/QBObjectPlane.hpp"
#include "qbRayTrace/qbLights/QBPointLight.hpp"
#include "QBUtils.hpp"
#include "qbNormals/QBTextureNormal.hpp"

namespace QBRT
{
	class QBScene
	{
		public:
			// The default constructor.
			QBScene();

			// Destructor
			virtual ~QBScene();

			// Function to perform the rendering.
			bool			Render(QBImage& outputImage);
		
			// Function to cast a ray into the scene.
			static bool		CastRay(	QBRT::QBRay& castRay,
										const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
										const std::shared_ptr<QBRT::QBObjectBase>& pThisObject,
										std::shared_ptr<QBRT::QBObjectBase>& pClosestObject,
										QBRT::DATA::HitData& sClosestHitData);

			// Function to handle rendering a tile.
			void			RenderTile(QBRT::DATA::Tile* pTile);

			// Function to handle setting up the scene (to be overriden).
			virtual void	SetupSceneObjects(uint32_t iEpisode);

		// Helper Functions.
		public:

		// Private functions.
		private:
			
			
			// Function to handle rendering a pixel.
			qbVector4<double>	RenderPixel(int x, int y, int xSize, int ySize);

			// Function to convert coordinates to a linear index.
			int					Sub2Ind(int x, int y, int xSize, int ySize);

		// Private members.
		private:
			// The camera that we will use.
			QBRT::QBCamera										m_Camera;

			// The list of objects in the scene.
			std::vector<std::shared_ptr<QBRT::QBObjectBase>>	m_vObjectList;

			// The list of lights in the scene.
			std::vector<std::shared_ptr<QBRT::QBLightBase>>		m_vLightList;

		public:
			// Scene parameters.
			uint32_t											m_iXSize, m_iYSize;
	};
}