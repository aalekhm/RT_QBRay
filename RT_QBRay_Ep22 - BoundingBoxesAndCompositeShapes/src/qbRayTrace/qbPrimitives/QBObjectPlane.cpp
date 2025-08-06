#include "QBObjectPlane.hpp"
#include "qbRayTrace/QBScene.hpp"
#include <cmath>

QBRT::QBObjectPlane::QBObjectPlane()
{
	m_iUVMapType = QBRT::uvPLANE;

	// Construct the default bounding box.
	m_GeomTransformBoundingBox.SetTransform(qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
											qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
											qbVector3<double>{std::vector<double>{1.0, 1.0, 0.01}});
}

// Override the destructor.
QBRT::QBObjectPlane::~QBObjectPlane()
{

}

// The function to test for intersections.
bool QBRT::QBObjectPlane::TestIntersection(	const QBRay& castRay,
											QBRT::DATA::HitData& sHitData)
{
	// At the point of intersection,
	// Line EQ  = Plane EQ
	//      ->            ->     ->
	// A + t.K  = P0 + P01.U + P1.V
	// Solving for t:
	// t = Az / -Kz
	// ->
	//  U = Ax + Kx.t
	// ->
	//  V = Ay + Ky.t
	
	// Copy the ray and apply the backwards transform.
	// "castRay" is in the world coordinate system.
	// Before doing any calculations, the 2 ojects need to be in the same coordinate system.
	// We need to bring it to the local coordinate system of the "Sphere".
	// To bring it to 'Sphere's" local coordinate, apply "Backward Transform"
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

	// Copy the direction vector from bckRay and normalize it.
	qbVector3<double> K = bckRay.m_vDir;
	K.Normalize();

	// Check if there is an intersection, ie. if the castRay is not parallel
	// to the plane.
	if (CloseEnough(K.z, 0.0) == false)
	{
		// There is an intersection.
		double t = bckRay.m_vPoint1.z / -K.z;
		
		// If t is negative, then the intersection point must be behind
		// the camera and we can ignore it.
		if (t > 0.0)
		{
			// Compute the values for U and V.
			double U = bckRay.m_vPoint1.x + (K.x * t);
			double V = bckRay.m_vPoint1.y + (K.y * t);

			// If the magnitude of both u and v is less than or equal to one
			// then we must be in the plane.
			if ((abs(U) < 1.0) && (abs(V) < 1.0))
			{
				// Compute the point of intersection.
				qbVector3<double> vPointOfIntersection = bckRay.m_vPoint1 + (t * K); // => Line EQ

				// Transform the intersection point back into world coordinates.
				sHitData.vPointOfIntersection = m_GeomTransform.Apply(vPointOfIntersection, QBRT::FWDTFORM);

				// Compute the world origin.
				qbVector3<double> vObjOrigin(0.0, 0.0, 0.0);
				qbVector3<double> vObjNewOrigin = m_GeomTransform.Apply(vObjOrigin, QBRT::FWDTFORM);

				// Compute the local normal.
				//qbVector3<double> vNormalVector(0.0, 0.0, -1.0);
				//vLocalNormal = m_GeomTransform.Apply(vNormalVector, QBRT::FWDTFORM) - vObjNewOrigin;
				//vLocalNormal.Normalize();
				qbVector3<double> vNormalVector{ 0.0, 0.0, -1.0 };
				sHitData.vNormalAtPointOfIntersection = m_GeomTransform.ApplyNorm(vNormalVector);
				sHitData.vNormalAtPointOfIntersection.Normalize();

				// Return the base color.
				sHitData.vColourAtPointOfIntersection = m_vBaseColour;

				// Return the local point of intersection.
				sHitData.vLocalPointOfIntersection = vPointOfIntersection;

				// Store the (u,v) coordinates for possible later use.
				ComputeUV(vPointOfIntersection, sHitData.vUVCoords);

				// Return a reference to this object.
				sHitData.pHitObject = this->shared_from_this();

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return false;
}