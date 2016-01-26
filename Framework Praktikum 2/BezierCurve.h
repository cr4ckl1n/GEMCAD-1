#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>

#include "Vec3.h"		// vector (x, y, z)

// for this bezier curve class we assume the curve is ALWAYS parameterized within [0, 1]!
class BezierCurve
{

public:

	// empty constructor which generates a curve with NO control points
	BezierCurve();

	// constructor which takes given control points
	BezierCurve(const std::vector<Vec3f>& controlPoints_);

	// getting references to the data
	std::vector<Vec3f>& getControlPoints() { return controlPoints; }

	// evaluate the curve at parameter t with de Casteljau algorithm. Returns the evaluated point and its tangent at parameter t.
	std::pair<Vec3f, Vec3f> evaluateCurveAt(const float t);

	// evaluate the curve at parameters T with de Casteljau algorithm. Returns the evaluated points and their tangents.
	std::pair<std::vector<Vec3f>, std::vector<Vec3f>> evaluateCurveAt(const std::vector<float>& T);

	// evaluate the curve with de Casteljau algorithm at numberSamples sample points. Returns the evaluated points and their tangents.
	std::pair<std::vector<Vec3f>, std::vector<Vec3f>> evaluateCurveAt(const size_t numberSamples);

	// evaluate the curve at parameter t with de Casteljau algorithm. Returns both bezier curves seperated at parameter t.
	std::pair<BezierCurve, BezierCurve> separateCurveAt(const float t);
    
	// overloading the << operator to print our information of the class. declared as friend, so the function has access to private members.
	friend std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve);

	int testeBezier();
private:

	// class data:
	std::vector<Vec3f> controlPoints;

};

// ostream << operator. E.g. use "std::cout << bezierCurve << std::endl;"
std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve);

#endif