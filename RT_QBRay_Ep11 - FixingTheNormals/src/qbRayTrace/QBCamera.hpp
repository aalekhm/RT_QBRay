#pragma once

#include "qbLinAlg/qbVector3.hpp"
#include "QBRay.hpp"

namespace QBRT
{
	class QBCamera
	{
		public:
			// The default constructor.
			QBCamera();

			// Functions to set camera parameters.
			void				SetPosition(const qbVector3<double>& vNewPosition);
			void				SetLookAt(const qbVector3<double>& vNewLookAt);
			void				SetUp(const qbVector3<double>& vNewUp);

			void				SetLength(double fNewLength);
			void				SetHorizontalSize(double fNewSize);
			void				SetAspect(double fNewAspectRatio);

			qbVector3<double>	GetPosition();
			qbVector3<double>	GetLookAt();
			qbVector3<double>	GetUp();
			qbVector3<double>	GetU();
			qbVector3<double>	GetV();
			qbVector3<double>	GetScreenCenter();
			double				GetLength();
			double				GetHorizontalSize();
			double				GetAspect();

			void				UpdateCameraGeometry();
			bool				GenerateRay(float fScreenX, float fScreenY, QBRT::QBRay& vCameraRay);
		public:
			qbVector3<double>	m_vCameraPosition;
			qbVector3<double>	m_vCameraLookAt;
			qbVector3<double>	m_vCameraUp;
			double				m_CameraLength;
			double				m_CameraHorizontalSize;
			double				m_CameraAspectRatio;
			
			qbVector3<double>	m_vAlignmentVector;
			qbVector3<double>	m_vProjectionScreenU;
			qbVector3<double>	m_vProjectionScreenV;
			qbVector3<double>	m_vProjectionScreenCenter;
		private:
	};
}