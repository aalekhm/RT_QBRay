#pragma once

#include "QBNormalBase.hpp"
#include "qbRayTrace/qbTextures/QBImageTexture.hpp"
#include <SDL3/SDL.h>
#include <random>

namespace QBRT
{
	namespace QBNormal
	{
		class QBImageNormal : public QBNormalBase
		{
			public:
				// Constructor / Destructor.
				QBImageNormal();
				virtual ~QBImageNormal() override;
				
				// Function to load the image to be used.
				bool							LoadImage(std::string sFilename);
			
				// Function to compute the perturbation.
				virtual qbVector3<double>		ComputePerturbation(const qbVector3<double>& vNormal, const qbVector2<double>& vUVCoords) override;
				
			private:
				// Function to return the value of a pixel in the image surface.													
				qbVector4<double>				GetColourAtPosition(int x, int y);
				
			public:
				bool							m_bReverseXY = false;
				
			private:
				std::shared_ptr<QBRT::QBTexture::QBImageTexture>	m_pImageTexture = nullptr;
		};
	}
}