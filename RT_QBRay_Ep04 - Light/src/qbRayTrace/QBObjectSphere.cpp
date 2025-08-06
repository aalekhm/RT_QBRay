#include "QBObjectSphere.hpp"

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
	// Compute the values of a, b and c.
	qbVector3<double> vRayDir = castRay.m_vDir;
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
	double a = 1.0; 

	// Calculate b = 2(p1.v)
	double b = 2.0 * qbVector3<double>::dot(castRay.m_vPoint1, vRayDir);

	// Calculate c = (p1.p1) - r2
	double c = qbVector3<double>::dot(castRay.m_vPoint1, castRay.m_vPoint1) - 1.0;

	// Test whether we actually have an intersection.
	double fIntersectionTest = b * b - 4.0 * a * c;

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
				vIntersectionPoint = castRay.m_vPoint1 + (vRayDir * t1);
			}
			else
			{
				vIntersectionPoint = castRay.m_vPoint1 + (vRayDir * t2);
			}

			// Compute the local normal. (easy for a sphere at origin)
			// Since a normal at the intersection point is a vector 
			// from the center of the sphere(0.0, 0.0, 0.0) to the 
			// intersection point.
			vLocalNormal = vIntersectionPoint;
			vLocalNormal.Normalize();
		}

		return true;
	}
	else
	{
		return false;
	}
}