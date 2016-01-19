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

#ifndef MATRIX_4_H
#define MATRIX_4_H

#include "Vec4.h"
#include "Vec3.h"

class Matrix4f
{
public:

	// class data: 4 by 4 matrix of floats. row first order, so first index is the row, second index the column.
	float values[4][4];

	// constructor generates eye-matrix by default
	Matrix4f();

	// constructor sets every entry to val
	Matrix4f(float val);

	// matrix matrix multiplication. uses this matrix as left one and the argument rightMatrix as right one
	Matrix4f operator* (const Matrix4f& rightMatrix) const;

	// matrix vector multiplication. multiplies this matrix with vec
	Vec4f operator* (const Vec4f& vec) const;

	// matrix vector multiplication. multiplies this matrix with vec. automatically adds the weight 1.0f to the vector.
	Vec3f operator* (const Vec3f& vec) const;

	// TODO: implement more basis transformation matrices
	// ==================================================

	// rotation around axis x (angle in rad: 2pi = 360°)
	static Matrix4f rotationXMatrix(float angle);
	// rotation around axis y (angle in rad: 2pi = 360°)
	static Matrix4f rotationYMatrix(float angle);
	// rotation around axis z (angle in rad: 2pi = 360°)
	static Matrix4f rotationZMatrix(float angle);
	// scale the matrix  (sx, sy, sz > 1 means upscaleing; sx,sy,sz > 1 means downscaleing; sx,sy,sz < 0 means Mirroring)
	static Matrix4f scaleMatrix(float sx, float sy, float sz);
	// Translate the Matrix to point dx,dy,dz.
	static Matrix4f translateMatrix(int dx, int dy, int dz);

	static Matrix4f test_Multiplikation();
	static Vec4f test_vecMult();


	// ==================================================

};

// ostream << operator. E.g. use "std::cout << matrix << std::endl;"
std::ostream& operator<< (std::ostream& os, const Matrix4f& matrix);

#endif