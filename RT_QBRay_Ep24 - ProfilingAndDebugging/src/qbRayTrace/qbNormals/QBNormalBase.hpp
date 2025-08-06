#pragma once

#include <memory>
#include "qbRayTrace/qbLinAlg/qbMatrix.h"
#include "qbRayTrace/qbLinAlg/qbMatrix33.hpp"
#include "qbRayTrace/qbLinAlg/qbVector.h"
#include "qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/qbLinAlg/qbVector4.hpp"
#include "qbRayTrace/QBRay.hpp"
#include "qbRayTrace/qbTextures/QBTextureBase.hpp"

namespace QBRT
{
	namespace QBNormal
	{
		class QBNormalBase
		{
			public:
				// Constructor / destructor.
				QBNormalBase();
				virtual ~QBNormalBase();

				// Function to compute the perturbation.
				virtual qbVector3<double>	ComputePerturbation(const qbVector3<double>& vNnormal, 
																const qbVector2<double>& vUVCoords);

				// Function to perturb the given normal.
				qbVector3<double>			PerturbNormal(	const qbVector3<double>& vNormal, 
															const qbVector3<double>& vPerturbation);

				// *** Function to perform numerical differentiation of a texture in UV space.
				qbVector2<double>			TextureDiff(	const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputTexture, 
															const qbVector2<double>& uvCoords);

				// Function to set the amplitude scale.
				void						SetAmplitude(double fAmplitude);

				// Function to set transform.
				void						SetTransform(	const qbVector2<double>& vTtranslation, 
															const double& fRotation, 
															const qbVector2<double>& vScale);

				// Function to apply the local transform to the given input vector.
				qbVector2<double>			ApplyTransform(	const qbVector2<double>& vInputVector);

			public:
				// Store the amplitude scale factor.
				double						m_fAmplitudeScale = 1.0;

			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix33<double>			m_GeomtericTransform{ std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0} };
		};
	}
}