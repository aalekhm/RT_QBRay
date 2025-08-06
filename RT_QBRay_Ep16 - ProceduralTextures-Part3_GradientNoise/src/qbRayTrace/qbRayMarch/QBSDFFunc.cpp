#include "QBSDFFunc.hpp"

double QBRT::RM::SDF::Sphere(	const qbVector3<double>& vP,
								const qbVector3<double>& vCenter,
								const qbVector3<double>& vParams)
{
	return (vP - vCenter).norm() - vParams.GetElement(0);
}

double QBRT::RM::SDF::Torus(	const qbVector3<double>& vP,
								const qbVector3<double>& vCenter,
								const qbVector3<double>& vParams)
{
	// SDF of a Sphere
	// p			= sqrt(x^2 + y^2) - rMajor
	// f(x, y, z)	= sqrt(p^2 + z^2) - rMinor

	double fRMajor = vParams.GetElement(0);
	double fRMinor = vParams.GetElement(1);
	double x = vP.GetElement(0) - vCenter.GetElement(0);
	double y = vP.GetElement(1) - vCenter.GetElement(1);
	double z = vP.GetElement(2) - vCenter.GetElement(2);
	
	double fP = sqrtf((x*x) + (y*y)) - fRMajor;
	double t2 = sqrtf((fP * fP) + (z * z)) - fRMinor;
	
	return t2;
}

double QBRT::RM::SDF::Box(	const qbVector3<double>& vP,
							const qbVector3<double>& vCenter,
							const qbVector3<double>& vParams)
{
	// SDF of a Box
	// Ax = |Px| - 1.0;	Bx = argmax(Ax, 0.0);
	// Ay = |Py| - 1.0;	By = argmax(Ay, 0.0);
	// Az = |Pz| - 1.0;	Bz = argmax(Az, 0.0);
	// fInternal = argmin( argmsx(Ax, argmax(Ay, Az)), 0.0);
	// fExternal = sqrt(Bx^2 + By^2 + Bz^2)
	// f(x, y, z) = fInternal + fExternal

	qbVector3<double> vLocation = (vP - vCenter);
	double ax = fabs(vLocation.GetElement(0)) - vParams.GetElement(0);
	double ay = fabs(vLocation.GetElement(1)) - vParams.GetElement(1);
	double az = fabs(vLocation.GetElement(2)) - vParams.GetElement(2);
	
	double bx = std::max(ax, 0.0);
	double by = std::max(ay, 0.0);
	double bz = std::max(az, 0.0);
	
	double fInternalDist = std::min(std::max(ax, std::max(ay, az)), 0.0);
	double fExternalDist = sqrt((bx*bx)+(by*by)+(bz*bz));
	
	return fInternalDist + fExternalDist;
}
