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

#include <vector>

#include "Vec3.h"
#include "BezierCurve.h"

// forward declarations, so elements know each other when defined further below
struct Solid;
struct Shell;
struct Face;
struct Loop;
struct Edge;
struct HalfEdge;
struct Vertex;

// data structure elements. this is an minimal extract of the data structure presented in the slides.
// we skip identifiers and pointers to unsorted lists of elements.
// by default all pointers are initialized with nullptr, so you can use "if (some_solid->toFace)" to check, if the pointer is set.
// care: the set functions do not modify its adjacent elements! this has to be done manually.

struct Solid
{
	size_t ID;				// user chosen integer identification
	Shell* outerShell;		// there is only one outer shell
	Shell* innerShell;		// there can be multiple inner shells. Access by next and prev of shell struct.

	// empty constructor which initializes all pointers with nullptr
	Solid();

	// first shell is the outer one, other ones are inner shells
	void addShell(Shell* shell);

	// removes the shell from the solid. Care! Does not change pointers of the sub elements of the shell.
	bool removeShell(Shell* shell);
};

struct Shell
{
	size_t ID;				// user chosen integer identification
	Solid* toSolid;			// back to the solid
	Shell* nextShell;		// next inner shell. cyclic: points to itself, if there is no other shell.
	Shell* prevShell;		// previous inner shell. cyclic: points to itself, if there is no other shell.
	Face* toFace;			// can be any face of the solid

	// empty constructor which initializes all pointers with nullptr
	Shell();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(Solid* toSolid_, Shell* nextShell_, Shell* prevShell_, Face* toFace_);

	// appends a shell to the double linked list behind this shell
	void addShell(Shell* shell);

	// removes itself from the double linked list. does nothing if it is the only shell in the list.
	void removeShell();

	// iterate through all shells of the solid of this shell, no matter if this shell is a inner or outer one.
	Shell* nextShellInSolid();
};

struct Face
{
	size_t ID;				// user chosen integer identification
	Shell* toShell;			// back to the shell
	Loop* outerLoop;		// to the boundary of the face
	Loop* innerLoop;		// to a possible hole. Can be null_ptr. Multiple holes are accessible through innerLoop->nextLoop.

	// empty constructor which initializes all pointers with nullptr
	Face();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(Shell* toShell_, Loop* outerLoop_, Loop* innerLoop_);

	// first loop is the outer one, other ones are inner loops
	void addLoop(Loop* loop);

	// returns a list of loops of this face
	std::vector<Loop*> getAllLoops();
};

struct Loop
{
	size_t ID;				// user chosen integer identification
	Face* toFace;			// back to the face
	Loop* nextLoop;			// next inner loop. cyclic: points to itself, if there is no other loop.
	Loop* prevLoop;			// previous inner loop. cyclic: points to itself, if there is no other loop.
	HalfEdge* toHE;			// can be any half edge of the loop

	// empty constructor which initializes all pointers with nullptr
	Loop();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(Face* toFace_, Loop* nextLoop_, Loop* prevLoop_, HalfEdge* toHE_);

	// appends a loop to the double linked list behind this loop
	void addLoop(Loop* loop);

	// iterate through all loops of the face of this loop, no matter if this loop is a inner or outer one.
	Loop* nextLoopInFace();

	// returns a list of half edges of this loop
	std::vector<HalfEdge*> getAllHalfEdges();

	// returns true, if the loop is a outer loop of its face, else false (then it is a inner loop)
	bool isOuterLoop();
};

struct Edge
{
	size_t ID;				// user chosen integer identification
	HalfEdge* he1;			// one half edge
	HalfEdge* he2;			// the other half edge
	BezierCurve bezierCurve;// geometric representation of the edge as bezier curve
	bool has_bezier;
	// empty constructor which initializes all pointers with nullptr
	Edge();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(HalfEdge* he1_, HalfEdge* he2_);
	void set(const BezierCurve& bezierCurve_);
	void set(HalfEdge* he1_, HalfEdge* he2_, const BezierCurve& bezierCurve);
};

struct HalfEdge
{
	size_t ID;				// user chosen integer identification
	Loop* toLoop;			// back to the loop
	Edge* toEdge;			// back to the parent edge
	HalfEdge* nextHE;		// next half edge
	HalfEdge* prevHE;		// previous half edge
	Vertex* startV;			// vertex at the tail of the half edge

	// empty constructor which initializes all pointers with nullptr
	HalfEdge();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(Loop* toLoop_, Edge* toEdge_, HalfEdge* nextHE_, HalfEdge* prevHE_, Vertex* startV_);

	// returns the opposite half edge
	HalfEdge* oppHE();

	// returns a list of half edges starting with this one, going over the next pointer
	std::vector<HalfEdge*> getAllHalfEdges();

	// overloading the << operator to print our information of the class
	friend std::ostream& operator<< (std::ostream& os, HalfEdge& he);
};

struct Vertex
{
	size_t ID;				// user chosen integer identification
	HalfEdge* outgoingHE;	// can be any outgoing half edge
	Vec3f coordinates;		// stores the 3d coordinates of the vertex

	// empty constructor which initializes all pointers with nullptr
	Vertex();

	// sets the elements. if an element is a nullptr it is ignored in the set routine.
	void set(HalfEdge* outgoingHE_, Vec3f& coordinates_);

	// returns a list of all outgoing half edges of this vertex
	std::vector<HalfEdge*> getAllOutgoingHalfEdges();

	// returns the half edge starting at this vertex in the given loop. returns nullptr if the vertex is not part of the loop.
	HalfEdge* getOutgoingHalfEdgeInLoop(Loop* loop);
};


#endif