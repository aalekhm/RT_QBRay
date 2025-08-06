#include "QBObjectBase.hpp"
#include <math.h>

#define EPSILON 1e-6f

// Default constructor.
QBRT::QBObjectBase::QBObjectBase()
{

}

// The destructor.
QBRT::QBObjectBase::~QBObjectBase()
{

}

// Function to test for intersections.
bool QBRT::QBObjectBase::TestIntersection(	const QBRay& castRay, 
											QBRT::DATA::HitData& sHitData)
{
	return false;
}

void QBRT::QBObjectBase::SetTransform(const QBRT::QBGeometricTransform& geomTransform)
{
	m_GeomTransform = geomTransform;
}

// Function to test whether two floating-point numbers are close to being equal.
bool QBRT::QBObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}

// Function to assign a material.
bool QBRT::QBObjectBase::AssignMaterial(const std::shared_ptr<QBRT::QBMaterialBase>& pMaterial)
{
	m_pMaterial = pMaterial;
	m_bHasMaterial = true;

	return m_bHasMaterial;
}

// Function to compute UV space.
void QBRT::QBObjectBase::ComputeUV(const uint32_t iUVMapType, const qbVector3<double>& vLocalPOI, qbVector2<double>& vUVCoords)
{
	switch (iUVMapType)
	{
		case QBRT::uvSPHERE:
		{
			// Sphere:
			//     		  -1     x^2 + y^2
			//		u = tan * (-----------)
			//		                z
			//	          -1	y
			//		v = tan * (---)
			//		            x
			//
			double x = vLocalPOI.x;
			double y = vLocalPOI.y;
			double z = vLocalPOI.z;
			double u = atan2(sqrtf(std::pow(x, 2.0) + std::pow(y, 2.0)), z);
			double v = atan2(y, x);
			
			u /= M_PI;
			v /= M_PI;
			
			//double u = atan2(y, x) / M_PI;
			//double v = 2.0 * (atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z) / M_PI) - 1.0;

			vUVCoords.x = u;
			vUVCoords.y = v;

			break;
		}
		case QBRT::uvPLANE:
		{
			// Plane projection.
			vUVCoords.x = vLocalPOI.x;
			vUVCoords.y = vLocalPOI.y;
			break;
		}
		case QBRT::uvCYLINDER:
		{
			// Cylinder projection.
			double x = vLocalPOI.x;
			double y = vLocalPOI.y;
			double z = vLocalPOI.z;				
			double u = atan2(y, x) / M_PI;
			double v = -z;
			vUVCoords.x = u;
			vUVCoords.y = v;
			break;
		}
		case QBRT::uvCONE:
		{
			double x = vLocalPOI.x;
			double y = vLocalPOI.y;
			double z = vLocalPOI.z;
			double u = atan2(y, x) / M_PI;
			double v = (z * 2.0) + 1.0;

			vUVCoords.x = u;
			vUVCoords.y = v;
		}
		break;
		case QBRT::uvBOX:
		{
			// Box projection.
			double x = vLocalPOI.x;
			double y = vLocalPOI.y;
			double z = vLocalPOI.z;
			double u = 0.0;
			double v = 0.0;
				
			if (CloseEnough(x, -1.0))
			{
				// Left face.
				u = -(y * 0.25) - 0.75;
				v = -z * 0.25;
					
			}
			else if (CloseEnough(x, 1.0))
			{
				// Right face.
				u = (y * 0.25) + 0.25;
				v = -z * 0.25;
					
			}
			else if (CloseEnough(y, -1.0))
			{
				// Front face.
				u = (x * 0.25) - 0.25;
				v = (-z * 0.25) - 0.5;
					
			}
			else if (CloseEnough(y, 1.0))
			{
				// Back face.
				u = -(x * 0.25) - 0.25;;
				v = (-z * 0.25) + 0.5;
					
			}
			else if (CloseEnough(z, -1.0))
			{
				// Top face.
				u = (x * 0.25) + 0.75;
				v = y * 0.25;
					
			}
			else if (CloseEnough(z, 1.0))
			{
				// Bottom face.
				u = (x * 0.25) - 0.25;
				v = y * 0.25;
					
			}
			else
			{
				// The object isn't a box...
			}
				
			vUVCoords.x = u;
			vUVCoords.y = v;
			break;
		}
	}
}