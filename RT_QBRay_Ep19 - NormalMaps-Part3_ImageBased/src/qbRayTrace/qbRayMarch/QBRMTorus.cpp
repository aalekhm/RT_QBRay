#include "QBRMTorus.hpp"

// Constructor.
QBRT::RM::QBRMTorus::QBRMTorus()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector3<double>*, qbVector3<double>*)> func = [=](qbVector3<double>* vLocation, qbVector3<double>* vParams)
	{
		return this->ObjectFunc(vLocation, vParams);
	};

	// Assign the object function.
	SetObjectFunc(func);

	// Modify the bounding box.
	m_BoundingBox.SetTransform(QBRT::QBGeometricTransform{	qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{1.0, 1.0, 1.0}
														});
}

// Destructor
QBRT::RM::QBRMTorus::~QBRMTorus()
{
	
}

// Function to set the radii.
void QBRT::RM::QBRMTorus::SetRadii(double fR1, double fR2)
{
	m_vParms.SetElement(0, fR1);
	m_vParms.SetElement(1, fR2);

	UpdateBounds();
}

// Function to update the bounding box.
void QBRT::RM::QBRMTorus::UpdateBounds()
{
	m_BoundingBox.SetTransform(QBRT::QBGeometricTransform{	qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{m_fRadii1 + m_fRadii2 + 0.3, m_fRadii1 + m_fRadii2 + 0.3, m_fRadii2 + 0.2}
														});
}

// Private object function.
double QBRT::RM::QBRMTorus::ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams)
{
	qbVector3<double>	vCenter{ 0.0, 0.0, 0.0 };
	return QBRT::RM::SDF::Torus(*vLocation, vCenter, *vParams);
}
