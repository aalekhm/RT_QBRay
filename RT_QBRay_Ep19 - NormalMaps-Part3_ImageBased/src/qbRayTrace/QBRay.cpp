#include "QBRay.hpp"

QBRT::QBRay::QBRay()
{
	m_vPoint1 = qbVector3<double>(0.0, 0.0, 0.0);
	m_vPoint2 = qbVector3<double>(0.0, 0.0, 0.0);
	m_vDir = m_vPoint2 - m_vPoint1;
}

QBRT::QBRay::QBRay(const qbVector3<double>& vPoint1, const qbVector3<double>& vPoint2)
{
	m_vPoint1 = vPoint1;
	m_vPoint2 = vPoint2;

	m_vDir = vPoint2 - vPoint1;
}
			
qbVector3<double> QBRT::QBRay::GetPoint1() const
{
	return m_vPoint1;
}

qbVector3<double> QBRT::QBRay::GetPoint2() const
{
	return m_vPoint2;
}
