#include "QBRayMarchBase.hpp"

// Default constructor.
QBRT::RM::QBRayMarchBase::QBRayMarchBase()
{
	// Define the tolerance.
	m_fEpsilon = 1e-12;

	// Define the maximum number of steps allowed.
	m_iMaxSteps = 100;
}
				
// Destructor.
QBRT::RM::QBRayMarchBase::~QBRayMarchBase()
{

}
				
// Override the function to test for intersections.
bool QBRT::RM::QBRayMarchBase::TestIntersection(	const QBRay& castRay,
													qbVector3<double>& vIntersectionPoint, 
													qbVector3<double>& vLocalNormal, 
													qbVector4<double>& vLocalColour)
{
	// Check if an object function has been defined.
	if (m_bHaveObjectFunc)
	{
		// Check if the object is visible.
		//if (!m_bIsVisible)
		//	return false;

		// Copy the ray and apply the backwards transform.
		QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

		qbVector3<double> vBoundPointOfIntersection;
		qbVector3<double> vBoundNormal;
		qbVector4<double> vBoundColour;
		// Test for intersection with the bounding box.
		if(m_BoundingBox.TestIntersection(	bckRay, 
											vBoundPointOfIntersection,
											vBoundNormal,
											vBoundColour)
		) {
			// Extract the ray direction
			qbVector3<double> vDir = bckRay.m_vDir;
			vDir.Normalize();

			qbVector3<double> vCurentLocation = bckRay.m_vPoint1;
			int iStepCount = 0;
			double fDistance = EvaluateSDF(&vCurentLocation, &m_vParms);

			// Main Loop.
			while(	(fDistance > m_fEpsilon)
					&&
					(iStepCount < m_iMaxSteps)
			) {
				vCurentLocation = vCurentLocation + (vDir * fDistance);

				fDistance = EvaluateSDF(&vCurentLocation, &m_vParms);

				// Can check with the Bounding Box Max distance or Bounding Box Circle.
				if (fDistance > 1e6)
				{
					iStepCount = m_iMaxSteps;
					break;
				}

				iStepCount++;
			}

			// If m_maxSteps exceeded, then no valid intersection found.
			if (iStepCount == m_iMaxSteps)
			{
				return false;
			}

			// Otherwise, we have a valid intersection at currentLoc.
			// Transform the intersection point back into world coordinates.
			vIntersectionPoint = m_GeomTransform.Apply(vCurentLocation, QBRT::FWDTFORM);

			// Compute the local normal.
			qbVector3<double>	vSurfaceNormal;
			
			qbVector3<double>	vX1 = vCurentLocation - m_vXDisp;
			qbVector3<double>	vX2 = vCurentLocation + m_vXDisp;

			qbVector3<double>	vY1 = vCurentLocation - m_vYDisp;
			qbVector3<double>	vY2 = vCurentLocation + m_vYDisp;

			qbVector3<double>	vZ1 = vCurentLocation - m_vZDisp;
			qbVector3<double>	vZ2 = vCurentLocation + m_vZDisp;

			vSurfaceNormal.x = EvaluateSDF(&vX2, &m_vParms) - EvaluateSDF(&vX1, &m_vParms);
			vSurfaceNormal.y = EvaluateSDF(&vY2, &m_vParms) - EvaluateSDF(&vY1, &m_vParms);
			vSurfaceNormal.z = EvaluateSDF(&vZ2, &m_vParms) - EvaluateSDF(&vZ1, &m_vParms);

			// Transform the local normal.
			vSurfaceNormal.Normalize();
			vLocalNormal = m_GeomTransform.ApplyNorm(vSurfaceNormal);
			vLocalNormal.Normalize();

			// Return the base colour.
			vLocalColour = m_vBaseColour;

			return true;
		}
	}

	return false;
}
				
// Function to set the object function.
void QBRT::RM::QBRayMarchBase::SetObjectFunc(	std::function<double(qbVector3<double>*, qbVector3<double>*)> objectFunc)
{
	m_ObjectFunc = objectFunc;
	m_bHaveObjectFunc = true;
}
				
// Function to evaluate the Signed Distance Function (SDF) at the given coordinates.
double QBRT::RM::QBRayMarchBase::EvaluateSDF(	qbVector3<double>* vLocation,
												qbVector3<double>* vParms )
{
	return m_ObjectFunc(vLocation, vParms);
}
												
