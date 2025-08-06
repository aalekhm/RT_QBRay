#pragma once
#include "QBTextureBase.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBCheckeredTexture : public QBTextureBase
		{
			public:
				// Constructor / destructor.
				QBCheckeredTexture();
				virtual ~QBCheckeredTexture() override;

				// Function to return the color.
				virtual qbVector4<double>	GetColor(const qbVector2<double>& vUVCoords) override;

				// Function to set the color.
				void						SetColour(const qbVector4<double>& vInputColour1, const qbVector4<double>& vInputColour2);

				void						SetColour(	const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputColouredTexture1,
														const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputColouredTexture2);
			private:
				std::shared_ptr<QBRT::QBTexture::QBTextureBase>	m_vColourTexture1;
				std::shared_ptr<QBRT::QBTexture::QBTextureBase>	m_vColourTexture2;
		};
	}
}