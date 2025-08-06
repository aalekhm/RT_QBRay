#pragma once

#include "QBNormalBase.hpp"
#include <random>

namespace QBRT
{
	namespace QBNormal
	{
		class QBConstant : public QBNormalBase
		{
			public:
				// Constructor / Destructor.
				QBConstant();
				virtual ~QBConstant() override;
			
				// Function to compute the perturbation.
				virtual qbVector3<double>	ComputePerturbation(const qbVector3<double>& vNormal,
																const qbVector2<double>& vUVCoords) override;
				
			public:
				qbVector3<double>	m_vDisplacement;
				
			private:
		};
	}
}

