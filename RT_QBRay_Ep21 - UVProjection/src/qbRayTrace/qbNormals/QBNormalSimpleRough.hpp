#pragma once

#include "QBNormalBase.hpp"
#include <random>

namespace QBRT
{
	namespace QBNormal
	{
		class QBNormalSimpleRough : public QBNormalBase
		{
			public:
				// Constructor / Destructor.
				QBNormalSimpleRough();
				virtual ~QBNormalSimpleRough() override;
			
				// Function to compute the perturbation.
				virtual qbVector3<double>		ComputePerturbation(const qbVector3<double>& vNormal,
																const qbVector2<double>& vUVCoords) override;
				
			public:
				std::shared_ptr<std::mt19937>	m_pRandom;
				
			private:
		};
	}
}

