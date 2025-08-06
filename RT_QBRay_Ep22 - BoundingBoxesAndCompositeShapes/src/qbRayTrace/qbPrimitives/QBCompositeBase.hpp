#pragma once

#include "QBObjectBase.hpp"
#include "QBBox.hpp"

namespace QBRT
{
	namespace SHAPES
	{
		class QBCompositeBase : public QBObjectBase
		{
			public:
				// Default constructor.
				QBCompositeBase();
				
				// The destructor.
				virtual ~QBCompositeBase() override;
				
				// Function to add a sub-shape.
				void				AddSubShape(std::shared_ptr<QBRT::QBObjectBase> subShape);
				
				// Override the GetExtents function.
				virtual void		GetExtents(	qbVector2<double>& xLim, 
												qbVector2<double>& yLim, 
												qbVector2<double>& zLim) override;
				
				// Override the function to test for intersections.
				virtual bool		TestIntersection(	const QBRT::QBRay& castRay, 
														QBRT::DATA::HitData& hitData) override;
																
				// Function to update the bounds after sub-shapes have been modified.
				void				UpdateBounds();
				
			private:
				// Test for intersections with the list of sub-objects.
				int					TestIntersections(	const QBRT::QBRay& castRay,
														const QBRT::QBRay& bckRay,
														qbVector3<double>& vPointOfIntersection,
														double& fCurrentDist,
														QBRT::DATA::HitData &hitData);
			public:
				// Bounding box.
				QBRT::QBBox											m_BoundingBox;
				bool												m_bUseBoundingBox = true;
			
				// List of sub-objects.
				std::vector<std::shared_ptr<QBRT::QBObjectBase>>	m_vShapeList;

				// Object limits.
				qbVector2<double>									m_xLim;
				qbVector2<double>									m_yLim;
				qbVector2<double>									m_zLim;
				
		};
	}
}