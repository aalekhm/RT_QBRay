#pragma once

#include "qbRayTrace/qbLinAlg/qbVector3.hpp"

namespace QBRT
{
	namespace RM
	{
		namespace SDF
		{
			double Sphere(	const qbVector3<double>& vP, 
							const qbVector3<double>& vCenter,
							const qbVector3<double>& vParams);

			double Torus(	const qbVector3<double>& vP, 
							const qbVector3<double>& vCenter,
							const qbVector3<double>& vParams);

			double Box(		const qbVector3<double>& vP, 
							const qbVector3<double>& vCenter,
							const qbVector3<double>& vParams);
		}
	}
}