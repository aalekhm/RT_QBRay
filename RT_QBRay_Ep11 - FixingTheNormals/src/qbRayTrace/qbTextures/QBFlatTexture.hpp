#pragma once
#include "QBTextureBase.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBFlatTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBFlatTexture();
				virtual ~QBFlatTexture() override;

				// Function to return the color.
				virtual qbVector3<double>	GetColor(const qbVector2<double>& vUVCoords) override;

				// Function to set the color.
				void						SetColour(const qbVector3<double>& vInputColour);

			private:
				qbVector3<double>			m_vColour;
		};
	}
}