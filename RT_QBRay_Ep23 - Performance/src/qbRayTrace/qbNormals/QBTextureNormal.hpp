#pragma once

#include "QBNormalbase.hpp"
#include <random>

namespace QBRT
{
	namespace QBNormal
	{
		class QBTextureNormal : public QBNormalBase
		{
			public:
				// Constructor / Destructor.
				QBTextureNormal();
				virtual ~QBTextureNormal() override;

				// Function to compute the perturbation.
				virtual qbVector3<double>	ComputePerturbation(const qbVector3<double>& vNormal, const qbVector2<double>& vUVCoords) override;

				// Function to assign the base texture.
				void						AssignBaseTexture(const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputTexture);

			public:
				double											m_fScale = 1.0;
				bool											m_bReverse = false;

			private:
				bool											m_bHasTexture = false;
				std::shared_ptr<QBRT::QBTexture::QBTextureBase> m_pBaseTexture;
		};
	}
}
