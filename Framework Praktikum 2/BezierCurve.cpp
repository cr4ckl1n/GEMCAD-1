#include "BezierCurve.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

BezierCurve::BezierCurve()
{
}

BezierCurve::BezierCurve(const std::vector<Vec3f>& controlPoints_)
	: controlPoints(controlPoints_)
{
}

std::pair<Vec3f, Vec3f> BezierCurve::evaluateCurveAt(const float t)
{
	// separate the curves. it is no overhead, since it is done within de Casteljau anyway
	auto seperatedCurve = separateCurveAt(t);
	// extract point and tangent
	size_t nrCps1 = seperatedCurve.first.getControlPoints().size();
	size_t nrCps2 = seperatedCurve.second.getControlPoints().size();
	Vec3f point;
	if (nrCps1 >= 1) point = seperatedCurve.first.getControlPoints().back();
	Vec3f tangent;	
	if (nrCps1 >= 2 && nrCps2 >= 2) tangent = seperatedCurve.second.getControlPoints()[1] - seperatedCurve.first.getControlPoints()[nrCps1 - 2];
	return std::pair<Vec3f, Vec3f>(point, tangent);
}

std::pair<std::vector<Vec3f>, std::vector<Vec3f>> BezierCurve::evaluateCurveAt(const std::vector<float>& T)
{
	std::vector<Vec3f> points;
	points.reserve(T.size());
	std::vector<Vec3f> tangents;
	tangents.reserve(T.size());
	for (auto t : T)
	{
		auto evaluatedCurve = evaluateCurveAt(t);
		points.push_back(evaluatedCurve.first);
		tangents.push_back(evaluatedCurve.second);
	}
	return std::pair<std::vector<Vec3f>, std::vector<Vec3f>>(points, tangents);
}

std::pair<std::vector<Vec3f>, std::vector<Vec3f>> BezierCurve::evaluateCurveAt(const size_t numberSamples)
{
	std::vector<float> T;
	T.reserve(numberSamples);
	float deltaT = 1.0f;
	if (numberSamples > 1) deltaT = 1.0f / (float(numberSamples) - 1.0f);
	for (size_t i = 0; i < numberSamples; ++i)
	{
		T.push_back(float(i) * deltaT);
	}
	return evaluateCurveAt(T);
}

std::pair<BezierCurve, BezierCurve> BezierCurve::separateCurveAt(const float t)
{
	std::vector<Vec3f> cps1, cps2;
	cps1.reserve(controlPoints.size());	
	cps2.reserve(controlPoints.size());
	
    float u=t;
    int n=3;
    Vec3f Q[10];
    
    for(int i=0;i<=n;++i){
        Q[i]=getControlPoints().at(i);
    }
    
    cps1.push_back(Q[0]);
    cps2.push_back(Q[n]);
    
    for (int k=1; k<=n; ++k) {
        
        for (int i=0; i<=n-k; ++i) {
            Q[i][0]=(1.0-u) * Q[i][0] + u*Q[i+1][0];
            Q[i][1]=(1.0-u) * Q[i][1] + u*Q[i+1][1];
            Q[i][2]=(1.0-u) * Q[i][2] + u*Q[i+1][2];
        }
        cps1.push_back(Q[0]);
        cps2.push_back(Q[n-k]);
	}
	BezierCurve curve1(cps1);
	BezierCurve curve2(cps2);
	return std::pair<BezierCurve, BezierCurve>(curve1, curve2);
}

std::ostream& operator<< (std::ostream& os, BezierCurve& bezierCurve)
{
	if (bezierCurve.controlPoints.empty())
	{
		os << "Bezier curve without control points!";
		return os;
	}
	// degree
	os << "Bezier curve, degree " << bezierCurve.controlPoints.size() - 1 << "\n";
	// control points
	for (size_t i = 0; i < bezierCurve.controlPoints.size(); i++) os << "  " << bezierCurve.controlPoints[i] << std::endl;
	return os;
}
