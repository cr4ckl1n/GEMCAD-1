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
	std::cout << heDS << std::endl << std::endl;
	if (heDS.getHalfEdges().size() > 0) activeHE = heDS.getHalfEdges().front();
	else activeHE = nullptr;
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
}

void initializeGL()
{
	// black screen
	glClearColor(0, 0, 0, 0);
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);
	// Use Point Smoothing
	glPointSize(5.0f);
	glLineWidth(2.0f);
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
	renderHEActive(activeHE);
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
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	//previous half edge
	case 'p' :
	case 'P' :
		activeHE = activeHE->prevHE;
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		//opposite half edge
	case 'g' :
	case 'G' :
		if(activeHE==activeHE->toEdge->he1){
			activeHE = activeHE->toEdge->he2;
	}else
		{
			activeHE = activeHE->toEdge->he1;
	}
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	
	

	case 'i' :
	case 'I' :
		if(activeHE->toLoop->toFace->innerLoop != NULL){
			activeHE = activeHE->toEdge->he1->toLoop->toFace->innerLoop->toHE;
	}
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	
	case 'o' :
	case 'O' :
			if(activeHE->toEdge->he1->toLoop->toFace->outerLoop != NULL){
			activeHE = activeHE->toEdge->he1->toLoop->toFace->outerLoop->toHE;

			}
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	
	
   case 's' :
	case 'S' :
		MEVVLS* mevvls = new MEVVLS;

	mevvls->coordinates_1 = Vec3f(3.0f, 3.0f,3.0f);
	mevvls->coordinates_2 = Vec3f(4.0, 4.0, 4.0);
	mevvls->newV1 = new Vertex;
	mevvls->newV2 = new Vertex;
	mevvls->newV1->coordinates = mevvls->coordinates_1;
	mevvls->newV2->coordinates = mevvls->coordinates_2;
	
	mevvls->newHe1 = new HalfEdge;
	mevvls->newHe2 = new HalfEdge;
	mevvls->newE1 = new Edge;
	mevvls->newL1 = new Loop;
	mevvls->newF1 = new Face;

	mevvls->newHe1->startV = mevvls->newV1;
	mevvls->newHe1->nextHE = mevvls->newHe2;
	mevvls->newHe1->prevHE = mevvls->newHe2;
	mevvls->newV1->outgoingHE = mevvls->newHe1;

	mevvls->newV1->outgoingHE = mevvls->newHe1;
	mevvls->newV2->outgoingHE = mevvls->newHe2;

	mevvls->newHe2->startV = mevvls->newV2;
	mevvls->newHe2->nextHE = mevvls->newHe1;
	mevvls->newHe2->prevHE = mevvls->newHe1;
	mevvls->newV2->outgoingHE = mevvls->newHe2;

	mevvls->newHe1->toEdge = mevvls->newE1;
	mevvls->newHe2->toEdge = mevvls->newE1;
	mevvls->newHe1 ->toLoop = mevvls->newL1;
	mevvls->newHe2 ->toLoop = mevvls->newL1;

	mevvls->newE1->he1 = mevvls->newHe1;
	mevvls->newE1->he2 = mevvls->newHe2;

	mevvls->newL1 ->toFace = mevvls->newF1;
	mevvls->newL1 ->toHE = mevvls->newHe1;

	mevvls->newF1 -> toShell = mevvls->newS1;
	mevvls->newF1 -> outerLoop = mevvls->newL1;

	mevvls->newS1 = new Solid;
	
	mevvls->newS1 ->toFace = mevvls->newF1;

	

		// V-E+F+2R-2S = H

		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	
	


		/*/
	case 'e' :
	case 'E' :
		MEL* mel = new MEL();
		if(mel->oldV1== mel->oldV2){
		
	}


else{
		
		//umhängen neue Elemente
		mel->newE -> he1= mel->newHe1;
		mel->newE -> he2= mel->newHe2;

		mel->newHe1 ->startV = mel->oldV1;
		mel->newHe2 ->startV = mel->oldV2;
		mel->newHe1 ->toEdge = mel->newE;
		mel->newHe2 ->toEdge = mel->newE;
		mel->newHe1 ->nextHE = mel->oldV2->outgoingHE;
		mel->newHe2 ->nextHE = mel->oldV1->outgoingHE;
		mel->newHe1 ->prevHE = mel->oldV1->outgoingHE->prevHE;
		mel->newHe2 ->prevHE = mel->oldV2->outgoingHE->prevHE;

		mel->newHe1 ->toLoop = mel->oldL;
		mel->newHe2 ->toLoop = mel->newL;

		mel->newL ->toFace = mel->newF;
		mel->newL ->toHE = mel->newHe2;

		mel->newF ->outerLoop = mel->newL;

		//umhängen alte Elemente
		mel->oldV1 ->outgoingHE ->prevHE = mel->newHe2;
		mel->oldV2  ->outgoingHE ->prevHE =mel->newHe1;
		mel->oldV1 ->outgoingHE ->toLoop = mel->newL;
		mel->oldV2 ->outgoingHE ->toLoop = mel->oldL;
		mel->oldV1 ->outgoingHE ->prevHE ->nextHE = mel->newHe1;
		mel->oldV2 ->outgoingHE ->prevHE ->nextHE = mel->newHe2;

		mel->oldV1 ->outgoingHE ->prevHE ->toLoop = mel->newL;
		mel->oldV2 ->outgoingHE ->prevHE ->toLoop = mel->newL;

	mel->newF ->outerLoop = mel->newL;
		
}
glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	case 'k':
	case 'K':
		MEKH* mekh = new MEKH;
		if (mekh->v1==nullptr || mekh->v2==nullptr || mekh->l1==nullptr || mekh->l2==nullptr){
}

if(mekh->v1==mekh->v2){
		
}

if(mekh->l1==mekh->l2){
}
	
else{
	
	mekh->newE1 ->he1=mekh->newHe1;
	mekh->newE1 ->he2=mekh->newHe2;

	//zweite Pointer
	Vertex* v1a = mekh->v1;
	Vertex* v2a = mekh->v2;


	mekh->newHe1 ->startV=v1a;
	mekh->newHe2 ->startV=v2a;
	mekh->newHe1 ->nextHE =v2a->outgoingHE;
	mekh->newHe2 ->nextHE = v1a->outgoingHE;
	mekh->newHe1 ->prevHE = v1a->outgoingHE->prevHE;
	mekh->newHe2 ->prevHE = v2a->outgoingHE->prevHE;

	mekh->newHe1 ->toEdge = mekh->newE1;
	mekh->newHe2 ->toEdge = mekh->newE1;
	mekh->newHe1 ->toLoop = mekh->l1;
	mekh->newHe2 ->toLoop = mekh->l1;

	mekh->v2 ->outgoingHE->prevHE = mekh->newHe1;
	v2a ->outgoingHE->prevHE -> nextHE = mekh->newHe2;
	mekh->v1 ->outgoingHE ->prevHE=mekh->newHe2;
	v1a ->outgoingHE ->prevHE->nextHE=mekh->newHe1;

	for (auto *p : halfEdges){
		p ->toLoop=mekh->l1;
	}

	mekh->l1 ->nextLoop=mekh->l1;
	mekh->l1 ->toFace->innerLoop=nullptr;

		halfEdges.push_back(mekh->newHe1);
		halfEdges.push_back(mekh->newHe2);
		edges.push_back(mekh->newE1);
		loops.push_back(mekh->L1);



}
glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
		/*/
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
	std::cout << "P: (P)revious half edge" << std::endl;
	std::cout << "V: half edge (V)is-à-vis" << std::endl;
	std::cout << "O: (O)uter loop jump" << std::endl;
	std::cout << "I: (I)nner loop jump" << std::endl;
	std::cout << "S: Make Edge Vertex Vertex Loop (S)olid (doesn't work)" << std::endl;
	std::cout << "K: Make Edge (K)ill Hole (doesn't work)"  << std::endl;
	std::cout << "E: Make (E)dge Loop(doesn't work)" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << std::endl;
}