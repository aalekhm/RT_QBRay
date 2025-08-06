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
void QBRT::QBObjectBase::ComputeUV(const qbVector3<double>& vLocalPOI, qbVector2<double>& vUVCoords)
{
	switch (m_iUVMapType)
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

			//double x = vLocalPOI.x;
			//double y = vLocalPOI.y;
			//double z = vLocalPOI.z;
			//double u = atan2(sqrtf(std::pow(x, 2.0) + std::pow(y, 2.0)), z);
			//double v = atan2(y, x);
			//
			//u /= M_PI;
			//v /= M_PI;
			
			double x = vLocalPOI.x;
			double y = vLocalPOI.y;
			double z = vLocalPOI.z;
			double u = atan2(y, x) / M_PI;
			double v = 2.0 * (atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z) / M_PI) - 1.0;

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

// Function to compute the extents of the object.
void QBRT::QBObjectBase::GetExtents(	qbVector2<double>& xLim, 
										qbVector2<double>& yLim, 
										qbVector2<double>& zLim)
{
	// Construct an array of corner points for a unit cube.
	std::vector<qbVector3<double>> unitCubeCornerPoints = ConstructCube(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	// Form the combined object and bounding box transform matrix.
	QBRT::QBGeometricTransform combinedTransform = m_GeomTransform * m_GeomTransformBoundingBox;
	
	// Apply the transforms to the unit cube corner points and compute limits.
	double minX = 1e6;
	double minY = 1e6;
	double minZ = 1e6;
	double maxX = -1e6;
	double maxY = -1e6;
	double maxZ = -1e6;
	for (int i = 0; i < 8; ++i)
	{
		// Apply the combined transform to each corner of the cube.
		unitCubeCornerPoints.at(i) = combinedTransform.Apply(unitCubeCornerPoints.at(i), QBRT::FWDTFORM);
		
		// Recalculate the bounds.
		if (unitCubeCornerPoints.at(i).GetElement(0) < minX)	minX = unitCubeCornerPoints.at(i).GetElement(0);
		if (unitCubeCornerPoints.at(i).GetElement(0) > maxX)	maxX = unitCubeCornerPoints.at(i).GetElement(0);
			
		if (unitCubeCornerPoints.at(i).GetElement(1) < minY)	minY = unitCubeCornerPoints.at(i).GetElement(1);
		if (unitCubeCornerPoints.at(i).GetElement(1) > maxY)	maxY = unitCubeCornerPoints.at(i).GetElement(1);
			
		if (unitCubeCornerPoints.at(i).GetElement(2) < minZ)	minZ = unitCubeCornerPoints.at(i).GetElement(2);
		if (unitCubeCornerPoints.at(i).GetElement(2) > maxZ)	maxZ = unitCubeCornerPoints.at(i).GetElement(2);					
	}
	
	// Return the limits.
	xLim.min = minX;
	xLim.max = maxX;
	yLim.min = minY;
	yLim.max = maxY;
	zLim.min = minZ;
	zLim.max = maxZ;
}

// Function to compute the extents of the object, accepting an additional transform matrix as input.
void QBRT::QBObjectBase::GetExtents(	const QBRT::QBGeometricTransform& parentGeometricTransform, 
										qbVector2<double>& xLim, 
										qbVector2<double>& yLim, 
										qbVector2<double>& zLim)
{
	// Construct an array of corner points for a unit cube.
	std::vector<qbVector3<double>> unitCubeCornerPoints = ConstructCube(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	
	// Form the combined object and bounding box transform matrix.
	QBRT::QBGeometricTransform combinedTransform = parentGeometricTransform * m_GeomTransform * m_GeomTransformBoundingBox;
	
	// Apply the transforms to the unit cube corner points and compute limits.
	double minX = 1e6;
	double minY = 1e6;
	double minZ = 1e6;
	double maxX = -1e6;
	double maxY = -1e6;
	double maxZ = -1e6;
	for (int i = 0; i < 8; ++i)
	{
		unitCubeCornerPoints.at(i) = combinedTransform.Apply(unitCubeCornerPoints.at(i), QBRT::FWDTFORM);
		
		if (unitCubeCornerPoints.at(i).GetElement(0) < minX)	minX = unitCubeCornerPoints.at(i).GetElement(0);
		if (unitCubeCornerPoints.at(i).GetElement(0) > maxX)	maxX = unitCubeCornerPoints.at(i).GetElement(0);
			
		if (unitCubeCornerPoints.at(i).GetElement(1) < minY)	minY = unitCubeCornerPoints.at(i).GetElement(1);
		if (unitCubeCornerPoints.at(i).GetElement(1) > maxY)	maxY = unitCubeCornerPoints.at(i).GetElement(1);
			
		if (unitCubeCornerPoints.at(i).GetElement(2) < minZ)	minZ = unitCubeCornerPoints.at(i).GetElement(2);
		if (unitCubeCornerPoints.at(i).GetElement(2) > maxZ)	maxZ = unitCubeCornerPoints.at(i).GetElement(2);					
	}
	
	// Return the limits.
	xLim.min = minX;
	xLim.max = maxX;
	yLim.min = minY;
	yLim.max = maxY;
	zLim.min = minZ;
	zLim.max = maxZ;
}

// Function to construct a unit cube.
std::vector<qbVector3<double>> QBRT::QBObjectBase::ConstructCube(	double xMin, 
																	double xMax, 
																	double yMin, 
																	double yMax, 
																	double zMin, 
																	double zMax)
{
	// Construct an array of corner points for a unit cube.
	std::vector<qbVector3<double>> cornerPoints (8);
	cornerPoints.at(0) = std::vector<double> {xMin - m_fBoundingBoxPadding, yMin - m_fBoundingBoxPadding, zMin - m_fBoundingBoxPadding};
	cornerPoints.at(1) = std::vector<double> {xMin - m_fBoundingBoxPadding, yMin - m_fBoundingBoxPadding, zMax + m_fBoundingBoxPadding};
	cornerPoints.at(2) = std::vector<double> {xMax + m_fBoundingBoxPadding, yMin - m_fBoundingBoxPadding, zMax + m_fBoundingBoxPadding};
	cornerPoints.at(3) = std::vector<double> {xMax + m_fBoundingBoxPadding, yMin - m_fBoundingBoxPadding, zMin - m_fBoundingBoxPadding};
	cornerPoints.at(4) = std::vector<double> {xMin - m_fBoundingBoxPadding, yMax + m_fBoundingBoxPadding, zMin - m_fBoundingBoxPadding};
	cornerPoints.at(5) = std::vector<double> {xMin - m_fBoundingBoxPadding, yMax + m_fBoundingBoxPadding, zMax - m_fBoundingBoxPadding};
	cornerPoints.at(6) = std::vector<double> {xMax + m_fBoundingBoxPadding, yMax + m_fBoundingBoxPadding, zMax + m_fBoundingBoxPadding};
	cornerPoints.at(7) = std::vector<double> {xMax + m_fBoundingBoxPadding, yMax + m_fBoundingBoxPadding, zMin - m_fBoundingBoxPadding};

	return cornerPoints;
}