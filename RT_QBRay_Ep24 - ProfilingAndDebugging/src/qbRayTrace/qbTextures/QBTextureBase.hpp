#pragma once
#include <memory>
#include "qbRayTrace/qbLinAlg/qbMatrix33.hpp"
#include "qbRayTrace/qbLinAlg/qbMatrix44.hpp"
#include "qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/qbLinAlg/qbVector4.hpp"
#include "qbRayTrace/QBRay.hpp"
#include "qbRayTrace/QBUtils.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBTextureBase();
				virtual ~QBTextureBase();

				// Function to retrun the color at a given point in the (u,v) coordinate system.
				// Note that the color is returned as a 4-dimensional vector (RGBA).
				virtual qbVector4<double>	GetColor(const qbVector2<double>& vUVCoords);

				// *** Function to return the actual texture value at a given point in the (u,v) coordinate system.
				virtual double				GetValue(const qbVector2<double>& vUVCoords);

				// Function to set transform.
				void						SetTransform(	const qbVector2<double>& vTranslation, 
															const double& fRotation, 
															const qbVector2<double>& vScale);

				// Function to blend RGBA colors, returning a 3-dimensional (RGB) result.
				static qbVector3<double>	BlendColors(const std::vector<qbVector3<double>>& vInputColorList);

				// Function to apply the local transform to the given input vector.
				qbVector3<double>			ApplyTransform(const qbVector3<double>& vInputVector);
			private:
			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix33<double>			m_TransformMatrix33;

		};
	}
}