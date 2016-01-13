#define RADPERDEG 0.0174533

#include "HalfEdgeDSRendering.h"

#include <GL/glut.h>

void renderDS(const HalfEdgeDS& heDS)
{
	for (auto const *v : heDS.getVertices()) renderV(v); // render all vertices as points
	for (auto const *e : heDS.getEdges()) renderE(e); // render all edges as lines
}

void renderE(const Edge* e, const Vec3f& color /*= Vec3f(0.0f, 1.0f, 0.0f)*/)
{
	if (!e || !e->he1 || !e->he2) return;

	// render bezier curve if it has at least two control points
	BezierCurve bezierCurve = e->bezierCurve;
	if (bezierCurve.getControlPoints().size() > 1)
	{

		// TODO: implement the visualization of the bezier curve (e.g. with GL_LINE_STRIP)
		// ===============================================================================

		// ===============================================================================
	}
	// no bezier control points available: draw straight line
	else
	{
		Vec3f& p1 = e->he1->startV->coordinates;
		Vec3f& p2 = e->he2->startV->coordinates;
		glBegin(GL_LINES);
		glColor3fv(&color.x);
		glVertex3fv(&p1.x);
		glVertex3fv(&p2.x);
		glEnd();
	}
}

void renderV(const Vertex* v, const Vec3f& color /*= Vec3f(1.0f, 0.0f, 1.0f)*/)
{
	if (!v) return;
	glBegin(GL_POINTS);
	glColor3fv(&color.x);
	glVertex3fv(&v->coordinates.x);
	glEnd();
}


void renderHEArrow(const HalfEdge* he)
{
	if (!he || !he->startV || !he->nextHE || !he->nextHE->startV) return;
	Vec3f& p1 = he->startV->coordinates;
	Vec3f& p2 = he->nextHE->startV->coordinates;
	Vec3f dir = p2 - p1;
	float diameter = dir.length() / 40.0f;
	glColor3f(1.0f, 0.0f, 0.0f);
	renderArrow(p1 + 0.15f * dir, p2 - 0.15f * dir, diameter);
}

void renderHEBezierEvaluation(const HalfEdge* he, float t)
{
	if (!he || !he->toEdge) return;
	BezierCurve bezierCurve = he->toEdge->bezierCurve;
	if (bezierCurve.getControlPoints().size() > 1)
	{
		auto twoBezierCurves = bezierCurve.separateCurveAt(t);
		// first partial curve cps		
		auto& cps = twoBezierCurves.first.getControlPoints();
		glColor3f(0.8f, 0.0f, 0.4f);
		glBegin(GL_LINE_STRIP);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
		glBegin(GL_POINTS);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
		// second partial curve cps
		cps = twoBezierCurves.second.getControlPoints();
		glColor3f(0.4f, 0.0f, 0.8f);
		glBegin(GL_LINE_STRIP);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
		glBegin(GL_POINTS);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
		// cps of the complete curve
		cps = bezierCurve.getControlPoints();
		glColor3f(0.3f, 0.7f, 0.7f);
		glBegin(GL_LINE_STRIP);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
		glBegin(GL_POINTS);
		for (auto& cp : cps)
			glVertex3fv(&cp.x);
		glEnd();
	}
	
}

void renderArrow(const Vec3f& p1, const Vec3f& p2, float diameter)
{
	Vec3f dir = p2 - p1;
	float length = dir.length();
	if (length < 0.00001f) return;

	GLUquadricObj *quadObj;

	glPushMatrix ();

	glTranslated(p1.x, p1.y, p1.z);

	if((dir.x!=0.)||(dir.y!=0.)) {
		glRotated(atan2(dir.y,dir.x)/RADPERDEG,0.,0.,1.);
		glRotated(atan2(sqrt(dir.x*dir.x+dir.y*dir.y),dir.z)/RADPERDEG,0.,1.,0.);
	} else if (dir.z<0){
		glRotated(180,1.,0.,0.);
	}

	glTranslatef(0,0,length-4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, 2*diameter, 0.0, 4*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, 2*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glTranslatef(0,0,-length+4*diameter);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, diameter, diameter, length-4*diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	quadObj = gluNewQuadric ();
	gluQuadricDrawStyle (quadObj, GLU_FILL);
	gluQuadricNormals (quadObj, GLU_SMOOTH);
	gluDisk(quadObj, 0.0, diameter, 32, 1);
	gluDeleteQuadric(quadObj);

	glPopMatrix ();
}
