#pragma once

#include "qbLinAlg/qbVector3.hpp"
#include "QBRay.hpp"
#include "qbLinAlg/qbMatrix44.hpp"

namespace QBRT
{
	// Define direction flag values.
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;

	class QBGeometricTransform
	{
		public:
			// Constructor & destructor.
			QBGeometricTransform();
			~QBGeometricTransform();

			// Construct from a pair of matrices.
			QBGeometricTransform(const qbMatrix44<double>& matFwd, const qbMatrix44<double>& matBck);
			QBGeometricTransform(	const qbVector3<double>& vTranslation,
									const qbVector3<double>& vRotation,
									const qbVector3<double>& vScaling);

			// Function to set translation, rotation and scale components.
			void						SetTransform(	const qbVector3<double>& vTranslation,
														const qbVector3<double>& vRotation,
														const qbVector3<double>& vScaling);

			// Functions to return the transform matrices.
			qbMatrix44<double>&			GetForward();
			qbMatrix44<double>&			GetBackward();

			// Function to apply the transform.
			QBRT::QBRay					Apply(const QBRT::QBRay& inputRay, bool bDirFlag);
			qbVector3<double>			Apply(const qbVector3<double>& vInputVector, bool bDirFlag);

			// Overload operators.
			friend QBGeometricTransform operator* (	const QBRT::QBGeometricTransform& geomTransformLHSLHS,
													const QBRT::QBGeometricTransform& geomTransformLHSRHS);

			// Overload the assignment operator.
			QBGeometricTransform		operator=(const QBRT::QBGeometricTransform& geomTransformRHS);

			// Function to print transform matrix to STDOUT.
			void						PrintMatrix(bool bDirFlag);

			// Function to allow printing of vectors.
			static void					PrintVector(const qbVector3<double>& vInVector);

		private:
			void						Print(const qbMatrix44<double>& matIN);

		private:
			qbMatrix44<double>			m_matFwd;
			qbMatrix44<double>			m_matBck;
	};
}