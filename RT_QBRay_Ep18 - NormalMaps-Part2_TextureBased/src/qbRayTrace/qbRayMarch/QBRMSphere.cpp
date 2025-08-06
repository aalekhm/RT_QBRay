#include "QBRMSphere.hpp"

// Constructor.
QBRT::RM::QBRMSphere::QBRMSphere()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector3<double>*, qbVector3<double>*)> func = [=](qbVector3<double>* vLocation, qbVector3<double>* vParams)
	{
		return this->ObjectFunc(vLocation, vParams);
	};

	// Assign the object function.
	SetObjectFunc(func);
}

// Destructor
QBRT::RM::QBRMSphere::~QBRMSphere()
{

}

// Private object function.
double QBRT::RM::QBRMSphere::ObjectFunc(qbVector3<double>* vLocation, qbVector3<double>* vParams)
{
	qbVector3<double>	vCenter{ 0.0, 0.0, 0.0 };
	qbVector<double>	vIntParams = std::vector<double>{ 1.0, 0.0, 0.0 };

	return QBRT::RM::SDF::Sphere(*vLocation, vCenter, vIntParams);
}
