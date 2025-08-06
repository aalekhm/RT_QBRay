// This file is part of the qbLinAlg linear algebra library.
/*
MIT License
Copyright (c) 2023 Michael Bennett	

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef QBVECTOR3_H
#define QBVECTOR3_H

/* *************************************************************************************************

	qbVector3
	
	Class to provide capability to handle three-dimensional vectors.

	Created as part of the qbLinAlg linear algebra library, which is intended to be primarily for
	educational purposes. For more details, see the corresponding videos on the QuantitativeBytes
	YouTube channel at:
	
	www.youtube.com/c/QuantitativeBytes								

************************************************************************************************* */

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <memory>
#include "qbVector.h"

template <class T>
class qbVector3
{
	public:
		// Define the various constructors.
		// Default.
		qbVector3();
		
		// With input data (std::vector).
		qbVector3(const std::vector<T> &inputData);
		// With input data (qbVector).
		qbVector3(const qbVector<T> &inputData);
		// With input data (qbVector3).
		qbVector3(const qbVector3<T> &inputData);
		// With input data as three separate values.
		qbVector3(const T x, const T y, const T z);
		
		// And the destructor.
		~qbVector3();	
		
		// Keep the GetNumDims() function for backwards compatibility.
		int GetNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);		
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		T norm();
		
		// Return a normalized copy of the vector.
		qbVector3<T> Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		qbVector3<T> operator+ (const qbVector3<T> &rhs) const;		
		qbVector3<T> operator- (const qbVector3<T> &rhs) const;
		qbVector3<T> operator* (const T &rhs) const;
		
		// Overload the assignment operator.
		qbVector3<T> operator= (const qbVector<T> &rhs);
		qbVector3<T> operator= (const std::vector<T> &rhs);
		qbVector3<T> operator= (const qbVector3<T> &rhs);
		
		// Friend functions.
		template <class U> friend qbVector3<U> operator* (const U &lhs, const qbVector3<U> &rhs);
		
		// Static functions.
		static T dot(const qbVector3<T> &a, const qbVector3<T> &b);
		static qbVector3<T> cross(const qbVector3<T> &a, const qbVector3<T> &b);
		
	public:
		union {
			struct {
				T x;
				T y;
				T z;
			};
			struct {
				T r;
				T g;
				T b;
			};
		};
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
qbVector3<T>::qbVector3()
{
	x = static_cast<T>(0.0);
	y = static_cast<T>(0.0);
	z = static_cast<T>(0.0);
}

template <class T>
qbVector3<T>::qbVector3(const std::vector<T> &inputData)
{
	if (inputData.size() != 3)
		throw std::invalid_argument("Cannot assign std::vector to qbVector3 - assignment dimension mismatch.");
		
	x = inputData.at(0);
	y = inputData.at(1);
	z = inputData.at(2);
}

template <class T>
qbVector3<T>::qbVector3(const qbVector<T> &inputData)
{
	if (inputData.GetNumDims() != 3)
		throw std::invalid_argument("Cannot assign qbVector to qbVector3 - assignment dimension mismatch.");
		
	x = inputData.GetElement(0);
	y = inputData.GetElement(1);
	z = inputData.GetElement(2);
}

template <class T>
qbVector3<T>::qbVector3(const qbVector3<T> &inputData)
{
	x = inputData.x;
	y = inputData.y;
	z = inputData.z;
}

template <class T>
qbVector3<T>::qbVector3(const T x, const T y, const T z)
{
	x = x;
	y = y;
	z = z;
}

template <class T>
qbVector3<T>::~qbVector3()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T qbVector3<T>::norm()
{		
	return sqrt((x*x) + (y*y) + (z*z));
}

// Return a normalized copy of the vector.
template <class T>
qbVector3<T> qbVector3<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	//qbVector<T> result(m_vectorData);
	qbVector3<T> result;
	result.x = x / vecNorm;
	result.y = y / vecNorm;
	result.z = z / vecNorm;

	return result;
}

// Normalize the vector in place.
template <class T>
void qbVector3<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	x = x / vecNorm;
	y = y / vecNorm;
	z = z / vecNorm;
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
qbVector3<T> qbVector3<T>::operator+ (const qbVector3<T> &rhs) const
{
	qbVector3<T> result;
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;
	
	return result;
}

template <class T>
qbVector3<T> qbVector3<T>::operator- (const qbVector3<T> &rhs) const
{
	qbVector3<T> result;
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;
	
	return result;
}

template <class T>
qbVector3<T> qbVector3<T>::operator* (const T &rhs) const
{
	qbVector3<T> result;
	result.x = x * rhs;
	result.y = y * rhs;
	result.z = z * rhs;
	
	return result;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
qbVector3<T> qbVector3<T>::operator= (const qbVector<T> &rhs)
{
	if (rhs.GetNumDims() != 3)
		throw std::invalid_argument("Cannot assign qbVector to qbVector3 - assignment dimension mismatch.");
	
	x = rhs.GetElement(0);
	y = rhs.GetElement(1);
	z = rhs.GetElement(2);
	
	return *this;
}

template <class T>
qbVector3<T> qbVector3<T>::operator= (const std::vector<T> &rhs)
{
	if (rhs.size() != 3)
		throw std::invalid_argument("Cannot assign std::vector to qbVector3 - assignment dimension mismatch.");
	
	x = rhs.at(0);
	y = rhs.at(1);
	z = rhs.at(2);
	
	return *this;
}

template <class T>
qbVector3<T> qbVector3<T>::operator= (const qbVector3<T> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	
	return *this;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
qbVector3<T> operator* (const T &lhs, const qbVector3<T> &rhs)
{
	// Perform scalar multiplication.
	qbVector3<T> result;
	result.x = lhs * rhs.x;
	result.y = lhs * rhs.y;
	result.z = lhs * rhs.z;
		
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T qbVector3<T>::dot(const qbVector3<T> &a, const qbVector3<T> &b)
{
	T cumulativeSum = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	
	return cumulativeSum;
}

template <class T>
qbVector3<T> qbVector3<T>::cross(const qbVector3<T> &a, const qbVector3<T> &b)
{
	// Compute the cross product.
	qbVector3<T> result;
	result.SetElement(0, ((a.GetElement(1) * b.GetElement(2)) - (a.GetElement(2) * b.GetElement(1))));
	result.SetElement(1, (-((a.GetElement(0) * b.GetElement(2)) - (a.GetElement(2) * b.GetElement(0)))));
	result.SetElement(2, ((a.GetElement(0) * b.GetElement(1)) - (a.GetElement(1) * b.GetElement(0))));		
	//result.m_x = (a.m_y * b.m_z) - (a.m_z * b.m_y);
	//result.m_y = -((a.m_x * b.m_z) - (a.m_z * b.m_x));
	//result.m_z = (a.m_x * b.m_y) - (a.m_y * b.m_x);
	
	return result;
}

/* **************************************************************************************************
FUNCTIONS FOR COMPATIBILITY
/* *************************************************************************************************/
template <class T>
int qbVector3<T>::GetNumDims() const
{
	return 3;
}

template <class T>
T qbVector3<T>::GetElement(int index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else if (index == 2)
	{
		return z;
	}
	else
	{
		throw std::invalid_argument("Attempt to get invalid element index.");
	}
	return 0;
}

template <class T>
void qbVector3<T>::SetElement(int index, T value)
{
	if (index == 0)
	{
		x = value;
	}
	else if (index == 1)
	{
		y = value;
	}
	else if (index == 2)
	{
		z = value;
	}
	else
	{
		throw std::invalid_argument("Attempt to set invalid element index.");
	}
}

#endif
