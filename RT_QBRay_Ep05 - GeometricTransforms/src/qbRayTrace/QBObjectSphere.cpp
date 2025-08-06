#include "QBObjectSphere.hpp"
#include <math.h>

//The default constructor.
QBRT::QBObjectSphere::QBObjectSphere()
{

}

// Override the destructor.
QBRT::QBObjectSphere::~QBObjectSphere()
{

}

// Function to test for intersections.
bool QBRT::QBObjectSphere::TestIntersection(	const QBRay& castRay, 
												qbVector3<double>& vIntersectionPoint, 
												qbVector3<double>& vLocalNormal, 
												qbVector3<double>& vLocalColour)
{
	// Copy the ray and apply the backwards transform.
	// "castRay" is in the world coordinate system.
	// Before doing any calculations, the 2 ojects need to be in the same coordinate system.
	// We need to bring it to the local coordinate system of the "Sphere".
	// To bring it to 'Sphere's" local coordinate, apply "Backward Transform"
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

	// Compute the values of a, b and c.
	qbVector3<double> vRayDir = bckRay.m_vDir;
	vRayDir.Normalize();

	// Solving for:
	// t2(v.v) + 2t(p1.v) + (p1.p1) - r2 = 0 ==> at2 + bt + c = 0             
	// a = (v.v)
	// b = 2(p1.v)
	// c = (p1.p1) - r2
	/* Note that a is equal to the squared magnitude of the
	direction of the cast ray. As this will be a unit vector,
	we can conclude that the value of 'a' will always be 1. 
	Calculate a = (v.v)	*/
	double a = qbVector3<double>::dot(vRayDir, vRayDir);

	// Calculate b = 2(p1.v)
	double b = 2.0 * qbVector3<double>::dot(bckRay.m_vPoint1, vRayDir);

	// Calculate c = (p1.p1) - r2
	double c = qbVector3<double>::dot(bckRay.m_vPoint1, bckRay.m_vPoint1) - 1.0;

	// Test whether we actually have an intersection.
	double fIntersectionTest = b * b - 4.0 * a * c;
	qbVector3<double> vLocalIntersectionPoint;

	// There is an intersection if the value is < 0.
	// If intersection happens then, b2 - 4ac > 0.
	if (fIntersectionTest > 0.0)
	{
		double fNumSQRT = sqrtf(static_cast<float>(fIntersectionTest));
		double t1 = (-b + fNumSQRT) / 2.0;
		double t2 = (-b - fNumSQRT) / 2.0;

		/* If either t1 or t2 are negative, then at least part of the object is
		behind the camera and so we will ignore it. */
		if ((t1 < 0.0) || (t2 < 0.0))
		{
			return false;
		}
		else
		{
			// Determine which point of intersection was closest to the camera.
			if (t1 < t2)
			{
				vLocalIntersectionPoint = bckRay.m_vPoint1 + (vRayDir * t1);
			}
			else
			{
				vLocalIntersectionPoint = bckRay.m_vPoint1 + (vRayDir * t2);
			}

			// Since the intersection point is in local coordinate system,
			// Bring it back to world coordinate system by applying FWD transform.
			// Transform the intersection point back into world coordinates.
			vIntersectionPoint = m_GeomTransform.Apply(vLocalIntersectionPoint, QBRT::FWDTFORM);

			// Compute the local normal. (easy for a sphere at origin)
			// Since a normal at the intersection point is a vector 
			// from the center of the sphere(0.0, 0.0, 0.0) to the intersection point.
			// Apply FWD transform to the local origin so that the object's origin is 
			// transformed to world coordinate system.
			qbVector3<double> vObjOrigin(0.0, 0.0, 0.0);
			qbVector3<double> vObjNewOrigin = m_GeomTransform.Apply(vObjOrigin, QBRT::FWDTFORM);

			// Calculate the normal in the world coordinate system.
			vLocalNormal = vIntersectionPoint - vObjNewOrigin;
			vLocalNormal.Normalize();

			// Return the base color.
			vLocalColour = m_vBaseColour;
		}

		return true;
	}
	else
	{
		return false;
	}
}