#pragma once
#include <chrono>

namespace QBRT
{
	class QBTimer
	{
		public:
			QBTimer();

			~QBTimer();

			void		SetFPSCaptureTimeEveryNSecs(float fFPSCaptureTimeInSecs);
			void		GrabTime();
		private:
			uint32_t														m_iFrameCount;
			std::chrono::time_point<std::chrono::high_resolution_clock>		m_LastUpdatedTime;
			float															m_fFPSCaptureTimeEveryNSecs;
	};
}