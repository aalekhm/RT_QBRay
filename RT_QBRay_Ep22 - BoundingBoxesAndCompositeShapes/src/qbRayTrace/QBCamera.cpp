#include "QBCamera.hpp"

#include "qbLinAlg/qbVector3.hpp"


#include "QBCamera.hpp"
#include "QBRay.hpp"
#include "math.h"

// The default constructor.
QBRT::QBCamera::QBCamera()
{
	// The default constructor.
	m_vCameraPosition.x = 0.0;
	m_vCameraPosition.y = -10.0;
	m_vCameraPosition.z = 0.0;

	m_vCameraLookAt.x = 0.0;
	m_vCameraLookAt.y = 0.0;
	m_vCameraLookAt.z = 0.0;

	m_vCameraUp.x = 0.0;
	m_vCameraUp.y = 0.0;
	m_vCameraUp.z = 1.0;

	m_CameraLength = 1.0;
	m_CameraHorizontalSize = 1.0;
	m_CameraAspectRatio = 1.0;
}

void QBRT::QBCamera::SetPosition(const qbVector3<double>& vNewPosition)
{
	m_vCameraPosition = vNewPosition;
}

void QBRT::QBCamera::SetLookAt(const qbVector3<double>& vNewLookAt)
{
	m_vCameraLookAt = vNewLookAt;
}

void QBRT::QBCamera::SetUp(const qbVector3<double>& vNewUp)
{
	m_vCameraUp = vNewUp;
}

void QBRT::QBCamera::SetLength(double fNewLength)
{
	m_CameraLength = fNewLength;
}

void QBRT::QBCamera::SetHorizontalSize(double fNewSize)
{
	m_CameraHorizontalSize = fNewSize;
}

void QBRT::QBCamera::SetAspect(double fNewAspectRatio)
{
	m_CameraAspectRatio = fNewAspectRatio;
}

// Method to return the position of the camera.
qbVector3<double> QBRT::QBCamera::GetPosition()
{
	return m_vCameraPosition;
}

// Method to return the look at of the camera.
qbVector3<double> QBRT::QBCamera::GetLookAt()
{
	return m_vCameraLookAt;
}

// Method to return the up vector of the camera.
qbVector3<double> QBRT::QBCamera::GetUp()
{
	return m_vCameraUp;
}

qbVector3<double> QBRT::QBCamera::GetU()
{
	return m_vProjectionScreenU;
}

qbVector3<double> QBRT::QBCamera::GetV()
{
	return m_vProjectionScreenV;
}

qbVector3<double> QBRT::QBCamera::GetScreenCenter()
{
	return m_vProjectionScreenCenter;
}

// Method to return the length of the camera.
double QBRT::QBCamera::GetLength()
{
	return m_CameraLength;
}

double QBRT::QBCamera::GetHorizontalSize()
{
	return m_CameraHorizontalSize;
}

double QBRT::QBCamera::GetAspect()
{
	return m_CameraAspectRatio;
}

void QBRT::QBCamera::UpdateCameraGeometry()
{
	// First, compute the vector from the camera position to the LookAt position.
	m_vAlignmentVector = m_vCameraLookAt - m_vCameraPosition;
	m_vAlignmentVector.Normalize();

	// Second, compute the alpha and beta unit vectors.
	m_vProjectionScreenU = qbVector3<double>::cross(m_vAlignmentVector, m_vCameraUp);
	m_vProjectionScreenU.Normalize();
	m_vProjectionScreenV = qbVector3<double>::cross(m_vProjectionScreenU, m_vAlignmentVector);
	m_vProjectionScreenV.Normalize();

	// Thirdly, compute the position of the center point of the screen.
	m_vProjectionScreenCenter = m_vCameraPosition + m_CameraLength * m_vAlignmentVector;

	// Modify the U and V vectors to match the size and aspect ratio.
	m_vProjectionScreenU = m_vProjectionScreenU * m_CameraHorizontalSize;
	m_vProjectionScreenV = m_vProjectionScreenV * (m_CameraHorizontalSize / m_CameraAspectRatio);
}

bool QBRT::QBCamera::GenerateRay(float fScreenX, float fScreenY, QBRT::QBRay& vCameraRay)
{
	// Compute the location of the screen point in world coordinates.
	qbVector3<double> vScreenWordPos_Right = m_vProjectionScreenCenter + (m_vProjectionScreenU * fScreenX);
	qbVector3<double> vScreenWorldPos = vScreenWordPos_Right + (m_vProjectionScreenV * fScreenY);

	// Use this point along with the camera position to compute the ray.
	vCameraRay.m_vPoint1 = m_vCameraPosition;
	vCameraRay.m_vPoint2 = vScreenWorldPos;
	vCameraRay.m_vDir = vScreenWorldPos - m_vCameraPosition;

	return true;
}

