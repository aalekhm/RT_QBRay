#include "QBNormalBase.hpp"

// Constructor / destructor.
QBRT::QBNormal::QBNormalBase::QBNormalBase()
{

}

QBRT::QBNormal::QBNormalBase::~QBNormalBase()
{

}

// Function to compute the perturbation.
qbVector3<double> QBRT::QBNormal::QBNormalBase::ComputePerturbation(const qbVector3<double>& vNnormal,
																	const qbVector2<double>& vUVCoords)
{
	// The default response.
	return qbVector3<double>(0.0, 0.0, 0.0);
}

// Function to perturb the given normal.
qbVector3<double> QBRT::QBNormal::QBNormalBase::PerturbNormal(	const qbVector3<double>& vNormal,
																const qbVector3<double>& vPerturbation)
{
	// Decide upon an appropriate up vector.
	qbVector3<double>	vNewUpVector(0.0, 0.0, -1.0);

	// Check if the normal vector is not too close pointing in the up direction
	// if yes, then we change its direction to point it in the positive x dirrection.
	if (vNormal.z > 0.99 || vNormal.z < -0.99)
	{
		vNewUpVector = std::vector<double>{1.0, 0.0, 0.0};
	}

	// Compute the directions (based on the tangent plane).
	qbVector3<double> pV = qbVector3<double>::cross(vNewUpVector, vNormal);
	pV.Normalize();
	qbVector3<double> pU = qbVector3<double>::cross(vNormal, pV);
	pU.Normalize();

	// Apply the perturbation on the tangent plane  that is perpendicular to the normal vector.
	qbVector3<double> vOutputPerturbation = vNormal + (pU * vPerturbation.x) + (pV * vPerturbation.y) + (vNormal * vPerturbation.z);

	// Normalize the output.
	vOutputPerturbation.Normalize();

	return vOutputPerturbation;
}

// *** Function to perform numerical differentiation of a texture in UV space.
qbVector2<double> QBRT::QBNormal::QBNormalBase::TextureDiff(	const std::shared_ptr<QBRT::QBTexture::QBTextureBase>& inputTexture,
																const qbVector2<double>& uvCoords)
{
	// We will use the symmetric difference quotient to estimate the partial derivatives of the texture
	// at the point f(u,v).
	// uGrad = f(u+h, v) - f(u-h, v) / 2h
	// vGrad = f(u, v+h) - f(u, v-h) / 2h
	double h = 0.001;
	qbVector2<double> vUDisp(h, 0.0);
	qbVector2<double> vVDisp(0.0, h);
	double uGrad = (inputTexture->GetValue(uvCoords + vUDisp) - inputTexture->GetValue(uvCoords - vUDisp)) / (2.0 * h);
	double vGrad = (inputTexture->GetValue(uvCoords + vVDisp) - inputTexture->GetValue(uvCoords - vVDisp)) / (2.0 * h);
	
	/* Form a vector for the output. 
	*/
	qbVector2<double> vOutput(uGrad, vGrad);
	return vOutput;
}


// Function to set the amplitude scale.
void QBRT::QBNormal::QBNormalBase::SetAmplitude(double fAmplitude)
{
	m_fAmplitudeScale = fAmplitude;
}

// Function to set transform.
void QBRT::QBNormal::QBNormalBase::SetTransform(	const qbVector2<double>& vTtranslation,
													const double& fRotation, 
													const qbVector2<double>& vScale)
{
	// Build the transform matrix.
	qbMatrix33<double> rotationMatrix = {std::vector<double> 
	{
		cos(fRotation), -sin(fRotation), 0.0,
		sin(fRotation), cos(fRotation), 0.0,
		0.0, 0.0, 1.0}
	};
																			
	qbMatrix33<double> scaleMatrix = {std::vector<double> 
	{
		vScale.x, 0.0, 0.0,
		0.0, vScale.y, 0.0,
		0.0, 0.0, 1.0}
	};
																		
	qbMatrix33<double> translationMatrix = {std::vector<double> 
	{
		1.0, 0.0, vTtranslation.x,
		0.0, 1.0, vTtranslation.y,
		0.0, 0.0, 1.0}
	};
																					
	// And combine to form the final transform matrix.
	m_GeomtericTransform = translationMatrix * rotationMatrix * scaleMatrix;
}

// Function to apply the local transform to the given input vector.
qbVector2<double> QBRT::QBNormal::QBNormalBase::ApplyTransform(const qbVector2<double>& vInputVector)
{
	// Copy the input vector and modify to have three elements.
	qbVector3<double> vNewInput;
	vNewInput.x = vInputVector.x;
	vNewInput.y = vInputVector.y;

	// Apply the transform.
	qbVector3<double> vResult = m_GeomtericTransform * vNewInput;

	// Produce the output.
	qbVector2<double> vOutput;
	vOutput.x = vResult.x;
	vOutput.y = vResult.y;

	return vOutput;
}