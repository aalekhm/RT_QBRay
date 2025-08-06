#pragma once
#include <memory>
#include "qbRayTrace/QBUtils.hpp"
#include "qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "qbRayTrace/QBRay.hpp"
#include "qbRayTrace/QBGeometricTransform.hpp"

namespace QBRT
{
	// Forward-declare the material base class. 
	// This will be overriden later.
	class QBMaterialBase;

	// Define constants for UV mapping types.
	constexpr int uvSPHERE		= 0;
	constexpr int uvPLANE		= 1;
	constexpr int uvCYLINDER	= 2;
	constexpr int uvBOX			= 3;
	constexpr int uvCONE		= 4;

	class QBObjectBase
	{
		public:
			// Constructor and destructor.
			QBObjectBase();
			virtual ~QBObjectBase();

			// Function to test for intersections.
			virtual bool	TestIntersection(	const QBRay& castRay, 
												QBRT::DATA::HitData& sHitData);

			// Function to set the transform matrix.
			void			SetTransform(const QBRT::QBGeometricTransform& geomTransform);

			// Function to test whether two floating-point numbers are close to being equal.
			bool			CloseEnough(const double f1, const double f2);

			// Function to assign a material.
			bool			AssignMaterial(const std::shared_ptr<QBRT::QBMaterialBase>& pMaterial);

			// Function to compute UV space.
			void			ComputeUV(const qbVector3<double>& vLocalPOI, qbVector2<double>& vUVCoords);

			// Function to get the extents of the object.
			virtual void					GetExtents(	qbVector2<double>& xLim, 
														qbVector2<double>& yLim, 
														qbVector2<double>& zLim);
			virtual void					GetExtents(	const QBRT::QBGeometricTransform& parentGeometricTransform,
														qbVector2<double>& xLim, 
														qbVector2<double>& yLim, 
														qbVector2<double>& zLim);
			std::vector<qbVector3<double>>	ConstructCube(	double xMin, 
															double xMax, 
															double yMin, 
															double yMax, 
															double zMin, 
															double zMax);

		// Public member variables.
		public:
			// The geometric transform applied to the object.
			QBGeometricTransform					m_GeomTransform;
			 
			// The base colour of the object.
			qbVector4<double>						m_vBaseColour;

			// A reference to the material assigned to this object.
			std::shared_ptr<QBRT::QBMaterialBase>	m_pMaterial;

			// A flag to indicate whether this object has a material or not.
			bool									m_bHasMaterial = false;

			std::string								m_sFriendlyName;

			// Control what type of UV mapping to apply to this object.
			int										m_iUVMapType = QBRT::uvSPHERE;

			// Bounding box GTform.		
			QBRT::QBGeometricTransform				m_GeomTransformBoundingBox;
			
			// Bounding box padding.
			double									m_fBoundingBoxPadding = 0.0;
		protected:
		private:
	};
}