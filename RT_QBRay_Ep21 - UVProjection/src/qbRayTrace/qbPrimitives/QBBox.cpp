#include "QBBox.hpp"
#include <array>
#include <cmath>

// The default constructor.
// Note that this will define a unit sphere at the origin.
QBRT::QBBox::QBBox()
{

}

// Override the destructor.
QBRT::QBBox::~QBBox()
{

}

// Override the function to test for intersections.
bool QBRT::QBBox::TestIntersection(	const QBRay& castRay,
									QBRT::DATA::HitData& sHitData)
{
	//if (!m_bIsVisible)
	//	return false;
	
	// Copy the ray and apply the backwards transform.
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);
	
	// For 6 faces. t @ PointOfIntersection & UnitVetors
	std::array<double, 6> t;
	std::array<double, 6> u;
	std::array<double, 6> v;	
	
	// Extract values of a.
	double ax = bckRay.m_vPoint1.x;
	double ay = bckRay.m_vPoint1.y;
	double az = bckRay.m_vPoint1.z;

	// Extract the value of k.
	qbVector3<double> k = bckRay.m_vDir;
	double kx = k.x;
	double ky = k.y;
	double kz = k.z;

	// Test for intersections with each plane (side of the box).
	// Top and bottom.
	if (!CloseEnough(kz, 0.0))
	{
		t[0] = (az - 1.0) / -kz;
		t[1] = (az + 1.0) / -kz;
		u[0] = ax + kx * t[0];
		v[0] = ay + ky * t[0];
		u[1] = ax + kx * t[1];
		v[1] = ay + ky * t[1];
	}
	else
	{
		t[0] = 100e6;
		t[1] = 100e6;
		u[0] = 0.0;
		v[0] = 0.0;
		u[1] = 0.0;
		v[1] = 0.0;
	}

		// Left and right.
	if (!CloseEnough(kx, 0.0))
	{
		t[2] = (ax + 1.0) / -kx;
		t[3] = (ax - 1.0) / -kx;
		u[2] = az + kz * t[2];
		v[2] = ay + ky * t[2];
		u[3] = az + kz * t[3];
		v[3] = ay + ky * t[3];
	}
	else
	{
		t[2] = 100e6;
		t[3] = 100e6;
		u[2] = 0.0;
		v[2] = 0.0;
		u[3] = 0.0;
		v[3] = 0.0;		
	}
	
	// Front and back.
	if (!CloseEnough(ky, 0.0))
	{
		t[4] = (ay + 1.0) / -ky;
		t[5] = (ay - 1.0) / -ky;
		u[4] = ax + kx * t[4];
		v[4] = az + kz * t[4];
		u[5] = ax + kx * t[5];
		v[5] = az + kz * t[5];
	}
	else
	{
		t[4] = 100e6;
		t[5] = 100e6;
		u[4] = 0.0;
		v[4] = 0.0;
		u[5] = 0.0;
		v[5] = 0.0;		
	}

	// Find the index of the smallest non-negative value of t.
	double fFinalU = 0.0;
	double fFinalV = 0.0;
	double fFinalT = 100e6;
	int finalIndex = 0;
	bool bValidIntersection = false;
	for (int i=0; i<6; ++i)
	{
		if (	(t[i] < fFinalT)
				&& 
				(t[i] > 0.0) 
				&& 
				(abs(u[i]) <= 1.0) 
				&& 
				(abs(v[i]) <= 1.0)
		) {
			fFinalT = t[i];
			finalIndex = i;
			fFinalU = u[i];
			fFinalV = v[i];
			bValidIntersection = true;
		}
	}

	if (bValidIntersection)
	{
		// Compute the point of intersection.
		qbVector3<double> vPointOfIntersection = bckRay.m_vPoint1 + fFinalT * k;
	
		// Compute the normal vector
		qbVector3<double> normalVector	{3};
		switch (finalIndex)
		{
			case 0:
				normalVector = std::vector<double>{0.0, 0.0, 1.0}; // Down.
				break;
				
			case 1:
				normalVector = std::vector<double>{0.0, 0.0, -1.0}; // Up.
				break;
				
			case 2:
				normalVector = std::vector<double>{-1.0, 0.0, 0.0}; // Left.
				break;
				
			case 3:
				normalVector = std::vector<double>{1.0, 0.0, 0.0}; // Right.
				break;
				
			case 4:
				normalVector = std::vector<double>{0.0, -1.0, 0.0}; // Backwards (towards the camera).
				break;
				
			case 5:
				normalVector = std::vector<double>{0.0, 1.0, 0.0}; // Forwards (away from the camera).
				break;
				
		}
		
		// Transform the intersection point back into world coordinates.
		sHitData.vPointOfIntersection = m_GeomTransform.Apply(vPointOfIntersection, QBRT::FWDTFORM);
			
		// Transform the normal vector.
		sHitData.vNormalAtPointOfIntersection = m_GeomTransform.ApplyNorm(normalVector);
		sHitData.vNormalAtPointOfIntersection.Normalize();
			
		// Return the base color.
		sHitData.vColourAtPointOfIntersection = m_vBaseColour;
		
		// Return the local point of intersection.
		sHitData.vLocalPointOfIntersection = vPointOfIntersection;

		// Store the (u,v) coordinates for possible later use.
		ComputeUV(QBRT::uvBOX, vPointOfIntersection, sHitData.vUVCoords);

		// Return a reference to this object.
		sHitData.pHitObject = this->shared_from_this();

		return true;
	}
	else
	{
		return false;
	}
}

bool QBRT::QBBox::TestIntersectionFast(const QBRT::QBRay& castRay)
{
	//if (!m_isVisible)
	//	return false;

	// Copy the ray and apply the backwards transform.
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);

	// For 6 faces. t @ PointOfIntersection & UnitVetors
	std::array<double, 6> t{ 100e6, 100e6, 100e6, 100e6, 100e6, 100e6 };
	std::array<double, 6> u{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	std::array<double, 6> v{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

	// Extract values of a.
	double ax = bckRay.m_vPoint1.x;
	double ay = bckRay.m_vPoint1.y;
	double az = bckRay.m_vPoint1.z;

	// Extract the value of k.
	qbVector3<double> k = bckRay.m_vDir;
	double kx = k.x;
	double ky = k.y;
	double kz = k.z;

	// Test for intersections with each plane (side of the box).
	// Top and bottom.
	if (!CloseEnough(kz, 0.0))
	{
		t[0] = (az - 1.0) / -kz;
		t[1] = (az + 1.0) / -kz;
		u[0] = ax + kx * t[0];
		v[0] = ay + ky * t[0];
		u[1] = ax + kx * t[1];
		v[1] = ay + ky * t[1];
	}

	// Left and right.
	if (!CloseEnough(kx, 0.0))
	{
		t[2] = (ax + 1.0) / -kx;
		t[3] = (ax - 1.0) / -kx;
		u[2] = az + kz * t[2];
		v[2] = ay + ky * t[2];
		u[3] = az + kz * t[3];
		v[3] = ay + ky * t[3];
	}

	// Front and back.
	if (!CloseEnough(ky, 0.0))
	{
		t[4] = (ay + 1.0) / -ky;
		t[5] = (ay - 1.0) / -ky;
		u[4] = ax + kx * t[4];
		v[4] = az + kz * t[4];
		u[5] = ax + kx * t[5];
		v[5] = az + kz * t[5];
	}

	// Find the index of the smallest non-negative value of t.
	/* Note that in the case of a bounding box, we are only interested
		in whether or not there was a valid intersection, we don't need
		to know which face of the box was actually involved. */
	bool validIntersection = false;
	int i = 0;
	while ((i < 6) && (!validIntersection))
	{
		if ((t[i] < 100e6) && (t[i] > 0.0) && (abs(u[i]) <= 1.0) && (abs(v[i]) <= 1.0))
		{
			validIntersection = true;
		}

		i++;
	}

	return validIntersection;
}

