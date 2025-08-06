#include "QBObjectBase.hpp"
#include <math.h>

#define EPSILON 1e-21f

// Default constructor.
QBRT::QBObjectBase::QBObjectBase()
{

}

// The destructor.
QBRT::QBObjectBase::~QBObjectBase()
{

}

// Function to test for intersections.
bool QBRT::QBObjectBase::TestIntersection(const QBRay& castRay, qbVector3<double>& vIntersectionPoint, qbVector3<double>& vLocalNormal, qbVector3<double>& vLocalColour)
{
	return false;
}

// Function to test whether two floating-point numbers are close to being equal.
bool QBRT::QBObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1 - f2) < EPSILON;
}
