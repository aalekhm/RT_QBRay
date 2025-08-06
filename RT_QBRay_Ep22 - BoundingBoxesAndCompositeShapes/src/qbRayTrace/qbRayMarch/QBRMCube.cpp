#include "QBRMCube.hpp"

// Constructor.
QBRT::RM::QBRMCube::QBRMCube()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector3<double>*, qbVector3<double>*)> func = [=](qbVector3<double>* vLocation, qbVector3<double>* vParams)
	{
		return this->ObjectFunc(vLocation, vParams);
	};

	// Assign the object function.
	SetObjectFunc(func);

	// Modify the bounding box.
	m_BoundingBox->SetTransform(QBRT::QBGeometricTransform{	qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{0.0, 0.0, 0.0},
															qbVector3<double>{1.2, 1.2, 1.2}
														});
}

// Destructor
QBRT::RM::QBRMCube::~QBRMCube()
{

}

// Private object function.
double QBRT::RM::QBRMCube::ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams)
{
	qbVector3<double> vCenter = std::vector<double>{ 0.0, 0.0, 0.0 };
	qbVector<double> vIntParms = std::vector<double>{ 1.0, 1.0, 1.0 };
	return QBRT::RM::SDF::Box(*vLocation, vCenter, vIntParms);
}
