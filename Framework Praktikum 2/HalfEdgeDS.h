// ========================================================================= //
// Authors: Matthias Borner                                                  //
// mailto:matthias.borner@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universität Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
// ========================================================================= //

#ifndef HALF_EDGE_DS_H
#define HALF_EDGE_DS_H

#include <stdlib.h>		// standard library
#include <vector>		// std::vector<>
#include <list>			// std::list<>

#include "HalfEdgeDSElements.h"

// Handles creating, verifying and modifying a half edge data structure.
// Also manages memory. Since we heavily rely on raw pointers, we need to use "new" and "delete", else we get memory leaks.
class HalfEdgeDS
{

protected:

	// class members: lists of pointers to the elements. these are unsorted. the next element is not necessarily connected to the previous one.
	// so this class owns all created data structure elements and is responsible for adding new ones and deleting old ones.
	std::list<Solid*> solids;
	std::list<Shell*> shells;
	std::list<Face*> faces;
	std::list<Loop*> loops;
	std::list<Edge*> edges;
	std::list<HalfEdge*> halfEdges;
	std::list<Vertex*> vertices;
	// counters only used to assign each element a unique ID
	size_t cSolids, cShells, cFaces, cLoops, cEdges, cHalfEdges, cVertices;

public:

	// empty constructor which creates an example object
	HalfEdgeDS();

	// deletes the content of the data structure
	~HalfEdgeDS();

	// creates a default example object. state determines how many euler operations are performed
	void createDefaultObject(int state);

	// clears the data structure completely
	void clearDS();

	// getters with read only access, returned as reference, so nothing gets copied
	const std::list<Solid*>& getSolids() const { return solids; }
	const std::list<Shell*>& gethells() const { return shells; }
	const std::list<Face*>& getFaces() const { return faces; }
	const std::list<Loop*>& getLoops() const { return loops; }
	const std::list<Edge*>& getEdges() const { return edges; }
	const std::list<HalfEdge*>& getHalfEdges() const { return halfEdges; }
	const std::list<Vertex*>& getVertices() const { return vertices; }

	// overloading the << operator to print our information of the class. declared as friend, so the function has access to private members.
	friend std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

	// creates new objects which are empty and appends them to the std::list. returns a pointer to the created object
	Solid* createNewSolid();
	Shell* createNewShell();
	Face* createNewFace();
	Loop* createNewLoop();
	Edge* createNewEdge();
	HalfEdge* createNewHalfEdge();
	Vertex* createNewVertex();

	// ============== EULER ==============

	// make edge, two vertices, loop, shell
	// creates a new shell on an existing solid with two positions p1 and p2.
	// new elements are added to the std::list and returned by parameter pointers.
	// does nothing and returns false if there is a problem.
	bool MEVVLS(Solid* solid, Vec3f& p1, Vec3f& p2, Shell** newShell, Face** newFace, Loop** newLoop, Edge** newEdge, Vertex** newVertex1, Vertex** newVertex2);

	// make edge, vertex
	// creates a new edge and vertex and appends it to an existing loop and vertex.
	// new elements are added to the std::list and returned by parameter pointers.
	// does nothing and returns false if there is a problem.
	bool MEV(Loop* loop, Vertex* vertex, Vec3f& p, Edge** newEdge, Vertex** newVertex);

	// make edge, loop
	// creates a new face, loop and edge between vertex1 and vertex2 which have to be in the same loop.
	// new elements are added to the std::list and returned by parameter pointers.
	// does nothing and returns false if there is a problem.
	bool MEL(Loop* loop, Vertex* vertex1, Vertex* vertex2, Face** newFace, Loop** newLoop, Edge** newEdge);

	// kill peripheral loop, make hole loop
	// makes the peripheral loop to a hole loop of the given face
	// does nothing and returns false if there is a problem.
	bool KPMH(Face* face, Loop* peripheralLoop);

	// calculates how many rings the object should have in order for the euler poincare formula to be correct.
	// float is used since for a topological invalid object, the number of rings is not an integer.
	float calculateRingsWithEulerPoincare();

	// ============== TRANSFORMATION ==============

	// rotates the objects around the x axis
	void rotateAllVerticesX(const float angleInRadian);
	// rotates the objects around the y axis
	void rotateAllVerticesY(const float angleInRadian);
	// rotates the objects around the z axis
	void rotateAllVerticesZ(const float angleInRadian);


private:

};

// ostream << operator to print some info of the data structure
std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds);

#endif