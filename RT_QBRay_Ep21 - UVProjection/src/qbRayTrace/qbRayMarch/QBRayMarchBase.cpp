#include "QBRayMarchBase.hpp"

// Default constructor.
QBRT::RM::QBRayMarchBase::QBRayMarchBase()
{
	m_BoundingBox = std::make_shared<QBRT::QBBox>();

	// Define the tolerance.
	m_fEpsilon = 1e-3;

	// Define the maximum number of steps allowed.
	m_iMaxSteps = 100;
}
				
// Destructor.
QBRT::RM::QBRayMarchBase::~QBRayMarchBase()
{

}
				
// Override the function to test for intersections.
bool QBRT::RM::QBRayMarchBase::TestIntersection(	const QBRay& castRay,
													QBRT::DATA::HitData& sHitData)
{
	// Check if an object function has been defined.
	if (m_bHaveObjectFunc)
	{
		// Check if the object is visible.
		//if (!m_bIsVisible)
		//	return false;

		// Copy the ray and apply the backwards transform.
		QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

		// Test for intersection with the bounding box.
		if(m_BoundingBox->TestIntersectionFast(	bckRay))
		{
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
			sHitData.vPointOfIntersection = m_GeomTransform.Apply(vCurentLocation, QBRT::FWDTFORM);

			// Compute the local normal.
			qbVector3<double>	vSurfaceNormal;
			
			/*
			 Note the extra code here to compute an offset location from which
			to compute the normal. The reason to do this is that in some cases,
			especially with more complex distance functions, the point of intersection
			can be computed as being very slightly inside the surface. This would
			obviously result in a normal vector pointing in the wrong direction.
			By tracing back along the intersecting ray a short distance and then using
			that location instead, we can avoid this problem.
			*/

			// Determine an offset point.
			qbVector3<double> vNormalLocation = vCurentLocation - (vDir * 0.01);

			qbVector3<double>	vX1 = vNormalLocation - m_vXDisp;
			qbVector3<double>	vX2 = vNormalLocation + m_vXDisp;

			qbVector3<double>	vY1 = vNormalLocation - m_vYDisp;
			qbVector3<double>	vY2 = vNormalLocation + m_vYDisp;

			qbVector3<double>	vZ1 = vNormalLocation - m_vZDisp;
			qbVector3<double>	vZ2 = vNormalLocation + m_vZDisp;

			vSurfaceNormal.x = EvaluateSDF(&vX2, &m_vParms) - EvaluateSDF(&vX1, &m_vParms);
			vSurfaceNormal.y = EvaluateSDF(&vY2, &m_vParms) - EvaluateSDF(&vY1, &m_vParms);
			vSurfaceNormal.z = EvaluateSDF(&vZ2, &m_vParms) - EvaluateSDF(&vZ1, &m_vParms);

			// Transform the local normal.
			vSurfaceNormal.Normalize();
			sHitData.vNormalAtPointOfIntersection = m_GeomTransform.ApplyNorm(vSurfaceNormal);

			// Return the base colour.
			sHitData.vColourAtPointOfIntersection = m_vBaseColour;

			// Return the local point of intersection.
			sHitData.vLocalPointOfIntersection = vCurentLocation;

			// Compute UV.		
			ComputeUV(QBRT::uvSPHERE, vCurentLocation, sHitData.vUVCoords);

			// Return a pointer to this object.
			sHitData.pHitObject = this->shared_from_this();

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
												
