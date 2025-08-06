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

#ifndef QBVECTOR2_H
#define QBVECTOR2_H

/* *************************************************************************************************

	qbVector2
	
	Class to provide capability to handle two-dimensional vectors.

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
class qbVector2
{
	public:
		// Define the various constructors.
		// Default.
		qbVector2();
		
		// With input data (std::vector).
		qbVector2(const std::vector<T> &inputData);
		// With input data (qbVector).
		qbVector2(const qbVector<T> &inputData);
		// With input data (qbVector2).
		qbVector2(const qbVector2<T> &inputData);
		// With input data as two separate values.
		qbVector2(const T x, const T y);
		
		// And the destructor.
		~qbVector2();	
		
		// Keep the GetNumDims() function for backwards compatibility.
		int GetNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);		
		
		// Functions to perform computations on the vector.
		// Return the length of the vector.
		T norm();
		
		// Return a normalized copy of the vector.
		qbVector2<T> Normalized();
		
		// Normalize the vector in place.
		void Normalize();
		
		// Overloaded operators.
		qbVector2<T> operator+ (const qbVector2<T> &rhs) const;		
		qbVector2<T> operator- (const qbVector2<T> &rhs) const;
		qbVector2<T> operator* (const T &rhs) const;
		
		// Overload the assignment operator.
		qbVector2<T> operator= (const qbVector<T> &rhs);
		qbVector2<T> operator= (const std::vector<T> &rhs);
		qbVector2<T> operator= (const qbVector2<T> &rhs);
		
		// Friend functions.
		template <class U> friend qbVector2<U> operator* (const U &lhs, const qbVector2<U> &rhs);
		
		// Static functions.
		static T dot(const qbVector2<T> &a, const qbVector2<T> &b);
		
	public:
		union {
			struct {
				T x;
				T y;
			};
			struct {
				T min;
				T max;
			};
		};
};

/* **************************************************************************************************
CONSTRUCTOR / DESTRUCTOR FUNCTIONS
/* *************************************************************************************************/
// The default constructor.
template <class T>
qbVector2<T>::qbVector2()
{
	x = static_cast<T>(0.0);
	y = static_cast<T>(0.0);
}

template <class T>
qbVector2<T>::qbVector2(const std::vector<T> &inputData)
{
	if (inputData.size() != 2)
		throw std::invalid_argument("Cannot assign std::vector to qbVector2 - assignment dimension mismatch.");
		
	x = inputData.at(0);
	y = inputData.at(1);
}

template <class T>
qbVector2<T>::qbVector2(const qbVector<T> &inputData)
{
	if (inputData.GetNumDims() != 2)
		throw std::invalid_argument("Cannot assign qbVector to qbVector2 - assignment dimension mismatch.");
		
	x = inputData.GetElement(0);
	y = inputData.GetElement(1);
}

template <class T>
qbVector2<T>::qbVector2(const qbVector2<T> &inputData)
{
	x = inputData.x;
	y = inputData.y;
}

template <class T>
qbVector2<T>::qbVector2(const T _x, const T _y)
{
	x = _x;
	y = _y;
}

template <class T>
qbVector2<T>::~qbVector2()
{
	// For now, we don't need to do anything in the destructor.
}

/* **************************************************************************************************
FUNCTIONS TO PERFORM COMPUTATIONS ON THE VECTOR
/* *************************************************************************************************/
// Compute the length of the vector, known as the 'norm'.
template <class T>
T qbVector2<T>::norm()
{		
	return sqrt((x*x) + (y*y));
}

// Return a normalized copy of the vector.
template <class T>
qbVector2<T> qbVector2<T>::Normalized()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	
	// Compute the normalized version of the vector.
	//qbVector<T> result(m_vectorData);
	qbVector2<T> result;
	result.x = x / vecNorm;
	result.y = y / vecNorm;

	return result;
}

// Normalize the vector in place.
template <class T>
void qbVector2<T>::Normalize()
{
	// Compute the vector norm.
	T vecNorm = this->norm();
	T denominator = static_cast<T>(1.0) / vecNorm;
	
	x = x / denominator;
	y = y / denominator;
}

/* **************************************************************************************************
OVERLOADED OPERATORS
/* *************************************************************************************************/
template <class T>
qbVector2<T> qbVector2<T>::operator+ (const qbVector2<T> &rhs) const
{
	qbVector2<T> result;
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	
	return result;
}

template <class T>
qbVector2<T> qbVector2<T>::operator- (const qbVector2<T> &rhs) const
{
	qbVector2<T> result;
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	
	return result;
}

template <class T>
qbVector2<T> qbVector2<T>::operator* (const T &rhs) const
{
	qbVector2<T> result;
	result.x = x * rhs;
	result.y = y * rhs;
	
	return result;
}

/* **************************************************************************************************
THE ASSIGNMENT (=) OPERATOR
/* *************************************************************************************************/
template <class T>
qbVector2<T> qbVector2<T>::operator= (const qbVector<T> &rhs)
{
	if (rhs.GetNumDims() != 2)
		throw std::invalid_argument("Cannot assign qbVector to qbVector2 - assignment dimension mismatch.");
	
	x = rhs.GetElement(0);
	y = rhs.GetElement(1);
	
	return *this;
}

template <class T>
qbVector2<T> qbVector2<T>::operator= (const std::vector<T> &rhs)
{
	if (rhs.size() != 2)
		throw std::invalid_argument("Cannot assign std::vector to qbVector2 - assignment dimension mismatch.");
	
	x = rhs.at(0);
	y = rhs.at(1);
	
	return *this;
}

template <class T>
qbVector2<T> qbVector2<T>::operator= (const qbVector2<T> &rhs)
{
	x = rhs.x;
	y = rhs.y;
	
	return *this;
}

/* **************************************************************************************************
FRIEND FUNCTIONS
/* *************************************************************************************************/
template <class T>
qbVector2<T> operator* (const T &lhs, const qbVector2<T> &rhs)
{
	// Perform scalar multiplication.
	qbVector2<T> result;
	result.x = lhs * rhs.x;
	result.y = lhs * rhs.y;
		
	return result;
}

/* **************************************************************************************************
STATIC FUNCTIONS
/* *************************************************************************************************/
template <class T>
T qbVector2<T>::dot(const qbVector2<T> &a, const qbVector2<T> &b)
{
	T cumulativeSum = (a.x * b.x) + (a.y * b.y);
	
	return cumulativeSum;
}

/* **************************************************************************************************
FUNCTIONS FOR COMPATIBILITY
/* *************************************************************************************************/
template <class T>
int qbVector2<T>::GetNumDims() const
{
	return 2;
}

template <class T>
T qbVector2<T>::GetElement(int index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else
	{
		throw std::invalid_argument("Attempt to get invalid element index.");
	}
	return 0;
}

template <class T>
void qbVector2<T>::SetElement(int index, T value)
{
	if (index == 0)
	{
		x = value;
	}
	else if (index == 1)
	{
		y = value;
	}
	else
	{
		throw std::invalid_argument("Attempt to set invalid element index.");
	}
}

#endif
