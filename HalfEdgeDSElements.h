// ========================================================================= //
// Authors: Matthias Borner                                                  //
// mailto:matthias.borner@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef HALF_EDGE_DS_ELEMENTS_H
#define HALF_EDGE_DS_ELEMENTS_H

#include "Vec3.h"		// vector (x, y, z)

// forward declarations, so elements know each other when defined further below
struct Solid;
struct Face;
struct Loop;
struct Edge;
struct HalfEdge;
struct Vertex;
struct MEVVLS;

// data structure elements. this is an minimal extract of the data structure presented in the slides.
// we skip identifiers and pointers to unsorted lists of elements.
// by default all pointers are initialized with nullptr, so you can use "if (some_solid->toFace)" to check, if the pointer is set.
struct Solid
{
	Face* toFace;			// can be any face of the solid
	Solid()
		: toFace(nullptr)
	{
	}
};

struct Face
{
	Solid* toShell;			// back to the solid
	Loop* outerLoop;		// to the boundary of the face
	Loop* innerLoop;		// to a possible hole. Can be null_ptr. Multiple holes are accessible through innerLoop->nextLoop.
	Face()
		: toShell(nullptr)
		, outerLoop(nullptr)
		, innerLoop(nullptr)
	{
	}
};

struct Loop
{
	Face* toFace;			// back to the face
	Loop* nextLoop;			// next inner loop. cyclic: points to itself, if there is no other loop.
	Loop* prevLoop;			// previous inner loop. cyclic: points to itself, if there is no other loop.
	HalfEdge* toHE;			// can be any half edge of the loop
	Loop()
		: toFace(nullptr)
		, nextLoop(nullptr)
		, prevLoop(nullptr)
		, toHE(nullptr)
	{
	}
};

struct Edge
{
	HalfEdge* he1;
	HalfEdge* he2;
	Edge()
		: he1(nullptr)
		, he2(nullptr)
	{
	}
};

struct HalfEdge
{
	Loop* toLoop;			// back to the loop
	Edge* toEdge;			// back to the parent edge
	HalfEdge* nextHE;		// next half edge
	HalfEdge* prevHE;		// previous half edge
	Vertex* startV;			// vertex at the tail of the half edge
	HalfEdge()
		: toLoop(nullptr)
		, toEdge(nullptr)
		, nextHE(nullptr)
		, prevHE(nullptr)
		, startV(nullptr)
	{
	}
};

struct Vertex
{
	HalfEdge* outgoingHE;	// can be any outgoing half edge
	Vec3f coordinates;		// stores the 3d coordinates of the vertex
	Vertex()
		: outgoingHE(nullptr)
		, coordinates(Vec3f())
	{
	}
};


struct MEVVLS
{
	Vec3f coordinates_1 ;
	Vec3f coordinates_2;
	Vertex* newV1;
	Vertex* newV2; 
	HalfEdge* newHe1; 
	HalfEdge* newHe2; 
	Edge* newE1; 
	Loop* newL1; 
	Face* newF1; 
	Solid* newS1;
		MEVVLS()
			:coordinates_1(Vec3f())
			,coordinates_2(Vec3f())
			,newV1(nullptr)
			,newV2(nullptr)
			,newHe1(nullptr)
			,newHe2(nullptr)
			,newE1(nullptr)
			,newL1(nullptr)
			,newF1(nullptr)
			,newS1(nullptr)

		{
			//(Vec3f(0.0f, 0.0f,0.0f),Vec3f(0.0f, 0.0f,0.0f),v1, v2, hE1,  hE2, e1, l1, f1, s1)

		};

			

	
	~MEVVLS();
};
struct MEL {

	Vertex* oldV1;
	Vertex* oldV2;
	Loop* oldL;
	HalfEdge* newHe1;
	HalfEdge* newHe2;
	Edge* newE; 
	Loop* newL; 
	Face* newF;
		MEL()
			:oldV1(nullptr)
			,oldV2(nullptr)
			,oldL(nullptr)
			,newHe1(nullptr)
			,newHe2(nullptr)
			,newE(nullptr)
			,newL(nullptr)
			,newF(nullptr)
		{
		};
		~MEL();
};

struct MEKH {
	Vertex* v1;
	Vertex* v2;
	Loop* l1;
	Loop* l2; 
	HalfEdge* newHe1; 
	HalfEdge* newHe2; 
	Edge* newE1;
		MEKH()
			:v1(nullptr)
			,v2(nullptr)
			, l1(nullptr)
			,l2(nullptr)
			, newHe1(nullptr)
			, newHe2(nullptr)
			, newE1(nullptr)
		{


		};
		~MEKH();

};


#endif