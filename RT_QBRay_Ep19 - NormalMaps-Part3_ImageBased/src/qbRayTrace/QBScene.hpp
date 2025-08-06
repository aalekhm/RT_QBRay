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

			// Function to perform the rendering.
			bool Render(QBImage& outputImage);
		
			// Function to cast a ray into the scene.
			static bool CastRay(	QBRT::QBRay& castRay,
									const std::vector<std::shared_ptr<QBRT::QBObjectBase>>& vObjectList,
									const std::shared_ptr<QBRT::QBObjectBase>& pThisObject,
									std::shared_ptr<QBRT::QBObjectBase>& pClosestObject,
									qbVector3<double>& vClosestIntersectionPoint,
									qbVector3<double>& vClosestLocalNormal,
									qbVector4<double>& vClosestLocalColour
								);
		// Helper Functions.
		public:

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
	};
}