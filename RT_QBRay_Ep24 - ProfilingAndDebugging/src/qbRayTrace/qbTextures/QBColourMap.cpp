#include "QBColourMap.hpp"

// Constructor / destructor.
QBRT::QBTexture::QBColourMap::QBColourMap()
{

}

QBRT::QBTexture::QBColourMap::~QBColourMap()
{

}

// Function to set a stop as a color.
void QBRT::QBTexture::QBColourMap::SetStop(double fPosition, const qbVector4<double>& vColourValues)
{
	m_vStopPositions.push_back(fPosition);
	m_StopValues.push_back(vColourValues);
}

// Function to get the color at a particular position.
qbVector4<double> QBRT::QBTexture::QBColourMap::GetColor(double fPosition)
{
	// Find the closest stops to the current position.
	int iNumStops = m_StopValues.size();
	int iStartStop = 0;
	int iEndStop = 0;
	double fDiff = 2.0;
	for (int i = 0; i < iNumStops; ++i)
	{
		double t = m_vStopPositions.at(i) - fPosition;
		if (fabs(t) < fDiff)
		{
			fDiff = fabs(t);
			iStartStop = i;
			if (t < 0.0)
				iEndStop = std::min(iNumStops, (i + 1));
			else if (t > 0.0)
				iEndStop = std::max((i - 1), 0);
			else
				iEndStop = i;
		}
	}
	
	// If the position was exactly at a stop, we simply return that value.
	if (iStartStop == iEndStop)
		return m_StopValues.at(iStartStop);
		
	// Otherwise we need to interpolate between the first and second stops.
	// Make sure the stops are in the right order.
	if (iEndStop < iStartStop)
		std::swap(iStartStop, iEndStop);
		
	// Perform linear interpolation of the values between the two stops.
	// y0 + ((x - x0)*((y1 - y0)/(x1 - x0)))
	double x = fPosition;
	double x0 = m_vStopPositions.at(iStartStop);
	double x1 = m_vStopPositions.at(iEndStop);
	return m_StopValues.at(iStartStop) + (x - x0) * ((m_StopValues.at(iEndStop) - m_StopValues.at(iStartStop)) * (1.0 / (x1 - x0)));
}
