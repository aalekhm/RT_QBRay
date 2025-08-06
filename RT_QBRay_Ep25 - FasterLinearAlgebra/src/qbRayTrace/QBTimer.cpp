#include "QBTimer.hpp"
#include <iostream>

QBRT::QBTimer::QBTimer()
{
	m_iFrameCount = 0;
	m_fFPSCaptureTimeEveryNSecs = 1.0;
}

QBRT::QBTimer::~QBTimer()
{

}

void QBRT::QBTimer::SetFPSCaptureTimeEveryNSecs(float fFPSCaptureTimeInSecs)
{
	m_fFPSCaptureTimeEveryNSecs = fFPSCaptureTimeInSecs;
}

void QBRT::QBTimer::GrabTime()
{
	// Record the ending time point
	auto frameEndTime = std::chrono::high_resolution_clock::now();

	m_iFrameCount++;

	// Update FPS every second (or at a desired interval)
	std::chrono::duration<double> elapsedSinceLastUpdate = frameEndTime - m_LastUpdatedTime;

	// Update 'n' seconds
	if (elapsedSinceLastUpdate.count() >= m_fFPSCaptureTimeEveryNSecs)
	{
		double fps = m_iFrameCount / elapsedSinceLastUpdate.count();
		std::cout << "iFrameCount = " << m_iFrameCount << ", FPS: " << fps << ", Rendering time: " << elapsedSinceLastUpdate.count() << "s" << std::endl;

		m_iFrameCount = 0;
		m_LastUpdatedTime = frameEndTime;
	}
}
