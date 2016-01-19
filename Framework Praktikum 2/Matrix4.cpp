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
#include <stdio.h>		// cout
#include <iostream>		// cout

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

	for(int row =0 ; row < 4; row ++) 
			{
				for( int col = 0 ; col < 4 ; col ++)
					{ 

						result.values[row][col] = this->values[row][0] * rightMatrix.values[0][col]
						+this->values[row][1] * rightMatrix.values[1][col] 
					+ this->values[row][2] * rightMatrix.values[2][col]
					+ this->values[row][3] * rightMatrix.values[3][col]; 
						Matrix4f test=	Matrix4f::values[row][col];
					
					//	printf("%d", test);
					}
				}

	return result;
}

Vec4f Matrix4f::operator* (const Vec4f& vec) const
{
	// start with 0-vector
	Vec4f result;
		for(int row =0 ; row < 4; row ++) 
			{
				for( int col = 0 ; col < 4 ; col ++)
					{ 
						result[row] = this->values[row][0] * vec[0]
						+this->values[row][1] * vec[1] 
						+ this->values[row][2] * vec[2]
						+ this->values[row][3] * vec[3]; 
					}
				}
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

Matrix4f Matrix4f::rotationYMatrix(float angle)
{
	Matrix4f result;
	result.values[0][0] = std::cosf(angle);
	result.values[0][2] = std::sinf(angle);
	result.values[2][0] = -std::sinf(angle);
	result.values[2][2] = std::cosf(angle);
	return result;
}

Matrix4f Matrix4f::rotationZMatrix(float angle)
{
	Matrix4f result;
	result.values[0][0] = std::cosf(angle);
	result.values[0][1] = - std::sinf(angle);
	result.values[1][0] = std::sinf(angle);
	result.values[1][1] = std::cosf(angle);
	return result;
}
Matrix4f Matrix4f::scaleMatrix(float sx, float sy, float sz){
	Matrix4f result;
	result.values[0][0] = sx;
	result.values[1][1] = sy;
	result.values[2][2] = sz;
	return result;
}

Matrix4f Matrix4f::translateMatrix(int dx, int dy, int dz){
	Matrix4f result;
	result.values[0][3] = dx;
	result.values[1][3] = dy;
	result.values[2][3] = dz;
	return result;
}


Matrix4f Matrix4f::test_Multiplikation(){
	Matrix4f a(1.0f);
	Matrix4f b(1.0f);
	float c=2.0f; 
	for (int row=0 ; row < 4 ; row++){

		for(int col=0; col < 4; col++){
			a.values[row][col] = a.values[row][col] +c;
			b.values[row][col] = a.values[row][col] +(2.0f*c); 
	}

	}
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	Matrix4f result = a.operator*(b);
	std::cout << result << std::endl;
	return result;

}

Vec4f Matrix4f::test_vecMult(){
	Matrix4f a(2.0f);
	Vec4f b;
	b[3] = 1.0f;

	b.x = 2.0f;
	b.y = 3.0f;
	b.z = 4.0f;
	
	std::cout << b << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << a << std::endl;
	std::cout << "\n" << std::endl;
	
	Vec4f result = a.operator*(b);
	std::cout << result << std::endl;
	return result; 


}


// ==================================================