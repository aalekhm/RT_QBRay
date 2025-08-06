#include "QBTextureBase.hpp"

QBRT::QBTexture::QBTextureBase::QBTextureBase()
{
	m_TransformMatrix33.SetToIdentity();
}

QBRT::QBTexture::QBTextureBase::~QBTextureBase()
{

}

// Function to retrun the color at a given point in the (u,v) coordinate system.
// Note that the color is returned as a 4-dimensional vector (RGBA).
qbVector3<double> QBRT::QBTexture::QBTextureBase::GetColor(const qbVector2<double>& vUVCoords)
{
	// Setup the output vector.
	qbVector3<double> vOutputColour;

	return vOutputColour;
}

// Function to set transform.
void QBRT::QBTexture::QBTextureBase::SetTransform(	const qbVector3<double>& vTranslation,
										const double& fRotation,
										const qbVector3<double>& vScale)
{
	// Build the transform matrix.
	qbMatrix33<double>	matTransaltion;
	qbMatrix33<double>	matRotationZ;
	qbMatrix33<double>	matScaling;

	matTransaltion.SetToIdentity();
	matTransaltion.SetElement(0, 2, vTranslation.x);
	matTransaltion.SetElement(1, 2, vTranslation.y);

	matRotationZ.SetToIdentity();
	matRotationZ.SetElement(0, 0, cos(fRotation));
	matRotationZ.SetElement(0, 1, -sin(fRotation));
	matRotationZ.SetElement(1, 0, sin(fRotation));
	matRotationZ.SetElement(1, 1, cos(fRotation));

	matScaling.SetToIdentity();
	matScaling.SetElement(0, 0, vScale.x);
	matScaling.SetElement(1, 1, vScale.y);

	// And combine to form the final transform matrix.
	m_TransformMatrix33 = matTransaltion * matRotationZ * matScaling;
}

// Function to blend RGBA colors, returning a 3-dimensional (RGB) result.
qbVector3<double> QBRT::QBTexture::QBTextureBase::BlendColors(const std::vector<qbVector3<double>>& vInputColorList)
{
	// Setup the output color.
	qbVector3<double> vOutputColor{ 3 };

	// Return the output.
	return vOutputColor;
}

// Function to apply the local transform to the given input vector.
qbVector3<double> QBRT::QBTexture::QBTextureBase::ApplyTransform(const qbVector3<double>& vInputVector)
{
	// Copy the input vector and modify to have three elements.
	qbVector3<double> vNewInput;
	vNewInput.SetElement(0, vInputVector.x);
	vNewInput.SetElement(1, vInputVector.y);
	
	// Apply the transform.
	qbVector3<double> result = m_TransformMatrix33 * vNewInput;
	
	// Produce the output.
	qbVector3<double> vOutput;
	vOutput.x = result.x;
	vOutput.y = result.y;
	
	return vOutput;
}
