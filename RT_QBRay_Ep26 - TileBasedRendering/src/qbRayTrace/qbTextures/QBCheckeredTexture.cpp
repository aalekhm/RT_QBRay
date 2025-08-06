#include "QBCheckeredTexture.hpp"
#include "QBFlatTexture.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBCheckeredTexture::QBCheckeredTexture()
{
	QBRT::QBTexture::QBFlatTexture flatTextureColor1;
	QBRT::QBTexture::QBFlatTexture flatTextureColor2;

	flatTextureColor1.SetColour(qbVector4<double>(1.0, 1.0, 1.0, 1.0));
	flatTextureColor2.SetColour(qbVector4<double>(0.2, 0.2, 0.2, 1.0));

	m_vColourTexture1 = std::make_shared< QBRT::QBTexture::QBFlatTexture>(flatTextureColor1);
	m_vColourTexture2 = std::make_shared< QBRT::QBTexture::QBFlatTexture>(flatTextureColor2);
}

QBRT::QBTexture::QBCheckeredTexture::~QBCheckeredTexture()
{

}

// Function to return the color.
qbVector4<double> QBRT::QBTexture::QBCheckeredTexture::GetColor(const qbVector2<double>& vUVCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double>	vInputLoc = vUVCoords;

	qbVector3<double>	vUVCoords3; vUVCoords3.x = vInputLoc.x; vUVCoords3.y = vInputLoc.y;
	qbVector3<double>	vNewLoc = ApplyTransform(vUVCoords3);
	double				fNewU = vNewLoc.x;
	double				fNewV = vNewLoc.y;

	qbVector4<double>	vLocalColour;
	int iCheck = static_cast<int>(floor(fNewU)) + static_cast<int>(floor(fNewV));

	vLocalColour = (iCheck % 2 == 0) ? m_vColourTexture1->GetColor(vUVCoords) : m_vColourTexture2->GetColor(vUVCoords);

	return vLocalColour;
}

// Function to set the color.
void QBRT::QBTexture::QBCheckeredTexture::SetColour(const qbVector4<double>& vInputColour1, const qbVector4<double>& vInputColour2)
{
	auto colouredTexture1 = std::make_shared< QBRT::QBTexture::QBFlatTexture>();
	auto colouredTexture2 = std::make_shared< QBRT::QBTexture::QBFlatTexture>();

	colouredTexture1->SetColour(vInputColour1);
	colouredTexture2->SetColour(vInputColour2);

	m_vColourTexture1 = colouredTexture1;
	m_vColourTexture2 = colouredTexture2;
}

void QBRT::QBTexture::QBCheckeredTexture::SetColour(	const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputColouredTexture1,
														const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputColouredTexture2)
{
	m_vColourTexture1 = inputColouredTexture1;
	m_vColourTexture2 = inputColouredTexture2;
}
