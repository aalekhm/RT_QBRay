#pragma once

#include "qbRayTrace/qbLinAlg/qbVector4.hpp"

namespace QBRT
{
	namespace QBTexture
	{
		class QBColourMap
		{
			public:
				// Constructor / destructor.
				QBColourMap();
				~QBColourMap();

				// Function to set a stop as a color.
				void						SetStop(double position, const qbVector4<double>& value);

				// Function to get the color at a particular position.
				qbVector4<double>			GetColor(double position);
			private:
				std::vector<double>				m_vStopPositions;
				std::vector<qbVector4<double>>	m_StopValues;
		};
	}
}