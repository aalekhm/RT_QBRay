#include "QBCompositeBase.hpp"

// Constructor.
QBRT::SHAPES::QBCompositeBase::QBCompositeBase()
{
	// Set default initial values for the limits.
	m_xLim = std::vector<double>{1e6, -1e6};
	m_yLim = std::vector<double>{1e6, -1e6};
	m_zLim = std::vector<double>{1e6, -1e6};
}

// Destructor.
QBRT::SHAPES::QBCompositeBase::~QBCompositeBase()
{

}

// Function to add a sub-shape.
void QBRT::SHAPES::QBCompositeBase::AddSubShape(std::shared_ptr<QBRT::QBObjectBase> subShape)
{
	// Modify the extents of this shape to accomodate the new sub-shape.
	qbVector2<double> xLim;
	qbVector2<double> yLim;
	qbVector2<double> zLim;

	subShape->GetExtents(xLim, yLim, zLim);

	if (xLim.min < m_xLim.min)	m_xLim.min = xLim.min;
	if (xLim.max > m_xLim.max)	m_xLim.max = xLim.max;
		
	if (yLim.min < m_yLim.min)	m_yLim.min = yLim.min;
	if (yLim.max > m_yLim.max)	m_yLim.max = yLim.max;
		
	if (zLim.min < m_zLim.min)	m_zLim.min = zLim.min;
	if (zLim.max > m_zLim.max)	m_zLim.max = zLim.max;
		
	// Modify the composite shape bounding box to fit the new extents.
	// Determine the size;
	double xSize = m_xLim.max - m_xLim.min;
	double ySize = m_yLim.max - m_yLim.min;
	double zSize = m_zLim.max - m_zLim.min;
	
	// Determine centre points.
	double xCentre = m_xLim.min + (xSize / 2.0);
	double yCentre = m_yLim.min + (ySize / 2.0);
	double zCentre = m_zLim.min + (zSize / 2.0);
	
	// Update the transform matrix.
	m_GeomTransformBoundingBox.SetTransform(qbVector3<double>(xCentre, yCentre, zCentre),
											qbVector3<double>(0.0, 0.0, 0.0),
											qbVector3<double>(xSize/2.0, ySize/2.0, zSize/2.0));
																				
	// And modify the bounding box.
	m_BoundingBox.SetTransform(m_GeomTransformBoundingBox);

	// Add the sub-shape to the list of sub-shapes.
	m_vShapeList.push_back(subShape);
}

// Function to update the bounds.
void QBRT::SHAPES::QBCompositeBase::UpdateBounds()
{
	// Set default initial values for the limits.
	m_xLim = std::vector<double>{1e6, -1e6};
	m_yLim = std::vector<double>{1e6, -1e6};
	m_zLim = std::vector<double>{1e6, -1e6};
	
	qbVector2<double> xLim;
	qbVector2<double> yLim;
	qbVector2<double> zLim;
	for (auto shape : m_vShapeList)
	{
		shape->GetExtents(xLim, yLim, zLim);

		if (xLim.min < m_xLim.min)	m_xLim.min = xLim.min;
		if (xLim.max > m_xLim.max)	m_xLim.max = xLim.max;

		if (yLim.min < m_yLim.min)	m_yLim.min = yLim.min;
		if (yLim.max > m_yLim.max)	m_yLim.max = yLim.max;

		if (zLim.min < m_zLim.min)	m_zLim.min = zLim.min;
		if (zLim.max > m_zLim.max)	m_zLim.max = zLim.max;
	}
	
	// Modify the composite shape bounding box to fit the new extents.
	// Determine the size;
	double xSize = m_xLim.max - m_xLim.min;
	double ySize = m_yLim.max - m_yLim.min;
	double zSize = m_zLim.max - m_zLim.min;

	// Determine centre points.
	double xCentre = m_xLim.min + (xSize / 2.0);
	double yCentre = m_yLim.min + (ySize / 2.0);
	double zCentre = m_zLim.min + (zSize / 2.0);

	// Update the transform matrix.
	m_GeomTransformBoundingBox.SetTransform(qbVector3<double>(xCentre, yCentre, zCentre),
											qbVector3<double>(0.0, 0.0, 0.0),
											qbVector3<double>(xSize/2.0, ySize/2.0, zSize/2.0));
																				
	// And modify the bounding box.
	m_BoundingBox.SetTransform(m_GeomTransformBoundingBox);
}

// Override the function to return the extents.
void QBRT::SHAPES::QBCompositeBase::GetExtents(qbVector2<double> &xLim, qbVector2<double> &yLim, qbVector2<double> &zLim)
{
	// Construct corners of a cube based on the current limits.
	std::vector<qbVector3<double>> cornerPoints = ConstructCube(m_xLim.min, m_xLim.max, 
																m_yLim.min, m_yLim.max, 
																m_zLim.min, m_zLim.max);
	
	// Apply the transforms to the unit cube corner points and compute limits.
	double minX = 1e6;
	double minY = 1e6;
	double minZ = 1e6;
	double maxX = -1e6;
	double maxY = -1e6;
	double maxZ = -1e6;

	for (int i = 0; i < 8; ++i)
	{
		cornerPoints.at(i) = m_GeomTransform.Apply(cornerPoints.at(i), QBRT::FWDTFORM);
		
		if (cornerPoints.at(i).GetElement(0) < minX)	minX = cornerPoints.at(i).x;
		if (cornerPoints.at(i).GetElement(0) > maxX)	maxX = cornerPoints.at(i).x;
			
		if (cornerPoints.at(i).GetElement(1) < minY)	minY = cornerPoints.at(i).y;
		if (cornerPoints.at(i).GetElement(1) > maxY)	maxY = cornerPoints.at(i).y;
			
		if (cornerPoints.at(i).GetElement(2) < minZ)	minZ = cornerPoints.at(i).z;
		if (cornerPoints.at(i).GetElement(2) > maxZ)	maxZ = cornerPoints.at(i).z;					
	}
	
	// Return the limits.
	xLim.min = minX;
	xLim.max = maxX;
	yLim.min = minY;
	yLim.max = maxY;
	zLim.min = minZ;
	zLim.max = maxZ;
}

// Test for intersections.
bool QBRT::SHAPES::QBCompositeBase::TestIntersection(	const QBRT::QBRay& castRay, 
														QBRT::DATA::HitData& hitData)
{
	// Check if the object is visible.
	//if (!m_isVisible)
	//	return false;
		
	// Copy the ray and apply the backwards transform.
	QBRT::QBRay bckRay = m_GeomTransform.Apply(castRay, QBRT::BCKTFORM);
	
	// Check for intersection with the bounding box.
	if (	!m_bUseBoundingBox 
			|| 
			m_BoundingBox.TestIntersectionFast(bckRay)
	) {
		// We intersected with the bounding box, so check everything else.
		qbVector3<double> vWorldIntPoint;
		double currentDist = 100e6;
		QBRT::DATA::HitData tempHitData;

		int validShapeIndex = TestIntersections(castRay, 
												bckRay, 
												vWorldIntPoint, 
												currentDist, 
												tempHitData);
		if (validShapeIndex > -1)
		{
			// An intersection with an internal sub-shape.
			qbVector3<double> newNormal = m_GeomTransform.ApplyNorm(tempHitData.vNormalAtPointOfIntersection);
			newNormal.Normalize();

			tempHitData.pHitObject->ComputeUV(tempHitData.vLocalPointOfIntersection, hitData.vUVCoords);
			//m_uvCoords = hitData.uvCoords;
			
			// Return these values.
			hitData.vPointOfIntersection			= vWorldIntPoint;
			hitData.vNormalAtPointOfIntersection	= newNormal;
			hitData.vColourAtPointOfIntersection	= tempHitData.vColourAtPointOfIntersection;
			hitData.vLocalPointOfIntersection		= tempHitData.vLocalPointOfIntersection;
			hitData.pHitObject						= tempHitData.pHitObject;
			
			return true;
		}
		else
		{
			// No intersections with internal sub-shapes.
			return false;
		}
	}
	else
	{
		// No intersection with the bounding box.
		return false;
	}
	
	return false;
}

// Test for intersections with the sub-object list.
int QBRT::SHAPES::QBCompositeBase::TestIntersections(	const QBRT::QBRay& castRay,
														const QBRT::QBRay& bckRay,
														qbVector3<double>& vWorldIntersectionPoint,
														double& fCurrentDist,
														QBRT::DATA::HitData& hitData)
{
	// Test for intersections with the sub-shapes.
	int numShapes = m_vShapeList.size();
	int iValidShapeIndex = -1;
	QBRT::DATA::HitData sHitData;

	for (int i = 0; i < numShapes; ++i)
	{
		//if (m_vShapeList.at(i) -> m_isVisible)
		{
			bool bShapeTest = m_vShapeList[i]->TestIntersection(bckRay, sHitData);
			if (bShapeTest)
			{
				// Transform the intersection point back into world coordinates.
				qbVector3<double> vPointOfIntersection = m_GeomTransform.Apply(sHitData.vPointOfIntersection, QBRT::FWDTFORM);
				
				// Compute the distance.
				double fDist = (vPointOfIntersection - castRay.m_vPoint1).norm();
				
				// If closest, then this is the shape to use.
				if (fDist < fCurrentDist)
				{
					fCurrentDist = fDist;
					iValidShapeIndex = i;
					vWorldIntersectionPoint = vPointOfIntersection;
					hitData = sHitData;
				}
			}
		}
	}
	
	return iValidShapeIndex;
}
