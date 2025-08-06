#include "QBCheckeredTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBCheckeredTexture::QBCheckeredTexture()
{
	m_vColour1.r = 1.0;
	m_vColour1.g = 1.0;
	m_vColour1.b = 1.0;

	m_vColour2.r = 0.2;
	m_vColour2.g = 0.2;
	m_vColour2.b = 0.2;
}

QBRT::QBTexture::QBCheckeredTexture::~QBCheckeredTexture()
{

}

// Function to return the color.
qbVector3<double> QBRT::QBTexture::QBCheckeredTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double>	vInputLoc = vUVCoords;

	qbVector3<double>	vUVCoords3; vUVCoords3.x = vInputLoc.x; vUVCoords3.y = vInputLoc.y;
	qbVector3<double>	vNewLoc = ApplyTransform(vUVCoords3);
	double				fNewU = vNewLoc.x;
	double				fNewV = vNewLoc.y;

	qbVector3<double>	vLocalColour;
	int iCheck = static_cast<int>(floor(fNewU)) + static_cast<int>(floor(fNewV));

	vLocalColour = (iCheck % 2 == 0) ? m_vColour1 : m_vColour2;

	return vLocalColour;
}

// Function to set the color.
void QBRT::QBTexture::QBCheckeredTexture::SetColour(const qbVector3<double>& vInputColour1, const qbVector3<double>& vInputColour2)
{
	m_vColour1 = vInputColour1;
	m_vColour2 = vInputColour2;
}
