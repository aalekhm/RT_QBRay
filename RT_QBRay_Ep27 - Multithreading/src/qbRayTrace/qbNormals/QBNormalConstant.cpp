#include "QBNormalConstant.hpp"

// Constructor / Destructor.
QBRT::QBNormal::QBConstant::QBConstant()
{

}

QBRT::QBNormal::QBConstant::~QBConstant()
{

}
			
// Function to compute the perturbation.
qbVector3<double> QBRT::QBNormal::QBConstant::ComputePerturbation(	const qbVector3<double>& vNormal,
																	const qbVector2<double>& vUVCoords)
{
	return PerturbNormal(vNormal, m_vDisplacement);
}
