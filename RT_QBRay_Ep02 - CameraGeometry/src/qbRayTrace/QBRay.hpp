#pragma once

#include <vector>
#include <SDL3/SDL.h>
#include "QBImage.hpp"

#include "qbLinAlg/qbVector3.hpp"

namespace QBRT
{
	class QBRay
	{
		public:
			// The default constructor.
			QBRay(const qbVector3<double>& vPoint1, const qbVector3<double>& vPoint2);
			
			qbVector3<double> GetPoint1() const;
			qbVector3<double> GetPoint2() const;

		public:
			qbVector3<double> m_vPoint1;
			qbVector3<double> m_vPoint2;
			qbVector3<double> m_vDir;
		private:
	};
}