#include "main.h"		// this header

#include <stdlib.h>		// standard library
#include <math.h>		// fmod
#include <stdio.h>		// cout
#include <iostream>		// cout

#include "HalfEdgeDSRendering.h"	// visualizing the data structure

// ==============
// === BASICS ===
// ==============

int main(int argc, char** argv)
{
	// initialize openGL window
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TU Darmstadt, MBorner"); 
	// link functions to certain openGL events
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);  
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);
	glutKeyboardFunc(keyPressed);
	// further initializations
	setDefaults();
	initializeGL();
	// data structure stuff
	updateDSStuff();
	// activate main loop
	glutMainLoop();
	return 0;
}

void setDefaults()
{
	// scene Information
	transX = 0.0f;
	transY = 0.0f;
	transZ = -8.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	// mouse information
	mouseX = 0;
	mouseY = 0;
	mouseButton = 0;
	mouseSensitivy = 1.0f;
	// ds
	state = 10;
	evalParameter = 0.5f;
}

void initializeGL()
{
	// black screen
	glClearColor(0, 0, 0, 0);
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);
	// Use Point Smoothing
	glPointSize(7.0f);
	glLineWidth(3.0f);
	// set shading model
	glShadeModel(GL_SMOOTH);
	// set lighting (white light)
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };  
	GLfloat ambientLight[] =   { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseLight[] =   { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess = 0.9f * 128.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightf(GL_LIGHT0, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
	GLfloat lp[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lp);
	// enable lighting by glColor
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// key bindings => cout
	coutHelp();
}

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)width / (float)height, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// =================
// === RENDERING ===
// =================

void renderCS()
{
	// x
	glPushMatrix();
	glColor3f(1, 0, 0); 
	renderArrow(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 0.0f, 0.0f), 0.04f);
	glPopMatrix();
	// y
	glPushMatrix();
	glColor3f(0, 1, 0);
	renderArrow(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f), 0.04f);
	glPopMatrix();
	// z
	glPushMatrix();
	glColor3f(0, 0, 1);
	renderArrow(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f), 0.04f);
	glPopMatrix();
}

void renderScene()
{
	// clear and set camera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// lighting from the viewer perspective
	GLfloat lp[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lp);
	// translate scene in viewing direction
	glTranslatef(transX, transY, transZ);  
	// rotate scene
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);	
	// draw data structure (lines) without lighting
	glDisable(GL_LIGHTING);
	renderDS(heDS);
	// draw 3d objects with lighting
	glEnable(GL_LIGHTING);
	renderHEArrow(activeHE);
	renderHEBezierEvaluation(activeHE, evalParameter);
	renderCS();	
	// swap Buffers
	glFlush();
	glutSwapBuffers();
}

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
		// esc => exit
	case 27:
		exit(0);
		break;
		// help file
	case 'h' :
	case 'H' :
		coutHelp();
		break;
		// reset view
	case 'r' :
	case 'R' :
		setDefaults();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// next half edge
	case 'n' :
	case 'N' :
		activeHE = activeHE->nextHE;
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// prev half edge
	case 'p' :
	case 'P' :
		activeHE = activeHE->prevHE;
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// opp half edge
	case 'o' :
	case 'O' :
		activeHE = activeHE->oppHE();
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// iterate around a (V)ertex
	case 'v' :
	case 'V' :
		activeHE = activeHE->oppHE()->nextHE;
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// iterate through (L)oops
	case 'l' :
	case 'L' :
		activeHE = activeHE->toLoop->nextLoopInFace()->toHE;
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// iterate through (S)hells
	case 's' :
	case 'S' :
		activeHE = activeHE->toLoop->toFace->toShell->nextShellInSolid()->toFace->outerLoop->toHE;
		std::cout << *activeHE << std::endl;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// iterate through (B)odies
	case 'b' :
	case 'B' :
		// NYI
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// numbers starting with 0 (key == 48)
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		state = int(key) - 48;
		heDS.createDefaultObject(state);
		updateDSStuff();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// increase state
	case '+':
		state = std::min(++state, 20);
		heDS.createDefaultObject(state);		
		updateDSStuff();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// decrease state
	case '-':
		state = std::max(1, --state);
		heDS.createDefaultObject(state);		
		updateDSStuff();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// decrease evalParameter
	case ',':
	case ';':
		evalParameter -= 0.05f;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		// increase evalParameter
	case '.':
	case ':':
		evalParameter += 0.05f;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;

		// TODO: implement more transformation calls
		// =========================================

	case 'x':
	case 'X':
		heDS.rotateAllVerticesX(10.0f * M_DegToRad);		
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;		

	case 'y':
	case 'Y':
		heDS.rotateAllVerticesY(10.0f * M_DegToRad);		
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;		

	case 'z':
	case 'Z':
		heDS.rotateAllVerticesY(10.0f * M_DegToRad);		
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;		
			
	case 'm' :
		Matrix4f::test_Multiplikation();
		break;		
		// =========================================

	case 'q' :
		Matrix4f::test_vecMult();
		break;		
		// =========================================



		default:
		std::cout << int(key) << " not bound!" << std::endl;
		break;

		// =========================================

	

	}
}

void mousePressed(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseX = x; 
	mouseY = y;
}

void mouseMoved(int x, int y)
{
	// rotate (cap angleY within [-85°, +85°])
	if (mouseButton == GLUT_LEFT_BUTTON)
	{
		angleX = fmod(angleX + (x-mouseX) * mouseSensitivy, 360.0f);
		angleY += (y-mouseY) * mouseSensitivy;
		if (angleY > 85) angleY = 85;
		if (angleY < -85) angleY = -85;
		glutPostRedisplay();
	}
	// zoom (here translation in z)
	if (mouseButton == GLUT_RIGHT_BUTTON)
	{
		transZ -= 0.2f * (y-mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// translation in xy
	if (mouseButton == GLUT_MIDDLE_BUTTON) 
	{
		transX += 0.2f * (x-mouseX) * mouseSensitivy;
		transY -= 0.2f * (y-mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// update mouse for next relative movement
	mouseX = x;
	mouseY = y;
}

// ===============
// === VARIOUS ===
// ===============

void coutHelp()
{
	std::cout << std::endl;
	std::cout << "====== KEY BINDINGS ======" << std::endl;
	std::cout << "ESC: exit" << std::endl;
	std::cout << "H: show this (H)elp file" << std::endl;
	std::cout << "R: (R)eset view" << std::endl;
	std::cout << "====== DS NAVIGATION =====" << std::endl;
	std::cout << "N: (N)ext half edge" << std::endl;
	std::cout << "P: (P)rev half edge" << std::endl;
	std::cout << "O: (O)pp  half edge" << std::endl;
	std::cout << "V: iterate around a (V)ertex" << std::endl;
	std::cout << "L: iterate through (L)oops" << std::endl;
	std::cout << "S: iterate through (S)hells" << std::endl;
	std::cout << "B: iterate through (B)odies (solids)" << std::endl;
	std::cout << "====== EXAMPLE OBJECTS ====" << std::endl;
	std::cout << "0-9: different states of the object" << std::endl;
	std::cout << "+: increase the state of the object" << std::endl;
	std::cout << "-: decrease the state of the object" << std::endl;
	std::cout << ".: increase the evaluation parameter" << std::endl;
	std::cout << ",: decrease the evaluation parameter" << std::endl;
	std::cout << "====== TRANSFORMATIONS ====" << std::endl;
	std::cout << "X: rotation of the complete object around x axis" << std::endl;
	std::cout << "Y: rotation of the complete object around y axis" << std::endl;
	std::cout << "Z: rotation of the complete object around z axis" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << std::endl;
}

void updateDSStuff()
{
	std::cout << heDS << std::endl;
	if (heDS.getHalfEdges().size() > 0) activeHE = heDS.getHalfEdges().front();
	else activeHE = nullptr;
}
