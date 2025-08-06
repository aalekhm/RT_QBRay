#include "QBTextureNormal.hpp"

// Constructor / Destructor.
QBRT::QBNormal::QBTextureNormal::QBTextureNormal()
{

}

QBRT::QBNormal::QBTextureNormal::~QBTextureNormal()
{

}

// Function to compute the perturbation.
qbVector3<double> QBRT::QBNormal::QBTextureNormal::ComputePerturbation(	const qbVector3<double>& vNormal, 
																		const qbVector2<double>& vUVCoords)
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	if (m_bHasTexture)
	{
		qbVector2<double> vUVGrad = TextureDiff(m_pBaseTexture, vUVCoords);
		if (m_bReverse == false)
		{
			x = -vUVGrad.x * m_fScale;
			y = -vUVGrad.y * m_fScale;
		}
		else
		{
			x = vUVGrad.x * m_fScale;
			y = vUVGrad.y * m_fScale;
		}
	}

	qbVector3<double> vPerturbation( x, y, z );
	return PerturbNormal(vNormal, vPerturbation);
}

// Function to assign the base texture.
void QBRT::QBNormal::QBTextureNormal::AssignBaseTexture(const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputTexture)
{
	m_pBaseTexture = inputTexture;
	m_bHasTexture = true;
}
