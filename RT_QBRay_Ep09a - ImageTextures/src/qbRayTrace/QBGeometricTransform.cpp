#include "QBGeometricTransform.hpp"

// Constructor / destructor.
QBRT::QBGeometricTransform::QBGeometricTransform()
{
	// Set forward and backward transforms to
	// identity matrices.
	m_matFwd.SetToIdentity();
	m_matBck.SetToIdentity();
}

QBRT::QBGeometricTransform::~QBGeometricTransform()
{

}

// Construct from a pair of matrices.
QBRT::QBGeometricTransform::QBGeometricTransform(const qbMatrix44<double>& matFwd, const qbMatrix44<double>& matBck)
{
	m_matFwd = matFwd;
	m_matBck = matBck;
}

QBRT::QBGeometricTransform::QBGeometricTransform(	const qbVector3<double>& vTranslation,
													const qbVector3<double>& vRotation,
													const qbVector3<double>& vScaling)
{
	SetTransform(vTranslation, vRotation, vScaling);
}

// Function to set translation, rotation and scale components.
void QBRT::QBGeometricTransform::SetTransform(	const qbVector3<double>& vTranslation,
												const qbVector3<double>& vRotation,
												const qbVector3<double>& vScaling) 
{
	// Define a matrix for each component of the transform.
	qbMatrix44<double>	matTransaltion;
	qbMatrix44<double>	matRotationX;
	qbMatrix44<double>	matRotationY;
	qbMatrix44<double>	matRotationZ;
	qbMatrix44<double>	matScaling;

	// Set these to identity.
	matTransaltion.SetToIdentity();
	matRotationX.SetToIdentity();
	matRotationY.SetToIdentity();
	matRotationZ.SetToIdentity();
	matScaling.SetToIdentity();

	// Populate these with the appropriate values.
	// First the translation matrix.
	matTransaltion.SetElement(0, 3, vTranslation.x);
	matTransaltion.SetElement(1, 3, vTranslation.y);
	matTransaltion.SetElement(2, 3, vTranslation.z);

	// Rotation matrices.
	matRotationZ.SetElement(0, 0, cos(vRotation.z));
	matRotationZ.SetElement(0, 1, -sin(vRotation.z));
	matRotationZ.SetElement(1, 0, sin(vRotation.z));
	matRotationZ.SetElement(1, 1, cos(vRotation.z));

	matRotationY.SetElement(0, 0, cos(vRotation.y));
	matRotationY.SetElement(0, 2, sin(vRotation.y));
	matRotationY.SetElement(2, 0, -sin(vRotation.y));
	matRotationY.SetElement(2, 2, cos(vRotation.y));

	matRotationX.SetElement(1, 1, cos(vRotation.x));
	matRotationX.SetElement(1, 2, -sin(vRotation.x));
	matRotationX.SetElement(2, 1, sin(vRotation.x));
	matRotationX.SetElement(2, 2, cos(vRotation.x));

	// And the scale matrix.
	matScaling.SetElement(0, 0, vScaling.x);
	matScaling.SetElement(1, 1, vScaling.y);
	matScaling.SetElement(2, 2, vScaling.z);

	// Combine to give the final forward transform matrix.
	m_matFwd =	matTransaltion *
				matRotationX * 
				matRotationY *
				matRotationZ *
				matScaling;

	// Compute the backwards transform.
	m_matBck = m_matFwd;
	m_matBck.Inverse();
}

// Functions to return the transform matrices.
qbMatrix44<double>& QBRT::QBGeometricTransform::GetForward()
{
	return m_matFwd;
}

qbMatrix44<double>& QBRT::QBGeometricTransform::GetBackward()
{
	return m_matBck;
}

// Function to apply the transform.
QBRT::QBRay QBRT::QBGeometricTransform::Apply(const QBRT::QBRay& inputRay, bool bDirFlag)
{
	// Create an output object.
	QBRT::QBRay outputRay;

	if (bDirFlag)
	{
		// Apply the forward transform.
		outputRay.m_vPoint1 = this->Apply(inputRay.m_vPoint1, QBRT::FWDTFORM);
		outputRay.m_vPoint2 = this->Apply(inputRay.m_vPoint2, QBRT::FWDTFORM);
		outputRay.m_vDir	= outputRay.m_vPoint2 - outputRay.m_vPoint1;
	}
	else
	{
		// Apply the backward transform.
		outputRay.m_vPoint1 = this->Apply(inputRay.m_vPoint1, QBRT::BCKTFORM);
		outputRay.m_vPoint2 = this->Apply(inputRay.m_vPoint2, QBRT::BCKTFORM);
		outputRay.m_vDir	= outputRay.m_vPoint2 - outputRay.m_vPoint1;
	}

	return outputRay;
}

qbVector3<double> QBRT::QBGeometricTransform::Apply(const qbVector3<double>& vInputVector, bool bDirFlag)
{
	// Convert inputVector to a 4-element vector.
	qbVector4<double> vTemp(vInputVector.x, vInputVector.y, vInputVector.z, 1.0);

	// Create a vector for the result.
	qbVector4<double> vResult;

	if (bDirFlag)
	{
		// Apply the forward transform.
		vResult = m_matFwd * vTemp;
	}
	else
	{
		// Apply the backward transform.
		vResult = m_matBck * vTemp;
	}

	// Reform the output as a 3-element vector.
	qbVector3<double> vOutput = qbVector3<double>(vResult.x, vResult.y, vResult.z);
	return vOutput;
}

// Overload operators.
namespace QBRT
{
	QBRT::QBGeometricTransform operator*(	const QBRT::QBGeometricTransform& geomTransformLHS,
											const QBRT::QBGeometricTransform& geomTransformRHS)
	{
		// Form the product of the two forward transforms.
		qbMatrix44<double> matFwdResult = geomTransformLHS.m_matFwd * geomTransformRHS.m_matFwd;

		// Compute the backward transform as the inverse of the forward transform.
		qbMatrix44<double> matBckResult = matFwdResult;
		matBckResult.Inverse();

		// Form the final result.
		QBRT::QBGeometricTransform matFinalResult(matFwdResult, matBckResult);
		return matFinalResult;
	}
}

// Overload the assignment operator.
QBRT::QBGeometricTransform QBRT::QBGeometricTransform::operator=(const QBRT::QBGeometricTransform& geomTransformRHS)
{
	if (this != &geomTransformRHS)
	{
		m_matFwd = geomTransformRHS.m_matFwd;
		m_matBck = geomTransformRHS.m_matBck;
	}

	return *this;
}

// Function to print transform matrix to STDOUT.
void QBRT::QBGeometricTransform::PrintMatrix(bool bDirFlag)
{
	if (bDirFlag)
	{
		Print(m_matFwd);
	}
	else
	{
		Print(m_matBck);
	}
}

// Function to allow printing of vectors.
void QBRT::QBGeometricTransform::PrintVector(const qbVector3<double>& vInVector)
{
	std::cout << std::fixed << std::setprecision(3) << vInVector.x << ", " << vInVector.y << ", " << vInVector.z;// << std::endl;
}

void QBRT::QBGeometricTransform::Print(const qbMatrix44<double>& matIN)
{
	int nRows = matIN.GetNumRows();
	int nCols = matIN.GetNumCols();

	for (int row = 0; row < nRows; ++row)
	{
		for (int col = 0; col < nCols; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << matIN.GetElement(row, col) << " ";
		}

		std::cout << std::endl;
	}
}