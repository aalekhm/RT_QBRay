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
			virtual qbVector3<double>	GetColor(const qbVector2<double>& vUVCoords) override;

			// Function to set the color.
			void						SetColour(const qbVector3<double>& vInputColour1, const qbVector3<double>& vInputColour2);

		private:
			qbVector3<double>			m_vColour1;
			qbVector3<double>			m_vColour2;
		};
	}
}