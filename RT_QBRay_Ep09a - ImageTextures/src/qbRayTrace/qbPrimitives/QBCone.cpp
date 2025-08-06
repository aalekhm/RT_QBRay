#include "QBCone.hpp"

// Default constructor.
QBRT::QBCone::QBCone()
{

}

// Override the destructor.
QBRT::QBCone::~QBCone()
{
}

// Override the function to test for intersections.
bool QBRT::QBCone::TestIntersection(	const QBRay& castRay,
										qbVector3<double>& vIntersectionPoint,
										qbVector3<double>& vLocalNormal,
										qbVector3<double>& vLocalColour)
{
	// Copy the ray and apply the backwards transform.
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

	// Copy the m_lab vector from bckRay and normalize it.
	qbVector3<double> v = bckRay.m_vDir;
	v.Normalize();

	// Get the start point of the line.
	qbVector3<double> p = bckRay.m_vPoint1;
	
	// Compute a, b and c.
	// a = Vx^2 + Vy^2 - Vz^2
	// b = 2(PxVx + PyVy - PzVz)
	// c = Px^2 + Py^2 - Pz^2
	double a = std::pow(v.x, 2) + std::pow(v.y, 2) - std::pow(v.z, 2);
	double b = 2 * ((p.x * v.x) + (p.y * v.y) - (p.z * v.z));
	double c = std::pow(p.x, 2) + std::pow(p.y, 2) - std::pow(p.z, 2);

	// Compute b^2 - 4ac.
	double fNumSQRT = sqrtf(std::pow(b, 2) - 4 * a * c);

	// Test for intersections.
	// First with the cylinder itself.
	std::array<qbVector3<double>, 3>	vPointsOfIntersection;
	std::array<double, 3>				t;
	
	bool bT1Valid, bT2Valid, bT3Valid;
	if (fNumSQRT > 0.0)
	{
		// There was an intersection.
		// Compute the values for t.
		t[0] = (-b + fNumSQRT) / (2 * a);
		t[1] = (-b - fNumSQRT) / (2 * a);

		// Compute the points of intersection.
		vPointsOfIntersection[0] = bckRay.m_vPoint1 + (v * t[0]);
		vPointsOfIntersection[1] = bckRay.m_vPoint1 + (v * t[1]);

		if(	t[0] > 0.0
			&&
			vPointsOfIntersection[0].z > 0.0
			&&
			vPointsOfIntersection[0].z < 1.0
		) {
			bT1Valid = true;
		}
		else
		{
			bT1Valid = false;
			t[0] = 100e6;
		}

		if(	t[1] > 0.0
			&&
			vPointsOfIntersection[1].z > 0.0
			&&
			vPointsOfIntersection[1].z < 1.0
		) {
			bT2Valid = true;
		}
		else
		{
			bT2Valid = false;
			t[1] = 100e6;
		}
	}
	else
	{
		bT1Valid = false;
		bT2Valid = false;
		t[0] = 100e6;
		t[1] = 100e6;
	}

	// And test the end cap.
	if (CloseEnough(v.z, 0.0))
	{
		bT3Valid = false;
		t[2] = 100e6;
	}
	else
	{
		// Compute the values of t.
		t[2] = (bckRay.m_vPoint1.z - 1.0) / -v.z;
		
		// Compute the points of intersection.
		vPointsOfIntersection[2] = bckRay.m_vPoint1 + (v * t[2]);

		// Check if these are valid.
		if(	t[2] > 0.0
			&&
			sqrtf(	std::pow(vPointsOfIntersection[2].x, 2.0)	// x^2 + y^2 < 1.0
					+ 
					std::pow(vPointsOfIntersection[2].y, 2.0)) 
				< 1.0
		) {
			bT3Valid = true;
		}
		else
		{
			bT3Valid = false;
			t[2] = 100e6;
		}
	}
	
	// If no valid intersections found, the we can stop.
	if (!bT1Valid && !bT2Valid && !bT3Valid)
		return false;
	
	// Check for the smallest valid value of t.
	uint32_t iMinIndex = 0;
	double fMinValue = 10e6;
	for (int i = 0; i < 3; ++i)
	{
		if (t[i] < fMinValue)
		{
			fMinValue = t[i];
			iMinIndex = i;
		}
	}

	// If minIndex is either 0 or 1, then we have a valid intersection with the cylinder itself.
	qbVector3<double>	vValidPointOfIntersection = vPointsOfIntersection[iMinIndex];
	if (iMinIndex < 2)
	{
		// Transform the intersection point back into world coordinates.
		vIntersectionPoint = m_GeomTransform.Apply(vValidPointOfIntersection, QBRT::FWDTFORM);

		// Compute the local normal.
		qbVector3<double>	vLocalOrigin(0.0, 0.0, 0.0);
		qbVector3<double>	vGlobalOrigin = m_GeomTransform.Apply(vLocalOrigin, QBRT::FWDTFORM);

		qbVector3<double>	vOrigNormal;
		qbVector3<double>	vNewNormal;
		vOrigNormal.x = vValidPointOfIntersection.x;
		vOrigNormal.y = vValidPointOfIntersection.y;
		vOrigNormal.z = -sqrtf(	std::pow(vValidPointOfIntersection.x, 2.0)	// -sqrtf(x^2 + y^2)
								+ 
								std::pow(vValidPointOfIntersection.y, 2.0));
		vNewNormal = m_GeomTransform.Apply(vOrigNormal, QBRT::FWDTFORM) - vGlobalOrigin;
		vNewNormal.Normalize();
		vLocalNormal = vNewNormal;

		// Return the base color.
		vLocalColour = m_vBaseColour;

		// Compute the (u,v) coordinates and store for possible later use.
		double x = vValidPointOfIntersection.x;
		double y = vValidPointOfIntersection.y;
		double z = vValidPointOfIntersection.z;
		double u = atan2(y, x) / M_PI;
		double v = (z * 2.0) + 1.0;

		m_vUVCoords.x = u;
		m_vUVCoords.y = v;

		return true;
	}
	else
	{
		// Otherwise check the end caps.
		if (!CloseEnough(v.z, 0.0))
		{
			// Check if we are inside the disk.
			if( sqrtf(	std::pow(vValidPointOfIntersection.x, 2.0)	// x^2 + y^2 < 1.0
						+ 
						std::pow(vValidPointOfIntersection.y, 2.0))
				< 1.0
			) {
				// Transform the intersection point back into world coordinates.
				vIntersectionPoint = m_GeomTransform.Apply(vValidPointOfIntersection, QBRT::FWDTFORM);

				qbVector3<double>	vLocalOrigin(0.0, 0.0, 0.0);
				qbVector3<double>	vGlobalOrigin = m_GeomTransform.Apply(vLocalOrigin, QBRT::FWDTFORM);

				qbVector3<double>	vNormal(0.0, 0.0, 1.0);
				vLocalNormal = m_GeomTransform.Apply(vNormal, QBRT::FWDTFORM) - vGlobalOrigin;
				vLocalNormal.Normalize();

				// Return the base color.
				vLocalColour = m_vBaseColour;

				// Compute and store (u,v) coordinates for possible later use.
				double x = vValidPointOfIntersection.x;
				double y = vValidPointOfIntersection.y;
				double z = vValidPointOfIntersection.z;
				m_vUVCoords.x = x;
				m_vUVCoords.y = y;

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
