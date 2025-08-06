#include "QBImageNormal.hpp"

// Constructor / Destructor.
QBRT::QBNormal::QBImageNormal::QBImageNormal()
{

}

QBRT::QBNormal::QBImageNormal::~QBImageNormal()
{

}
				
// Function to load the image to be used.
bool QBRT::QBNormal::QBImageNormal::LoadImage(std::string sFilename)
{
	bool bImageLoaded = false;

	m_pImageTexture = std::make_shared<QBRT::QBTexture::QBImageTexture>();
	if (m_pImageTexture != nullptr)
	{
		if (m_pImageTexture->LoadImage(sFilename))
		{
			bImageLoaded = true;
		}
	}

	return bImageLoaded;
}
			
// Function to compute the perturbation.
qbVector3<double> QBRT::QBNormal::QBImageNormal::ComputePerturbation(const qbVector3<double>& vNormal, const qbVector2<double>& vUVCoords)
{
	double xDisplacement = 0.0;
	double yDisplacement = 0.0;
	double zDisplacement = 0.0;
	if (m_pImageTexture->IsImageLoaded())
	{	
		double iWidth = m_pImageTexture->GetWidth();
		double iHeight = m_pImageTexture->GetHeight();

		// Apply the local transform to the (u,v) coordinates.
		qbVector2<double> vInputLoc = vUVCoords;
		qbVector2<double> vNewLoc = ApplyTransform(vInputLoc);
		double u = vNewLoc.x;
		double v = vNewLoc.y;
		
		// Modulo arithmatic to account for possible tiling.
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);		
		
		// Convert (u,v) to image dimensions (x,y).
		double xsd = static_cast<double>(iWidth);
		double ysd = static_cast<double>(iHeight);
		double xF = ((u + 1.0) / 2.0) * xsd;
		double yF = ysd - (((v + 1.0) / 2.0) * ysd);

		// x, y are the positions with the particular square
		int x = static_cast<int>(round(xF));
		int y = static_cast<int>(round(yF));

#if (USE_BILINEARINTERPOLATION == 1)
		// Positions of the 4 corners around the above point(x, y)
		int xMin = static_cast<int>(floor(xF));
		int yMin = static_cast<int>(floor(yF));
		int xMax = static_cast<int>(ceil(xF));
		int yMax = static_cast<int>(ceil(yF));
		
		// Perform bilinear interpolation.
		// Get Colour values of the 4 corners
		qbVector4<double> vColour0 = GetColourAtPosition(xMin, yMin);
		qbVector4<double> vColour1 = GetColourAtPosition(xMax, yMin);
		qbVector4<double> vColour2 = GetColourAtPosition(xMin, yMax);
		qbVector4<double> vColour3 = GetColourAtPosition(xMax, yMax);

		double interpR = QBRT::QBUtils::BilinearInterp(xMin, yMin,		vColour0.r, xMax, yMin,		vColour1.r, xMin, yMax,		vColour2.r, xMax, yMax,		vColour3.r, xF, yF);
		double interpG = QBRT::QBUtils::BilinearInterp(xMin, yMin,		vColour0.g, xMax, yMin,		vColour1.g, xMin, yMax,		vColour2.g, xMax, yMax,		vColour3.g, xF, yF);
		double interpB = QBRT::QBUtils::BilinearInterp(xMin, yMin,		vColour0.b, xMax, yMin,		vColour1.b, xMin, yMax,		vColour2.b, xMax, yMax,		vColour3.b, xF, yF);
		
		xDisplacement = interpR;
		yDisplacement = interpG;
		zDisplacement = interpB;
#else
		qbVector4<double> vColour = GetColourAtPosition(x, y);
		xDisplacement = vColour.r;
		yDisplacement = vColour.g;
		zDisplacement = vColour.b;
#endif
	}
	
	if (m_bReverseXY)
	{
		xDisplacement = -xDisplacement;
		yDisplacement = -yDisplacement;
	}	
		
	qbVector3<double> perturbation(xDisplacement, yDisplacement, zDisplacement);
	return PerturbNormal(vNormal, perturbation);
}
			
// Function to return the value of a pixel in the image surface.													
qbVector4<double> QBRT::QBNormal::QBImageNormal::GetColourAtPosition(int x, int y)
{
	// Since the colour values are between	0.0 < Colour 1.0
	// we 1st convert then to				0 < Colour 255
	// then betweeen						-128.0 < Colour < 128.0
	//  except for blue;
	qbVector4<double> vReturnColour = m_pImageTexture->GetColourAtPosition(x, y);

	//// Return the color.		
	vReturnColour = vReturnColour * 255.0;
	vReturnColour.r = static_cast<double>(vReturnColour.r - 128) / 128.0;
	vReturnColour.g = static_cast<double>(vReturnColour.g - 128) / 128.0;
	vReturnColour.b = static_cast<double>(vReturnColour.b) / 255.0;

	return vReturnColour;
}
