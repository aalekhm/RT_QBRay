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
qbVector4<double> QBRT::QBTexture::QBTextureBase::GetColor(const qbVector2<double>& vUVCoords)
{
	// Setup the output vector.
	qbVector4<double> vOutputColour;

	return vOutputColour;
}

// Function to set transform.
void QBRT::QBTexture::QBTextureBase::SetTransform(	const qbVector3<double>& vTranslation,
										const double& fRotation,
										const qbVector3<double>& vScale)
{
	// Build the transform matrix.
	qbMatrix33<double> matRotationZ = {std::vector<double>
	{
		cos(fRotation), -sin(fRotation), 0.0,
		sin(fRotation), cos(fRotation), 0.0,
		0.0, 0.0, 1.0
	}};
																			
	qbMatrix33<double> matScaling = {std::vector<double>
	{
		vScale.x, 0.0, 0.0,
		0.0, vScale.y, 0.0,
		0.0, 0.0, 1.0
	}};
																		
	qbMatrix33<double> matTransaltion = {std::vector<double>
	{
		1.0, 0.0, vTranslation.x,
		0.0, 1.0, vTranslation.y,
		0.0, 0.0, 1.0
	}};

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
	vNewInput.x = vInputVector.x;
	vNewInput.y = vInputVector.y;
	
	// Apply the transform.
	qbVector3<double> result = m_TransformMatrix33 * vNewInput;
	
	// Produce the output.
	qbVector3<double> vOutput;
	vOutput.x = result.x;
	vOutput.y = result.y;
	
	return vOutput;
}
