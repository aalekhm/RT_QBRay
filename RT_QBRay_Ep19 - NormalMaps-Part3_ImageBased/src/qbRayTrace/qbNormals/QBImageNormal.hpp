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
				// Functions to handle interpolation.
				double							LinearInterp(	const double &x0, 
																const double &y0, 
																const double &x1, 
																const double &y1, 
																const double &x);
				double							BilinearInterp(	const double &x0, const double &y0, const double &v0,
																const double &x1, const double &y1, const double &v1,
																const double &x2, const double &y2, const double &v2,
																const double &x3, const double &y3, const double &v3,
																const double &x, const double &y);
			
				// Function to return the value of a pixel in the image surface.													
				qbVector4<double>				GetColourAtPosition(int x, int y);
				
			public:
				bool							m_bReverseXY = false;
				
			private:
				std::shared_ptr<QBRT::QBTexture::QBImageTexture>	m_pImageTexture = nullptr;
		};
	}
}