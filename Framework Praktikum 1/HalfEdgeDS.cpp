#include "HalfEdgeDS.h"

#include <stdio.h>		// cout
#include <iostream>		// cout

HalfEdgeDS::HalfEdgeDS()
{
	clearDS();
	createDefaultObject();
}	

HalfEdgeDS::~HalfEdgeDS()
{
	clearDS();
}

void HalfEdgeDS::createDefaultObject()
{
	// care: for every "new" we need a "delete". if an element is added to the according list, it is deleted automatically within clearDS().

	// create elements. 	
	Vertex* v1 = new Vertex;
	Vertex* v2 = new Vertex;
    Vertex* v3 = new Vertex;
	Vertex* v4 = new Vertex;
	Vertex* v5 = new Vertex;
	Vertex* v6 = new Vertex;
    Vertex* v7 = new Vertex;
	Vertex* v8 = new Vertex;
	Vertex* v9 = new Vertex;
	Vertex* v10 = new Vertex;
	HalfEdge* he1 = new HalfEdge;
	HalfEdge* he2 = new HalfEdge;
	HalfEdge* he3 = new HalfEdge;
	HalfEdge* he4 = new HalfEdge;
	HalfEdge* he5 = new HalfEdge;
	HalfEdge* he6 = new HalfEdge;
	HalfEdge* he7 = new HalfEdge;
	HalfEdge* he8 = new HalfEdge;
	HalfEdge* he9 = new HalfEdge;
	HalfEdge* he10 = new HalfEdge;
	HalfEdge* he11 = new HalfEdge;
	HalfEdge* he12 = new HalfEdge;
	HalfEdge* he13 = new HalfEdge;
	HalfEdge* he14 = new HalfEdge;
	HalfEdge* he15 = new HalfEdge;
	HalfEdge* he16 = new HalfEdge;
	HalfEdge* he17 = new HalfEdge;
	HalfEdge* he18 = new HalfEdge;
	HalfEdge* he19 = new HalfEdge;
	HalfEdge* he20 = new HalfEdge;
	HalfEdge* he21 = new HalfEdge;
	HalfEdge* he22 = new HalfEdge;
	HalfEdge* he23 = new HalfEdge;
	HalfEdge* he24 = new HalfEdge;
	HalfEdge* he25 = new HalfEdge;
	HalfEdge* he26 = new HalfEdge;
	HalfEdge* he27 = new HalfEdge;
	HalfEdge* he28 = new HalfEdge;
	HalfEdge* he29 = new HalfEdge;
	HalfEdge* he30 = new HalfEdge;
	Edge* e1 = new Edge;
	Edge* e2 = new Edge;
	Edge* e3 = new Edge;
	Edge* e4 = new Edge;
	Edge* e5 = new Edge;
	Edge* e6 = new Edge;
	Edge* e7 = new Edge;
	Edge* e8 = new Edge;
	Edge* e9 = new Edge;
	Edge* e10 = new Edge;
	Edge* e11 = new Edge;
	Edge* e12 = new Edge;
	Edge* e13 = new Edge;
	Edge* e14 = new Edge;
	Edge* e15 = new Edge;

	Loop* l1 = new Loop;
	Loop* l2 = new Loop;
	Loop* l3 = new Loop;
	Loop* l4 = new Loop;
	Loop* l5 = new Loop;
	Loop* l6 = new Loop;
	Loop* l7 = new Loop;
	Loop* l8 = new Loop;
	Loop* l9 = new Loop;

	Face* f1 = new Face;
	Face* f2 = new Face;
	Face* f3 = new Face;
	Face* f4 = new Face;
	Face* f5 = new Face;
	Face* f6 = new Face;
	Face* f7 = new Face;



	// set up connections
	v1->coordinates = Vec3f(0.0f, 0.0f, 0.0f);
	v2->coordinates = Vec3f(0.0f, 3.0f, 0.0f);
	v3->coordinates = Vec3f(3.0f, 0.0f, 0.0f);
	v4->coordinates = Vec3f(3.0f, 3.0f, 3.0f);
	v5->coordinates = Vec3f(1.5f, 1.0f, 1.0f);
	v6->coordinates = Vec3f(1.7f, 1.5f, 1.5f);
	v7->coordinates = Vec3f(2.2f, 1.0f, 1.0f);
	v8->coordinates = Vec3f(0.5f, 1.0f, 0.0f);
	v9->coordinates = Vec3f(0.7f, 1.5f, 0.0f);
	v10->coordinates = Vec3f(1.2f, 1.0f, 0.0f);
	
	// Erstellen des Tetraeder

	he1->startV = v1;
	he1->nextHE = he2;
	he1->prevHE = he12;
	
	he2->startV = v2;
	he2->nextHE = he3;
	he2->prevHE = he1;

	he3->startV = v3;
	he3->nextHE = he4;
	he3->prevHE = he2;

	he4->startV = v1;
	he4->nextHE = he5;
	he4->prevHE = he3;

	he5->startV = v4;
	he5->nextHE = he6;
	he5->prevHE = he4;

	he6->startV = v1;
	he6->nextHE = he7;
	he6->prevHE = he5;

	he7->startV = v3;
	he7->nextHE = he8;
	he7->prevHE = he6;
	
	he8->startV = v4;
	he8->nextHE = he9;
	he8->prevHE = he7;	

	he9->startV = v3;
	he9->nextHE = he10;
	he9->prevHE = he8;

	he10->startV = v2;
	he10->nextHE = he11;
	he10->prevHE = he9;

	he11->startV = v4;
	he11->nextHE = he12;
	he11->prevHE = he10;

	he12->startV = v2;
	he12->nextHE = he1;
	he12->prevHE = he11;
	
	e1->he1 = he1;
	e1->he2 = he12;
	he1->toEdge = e1;
	he12->toEdge = e1;

	e2->he1 = he2;
	e2->he2 = he9;
	he2->toEdge = e2;
	he9->toEdge = e2;

	e3->he1 = he3;
	e3->he2 = he6;
	he3->toEdge = e3;
	he6->toEdge = e3;

	e4->he1 = he4;
	e4->he2 = he5;
	he4->toEdge = e4;
	he5->toEdge = e4;

	e5->he1 = he7;
	e5->he2 = he8;
	he7->toEdge = e5;
	he8->toEdge = e5;
	
	e6->he1 = he10;
	e6->he2 = he11;
	he10->toEdge = e6;
	he11->toEdge = e6;

	he1->toLoop = l1  ;
	he2->toLoop = l1;
	he3->toLoop = l1;
	l1->toHE = he1;
	l1->toFace = f4;

	he6->toLoop = l2;
	he7->toLoop = l2;
	he5->toLoop = l2;
	l2->toHE = he3;
	l2->toFace = f3;

	he2->toLoop = l3;
	he7->toLoop = l3;
	he11->toLoop = l3;
	l3->toHE = he8;
	l3->toFace = f2;

	he1->toLoop = l4;
	he10->toLoop = l4;
	he5->toLoop = l4;
	l4->toHE = he10;
	l4->toFace = f1;

	f4->outerLoop = l1;
	f3->outerLoop = l2;
	f2->outerLoop = l3;
	f1->outerLoop = l4;

	// Erstellen des Durchbruchs
	
	he13->startV = v5;
	he13->nextHE = he14;
	he13->prevHE = he30;

	he14->startV = v6;
	he14->nextHE = he15;
	he14->prevHE = he13;

	he15->startV = v7;
	he15->nextHE = he16;
	he15->prevHE = he14;
	
	he16->startV = v5;
	he16->nextHE = he17;
	he16->prevHE = he15;

	he17->startV = v7;
	he17->nextHE = he18;
	he17->prevHE = he16;

	he18->startV = v6;
	he18->nextHE = he19;
	he18->prevHE = he17;
	
	he19->startV = v5;
	he19->nextHE = he20;
	he19->prevHE = he18;

	he20->startV = v8;
	he20->nextHE = he21;
	he20->prevHE = he19;

	he21->startV = v9;
	he21->nextHE = he22;
	he21->prevHE = he20;
	
	he22->startV = v6;
	he22->nextHE = he23;
	he22->prevHE = he21;

	he23->startV = v9;
	he23->nextHE = he24;
	he23->prevHE = he22;

	he24->startV = v10;
	he24->nextHE = he25;
	he24->prevHE = he23;
		
	he25->startV = v7;
	he25->nextHE = he26;
	he25->prevHE = he24;

	he26->startV = v10;
	he26->nextHE = he27;
	he26->prevHE = he25;

	he27->startV = v8;
	he27->nextHE = he28;
	he27->prevHE = he26;

	he28->startV = v10;
	he28->nextHE = he29;
	he28->prevHE = he27;

	he29->startV = v9;
	he29->nextHE = he30;
	he29->prevHE = he28;

	he30->startV = v8;
	he30->nextHE = he13;
	he30->prevHE = he29;

	e7->he1 = he13;
	e7->he2 = he18;
	he13->toEdge = e7;
	he18->toEdge = e7;

	e8->he1 = he14;
	e8->he2 = he17;
	he14->toEdge = e8;
	he17->toEdge = e8;

	e9->he1 = he15;
	e9->he2 = he16;
	he16->toEdge = e9;
	he15->toEdge = e9;


	e10->he1 = he19;
	e10->he2 = he30;
	he19->toEdge = e10;
	he30->toEdge = e10;

	e11->he1 = he20;
	e11->he2 = he29;
	he20->toEdge = e11;
	he29->toEdge = e11;

	e12->he1 = he22;
	e12->he2 = he21;
	he21->toEdge = e12;
	he22->toEdge = e12;


	e13->he1 = he23;
	e13->he2 = he28;
	he23->toEdge = e13;
	he28->toEdge = e13;

	e14->he1 = he24;
	e14->he2 = he25;
	he24->toEdge = e14;
	he24->toEdge = e14;

	e15->he1 = he26;
	e15->he2 = he27;
	he26->toEdge = e15;
	he27->toEdge = e15;

	he13->toLoop = l5;
	he14->toLoop = l5;
	he15->toLoop = l5;
	l5->toHE = he13;
	l5->toFace = f4;

	he20->toLoop = l6 ;
	he23->toLoop = l6;
	he26->toLoop = l6;
	l6->toHE = he20;
	l6->toFace = f1;

	he22->toLoop = l7;
	he23->toLoop = l7;
	he24->toLoop = l7;
	he17->toLoop = l7;
	l7->toHE = he22;
	l7->toFace = f5;

	he19->toLoop = l8;
	he27->toLoop = l8;
	he24->toLoop = l8;
	he15->toLoop = l8;
	l8->toHE = he19;
	l8->toFace = f6;
	
	he22->toLoop = l9;
	he29->toLoop = l9;
	he30->toLoop = l9;
	he13->toLoop = l9;
	l9->toHE = he29;
	l9->toFace = f7;

	f4->innerLoop = l5;
	f1->innerLoop = l6;
	f5->outerLoop = l7;
	f6->outerLoop = l8;
	f7->outerLoop = l9;


	// add elements to the lists
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);
	vertices.push_back(v9);
	vertices.push_back(v10);
	
	halfEdges.push_back(he1);
	halfEdges.push_back(he2);
	halfEdges.push_back(he3);
	halfEdges.push_back(he4);
	halfEdges.push_back(he5);
	halfEdges.push_back(he6);
	halfEdges.push_back(he7);
	halfEdges.push_back(he8);
	halfEdges.push_back(he9);
	halfEdges.push_back(he10);
	halfEdges.push_back(he11);
	halfEdges.push_back(he12);
	halfEdges.push_back(he13);
	halfEdges.push_back(he14);
	halfEdges.push_back(he15);
	halfEdges.push_back(he16);
	halfEdges.push_back(he17);
	halfEdges.push_back(he18);
	halfEdges.push_back(he19);
	halfEdges.push_back(he20);
	halfEdges.push_back(he21);
	halfEdges.push_back(he22);
	halfEdges.push_back(he23);
	halfEdges.push_back(he24);
	halfEdges.push_back(he25);
	halfEdges.push_back(he26);
	halfEdges.push_back(he27);
	halfEdges.push_back(he28);
	halfEdges.push_back(he29);
	halfEdges.push_back(he30);

	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);
	edges.push_back(e5);
	edges.push_back(e6);
	edges.push_back(e7);
	edges.push_back(e8);
	edges.push_back(e9);
	edges.push_back(e10);
	edges.push_back(e11);
	edges.push_back(e12);
	edges.push_back(e13);
	edges.push_back(e14);
	edges.push_back(e15);


	loops.push_back(l1);
	loops.push_back(l2);
	loops.push_back(l3);
	loops.push_back(l4);
	loops.push_back(l5);
	loops.push_back(l6);
	loops.push_back(l7);
	loops.push_back(l8);
	loops.push_back(l9);

	faces.push_back(f1);
	faces.push_back(f2);
	faces.push_back(f3);
	faces.push_back(f4);
	faces.push_back(f5);
	faces.push_back(f6);
	faces.push_back(f7);
	
	
	


	// TODO: Erstellen Sie ein valides Testobjekt mit allen topologischen Elementen und Verknüpfungen. Dieses Objekt sollte volumetrisch sein und mindestens ein Loch besitzen.
}


void HalfEdgeDS::clearDS()
{
	// for every "new" in this code, we need to call delete. take care, that you delete ALL elements
	for (auto *p : vertices) delete p;
	vertices.clear();
	for (auto *p : halfEdges) delete p;
	halfEdges.clear();
	for (auto *p : edges) delete p;
	edges.clear();
	for (auto *p : loops) delete p;
	loops.clear();
	for (auto *p : faces) delete p;
	faces.clear();
	for (auto *p : solids) delete p;
	solids.clear();
}

std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds)
{

	
	os << "Elements in the lists of the data structure:" << std::endl;
	os << "  " << ds.solids.size() << " solids, "
		<< ds.faces.size() << " faces, "
		<< ds.loops.size() << " loops, "
		<< ds.edges.size() << " edges, "
		<< ds.halfEdges.size() << " halfEdges, "
		<< ds.vertices.size() << " vertices.";
	return os;
}