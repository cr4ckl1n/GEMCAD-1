// ========================================================================= //
// Authors: Matthias Bein                                                    //
// mailto:matthias.bein@igd.fraunhofer.de                                    //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 29.10.2013                                                 //
// ========================================================================= //

#include "Matrix4.h"

Matrix4f::Matrix4f()
{
	for(unsigned int row = 0; row < 4; ++row)
	{
		for(unsigned int column = 0; column < 4; ++column)
		{
			if(row == column)
				values[row][column] = 1.0f;
			else
				values[row][column] = 0.0f;
		}
	}
}

Matrix4f::Matrix4f(float val)
{
	for(unsigned int row = 0; row < 4; ++row)
	{
		for(unsigned int column = 0; column < 4; ++column)
		{
			values[row][column] = val;
		}
	}
}


Matrix4f Matrix4f::operator* (const Matrix4f& rightMatrix) const
{
	// start with 0-matrix
	Matrix4f result(0.0f);

	// TODO: implement matrix matrix multiplication
	// ============================================

	// ============================================

	return result;
}

Vec4f Matrix4f::operator* (const Vec4f& vec) const
{
	// start with 0-vector
	Vec4f result;

	// TODO: implement matrix vector multiplication
	// ============================================

	// ============================================

	return result;
}

Vec3f Matrix4f::operator*(const Vec3f& vec) const
{
	Vec4f v4(vec.x, vec.y, vec.z, 1.0f);
	Vec4f result = *this * v4;
	result.homogenize();
	return Vec3f(result.x, result.y, result.z);
}

std::ostream& operator<< (std::ostream& os, const Matrix4f& matrix)
{
	os  << matrix.values[0][0] << ", " << matrix.values[0][1] << ", " << matrix.values[0][2] << ", " << matrix.values[0][3] << std::endl
		<< matrix.values[1][0] << ", " << matrix.values[1][1] << ", " << matrix.values[1][2] << ", " << matrix.values[1][3] << std::endl
		<< matrix.values[2][0] << ", " << matrix.values[2][1] << ", " << matrix.values[2][2] << ", " << matrix.values[2][3] << std::endl
		<< matrix.values[3][0] << ", " << matrix.values[3][1] << ", " << matrix.values[3][2] << ", " << matrix.values[3][3];
	return os;
}

// TODO: implement more basis transformation matrices
// ==================================================

Matrix4f Matrix4f::rotationXMatrix(float angle)
{
	Matrix4f result;
	result.values[1][1] = std::cosf(angle);
	result.values[1][2] = - std::sinf(angle);
	result.values[2][1] = std::sinf(angle);
	result.values[2][2] = std::cosf(angle);
	return result;
}

// ==================================================