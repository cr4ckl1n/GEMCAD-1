#include "HalfEdgeDS.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "Matrix4.h"				// transformations

HalfEdgeDS::HalfEdgeDS()
{
	clearDS();
	createDefaultObject(10);
}	

HalfEdgeDS::~HalfEdgeDS()
{
	clearDS();
}

void HalfEdgeDS::createDefaultObject(int state)
{
	
	clearDS();

	// front quad (xy-plane, z = 1.0f)
	//  v3 ----e2---- v2
	//  |             |
	//  e3   l1,f1    e1
	//  |             |
	//  v0 ----e0---- v1
	// l1 is oriented counter clock wise and is the front face.
	// l0 is oriented clock wise and is the back face.
	// l0 is the "open" loop used to create all other faces.
	Shell *s0 = nullptr;
	Face *f0 = nullptr;
	Loop *l0 = nullptr;
	Edge *e0 = nullptr;
	Vertex *v0 = nullptr, *v1 = nullptr;
	Solid *solid = createNewSolid();
	MEVVLS(solid, Vec3f(1.0f, 1.0f, 1.0f), Vec3f(3.0f, 1.0f, 1.0f), &s0, &f0, &l0, &e0, &v0, &v1);

	// example bezier curve edge
	std::vector<Vec3f> cps0;
	cps0.push_back(Vec3f(1.0f, 1.0f, 1.0f));
	cps0.push_back(Vec3f(1.6f, 0.5f, 1.0f));
	cps0.push_back(Vec3f(2.3f, 0.5f, 1.0f));
	cps0.push_back(Vec3f(3.0f, 1.0f, 1.0f));
	BezierCurve bezierCurve1(cps0);
	e0->set(bezierCurve1);
	e0->has_bezier = true;
	

	if (state <= 1) return;
	Edge *e1 = nullptr;
	Vertex* v2 = nullptr;
	MEV(l0, v1, Vec3f(3.0f, 2.0f, 1.0f), &e1, &v2);
	e1->has_bezier = false;
	Edge *e2 = nullptr;
	Vertex* v3 = nullptr;
	MEV(l0, v2, Vec3f(1.0f, 2.0f, 1.0f), &e2, &v3);
	e2->has_bezier = false;
	if (state <= 2) return;
	Face *f1 = nullptr;
	Loop *l1 = nullptr;
	Edge* e3 = nullptr;	
	MEL(l0, v3, v0, &f1, &l1, &e3);
	e3->has_bezier = false;
	if (state <= 3) return;
	
	// bottom quad (xz-plane, y = 1.0f)
	//  v4 ----e5---- v5
	//  |             |
	//  e4   l2,f2    e6
	//  |             |
	//  v0 ----e0---- v1
	// use l0 to create this face
	Edge *e4 = nullptr;
	Vertex* v4 = nullptr;
	MEV(l0, v0, Vec3f(1.0f, 1.0f, -2.0f), &e4, &v4);
	e4->has_bezier = false;
	Edge *e5 = nullptr;
	Vertex* v5 = nullptr;
	MEV(l0, v4, Vec3f(3.0f, 1.0f, -2.0f), &e5, &v5);
	e5->has_bezier = false;
	if (state <= 4) return;
	Face *f2 = nullptr;
	Loop *l2 = nullptr;
	Edge* e6 = nullptr;	
	MEL(l0, v5, v1, &f2, &l2, &e6);
	e6->has_bezier = false;
	if (state <= 5) return;
	
	// left quad (yz-plane, x = 1.0f)
	//  v3 ----e7---- v6
	//  |             |
	//  e3   l3,f3    e8
	//  |             |
	//  v0 ----e4---- v4
	Edge *e7 = nullptr;
	Vertex* v6 = nullptr;
	MEV(l0, v3, Vec3f(1.0f, 2.0f, -2.0f), &e7, &v6);
	e7->has_bezier = false;
	if (state <= 6) return;
	Face *f3 = nullptr;
	Loop *l3 = nullptr;
	Edge* e8 = nullptr;	
	MEL(l0, v6, v4, &f3, &l3, &e8);
	e8->has_bezier = false;
	if (state <= 7) return;
	
	// right quad (yz-plane, x = 3.0f)
	//  v2 ----e10--- v7
	//  |             |
	//  e1   l4,f4    e9
	//  |             |
	//  v1 ----e6---- v5
	Edge *e9 = nullptr;
	Vertex* v7 = nullptr;
	MEV(l0, v5, Vec3f(3.0f, 2.0f, -2.0f), &e9, &v7);
	e9->has_bezier = false;
	if (state <= 8) return;
	Face *f4 = nullptr;
	Loop *l4 = nullptr;
	Edge* e10 = nullptr;	
	MEL(l0, v7, v2, &f4, &l4, &e10);
	e10->has_bezier = false;
	if (state <= 9) return;

	// back quad (xy-plane, z = -2.0f)
	//  v7 ----e11--- v6
	//  |             |
	//  e9   l5,f5    e8
	//  |             |
	//  v5 ----e5---- v4
	// the previously "open" loop 0 is automatically becoming the top quad
	Face *f5 = nullptr;
	Loop *l5 = nullptr;
	Edge* e11 = nullptr;
	MEL(l0, v6, v7, &f5, &l5, &e11);
	e11->has_bezier = false;
	if (state <= 10) return;

	// top hole (xz-plane, y = 2.0f)
	//  v12 ---e14--- v11
	//  |             |
	//  e15  l7,f7    e13
	//  |             |
	//  v9 ----e12--- v10
	// l7 is oriented counter clock wise and is the front face.
	// l6 is oriented clock wise and is the back face.
	// l6 is the "open" loop used to create all other faces.
	Shell *s1 = nullptr;
	Face *f6 = nullptr;
	Loop *l6 = nullptr;
	Edge *e12 = nullptr;
	Vertex *v9 = nullptr, *v10 = nullptr;
	MEVVLS(solid, Vec3f(1.5f, 2.0f, 0.5f), Vec3f(2.5f, 2.0f, 0.5f), &s1, &f6, &l6, &e12, &v9, &v10);
	if (state <= 11) return;
	Edge *e13 = nullptr;
	Vertex* v11 = nullptr;
	MEV(l6, v10, Vec3f(2.5f, 2.0f, -1.5f), &e13, &v11);
	Edge *e14 = nullptr;
	Vertex* v12 = nullptr;
	MEV(l6, v11, Vec3f(1.5f, 2.0f, -1.5f), &e14, &v12);
	if (state <= 12) return;
	Face *f7 = nullptr;
	Loop *l7 = nullptr;
	Edge* e15 = nullptr;	
	MEL(l6, v12, v9, &f7, &l7, &e15);
	if (state <= 13) return;

	// make top hole quad to a real hole in face 0
	KPMH(f0, l6);
	if (state <= 14) return;

	// create a ring with face 2 and the previously created hole
	KPMH(f2, l7);

	// ==========================================
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
	for (auto *p : shells) delete p;
	shells.clear();
	for (auto *p : solids) delete p;
	solids.clear();
	cSolids = 0;
	cShells = 0;
	cFaces = 0;
	cLoops = 0;
	cEdges = 0;
	cHalfEdges = 0;
	cVertices = 0;
}

Solid* HalfEdgeDS::createNewSolid()
{
	Solid* p = new Solid;
	p->ID = cSolids++;
	solids.push_back(p);
	return p;
}

Shell* HalfEdgeDS::createNewShell()
{
	Shell* p = new Shell;
	p->ID = cShells++;
	shells.push_back(p);
	return p;
}

Face* HalfEdgeDS::createNewFace()
{
	Face* p = new Face;
	p->ID = cFaces++;
	faces.push_back(p);
	return p;
}

Loop* HalfEdgeDS::createNewLoop()
{
	Loop* p = new Loop;
	p->ID = cLoops++;
	loops.push_back(p);
	return p;
}

Edge* HalfEdgeDS::createNewEdge()
{
	Edge* p = new Edge;
	p->ID = cEdges++;
	edges.push_back(p);
	return p;
}

HalfEdge* HalfEdgeDS::createNewHalfEdge()
{
	HalfEdge* p = new HalfEdge;
	p->ID = cHalfEdges++;
	halfEdges.push_back(p);
	return p;
}

Vertex* HalfEdgeDS::createNewVertex()
{
	Vertex* p = new Vertex;
	p->ID = cVertices++;
	vertices.push_back(p);
	return p;
}

bool HalfEdgeDS::MEVVLS(Solid* solid, Vec3f& p1, Vec3f& p2, Shell** newShell, Face** newFace, Loop** newLoop, Edge** newEdge, Vertex** newVertex1, Vertex** newVertex2)
{
	// validation. we assume all pointers of the objects are set and correct.
	if (!solid)
	{
		std::cout << "MEVVLS error: nullptr argument (solid)." << std::endl; 
		return false;
	}
	// create elements and append them to the std::list	
	*newShell = createNewShell();
	*newFace = createNewFace();
	*newLoop = createNewLoop();
	*newEdge = createNewEdge();
	*newVertex1 = createNewVertex();
	*newVertex2 = createNewVertex();
	HalfEdge* he1 = createNewHalfEdge();
	HalfEdge* he2 = createNewHalfEdge();
	// set up new connections
	solid->addShell(*newShell);
	(*newShell)->set(solid, *newShell, *newShell, *newFace);
	(*newFace)->set(*newShell, *newLoop, nullptr);
	(*newLoop)->set(*newFace, *newLoop, *newLoop, he1);
	(*newEdge)->set(he1, he2);
	he1->set(*newLoop, *newEdge, he2, he2, *newVertex1);
	he2->set(*newLoop, *newEdge, he1, he1, *newVertex2);
	(*newVertex1)->set(he1, p1);
	(*newVertex2)->set(he2, p2);
	return true;
}

bool HalfEdgeDS::MEV(Loop* loop, Vertex* vertex, Vec3f& p, Edge** newEdge, Vertex** newVertex)
{
	// validation. we assume all pointers of the objects are set and correct.
	if (!loop || !vertex)
	{
		std::cout << "MEV error: nullptr arguments (loop or vertex)." << std::endl; 
		return false;
	}
	// remember old connections
	HalfEdge* heAfterNewEdge = vertex->getOutgoingHalfEdgeInLoop(loop);
	if (!heAfterNewEdge)
	{
		std::cout << "MEV error: vertex " << vertex->ID << " is not in loop " << loop->ID << std::endl; 
		return false;
	}
	// create elements and append them to the std::list	
	*newEdge = createNewEdge();
	*newVertex = createNewVertex();
	HalfEdge* he1 = createNewHalfEdge();
	HalfEdge* he2 = createNewHalfEdge();
	// set up new connections	
	HalfEdge* heBeforeNewEdge = heAfterNewEdge->prevHE;
	heAfterNewEdge->prevHE = he2;
	heBeforeNewEdge->nextHE = he1;
	(*newEdge)->set(he1, he2);
	he1->set(loop, *newEdge, he2, heBeforeNewEdge, vertex);
	he2->set(loop, *newEdge, heAfterNewEdge, he1, *newVertex);
	(*newVertex)->set(he2, p);
	return true;
}

bool HalfEdgeDS::MEL(Loop* loop, Vertex* vertex1, Vertex* vertex2, Face** newFace, Loop** newLoop, Edge** newEdge)
{
	// validation. we assume all pointers of the objects are set and correct.
	if (!loop || !vertex1 || !vertex2)
	{
		std::cout << "MEL error: nullptr arguments (loop, vertex1 or vertex2)." << std::endl; 
		return false;
	}
	if (vertex1 == vertex2)
	{
		std::cout << "MEL error: same vertices." << std::endl; 
		return false;
	}
	// remember old connections
	HalfEdge* heFromVertex1 = vertex1->getOutgoingHalfEdgeInLoop(loop);
	HalfEdge* heToVertex1 = heFromVertex1->prevHE;
	HalfEdge* heFromVertex2 = vertex2->getOutgoingHalfEdgeInLoop(loop);
	HalfEdge* heToVertex2 = heFromVertex2->prevHE;
	if (!heFromVertex1 || !heFromVertex2) 
	{
		std::cout << "MEL error: vertex " << vertex1->ID << " or " << vertex2->ID << " are not in loop " << loop->ID << std::endl; 
		return false;
	}
	// create elements and append them to the std::list	
	*newFace = createNewFace();
	*newLoop = createNewLoop();
	*newEdge = createNewEdge();
	HalfEdge* he1 = createNewHalfEdge();
	HalfEdge* he2 = createNewHalfEdge();
	// set up new connections
	heToVertex1->nextHE = he1;
	heToVertex2->nextHE = he2;
	heFromVertex1->prevHE = he2;
	heFromVertex2->prevHE = he1;
	loop->toHE = he2;
	(*newFace)->set(loop->toFace->toShell, *newLoop, nullptr);
	(*newLoop)->set(*newFace, *newLoop, *newLoop, he1);
	(*newEdge)->set(he1, he2);
	he1->set(*newLoop, *newEdge, heFromVertex2, heToVertex1, vertex1);
	he2->set(loop, *newEdge, heFromVertex1, heToVertex2, vertex2);	
	auto hesNewLoop = he1->getAllHalfEdges();
	for (auto he : hesNewLoop) he->toLoop = *newLoop;
	return true;
}

bool HalfEdgeDS::KPMH(Face* face, Loop* peripheralLoop)
{
	// validation. we assume all pointers of the objects are set and correct.
	if (!face || !peripheralLoop)
	{
		std::cout << "KPMH error: nullptr arguments (face or peripheralLoop)." << std::endl; 
		return false;
	}
	if (!peripheralLoop->isOuterLoop())
	{
		std::cout << "KPMH error: loop " << peripheralLoop->ID << " is not a peripheral loop." << std::endl; 
		return false;
	}
	// check if a shell gets obsolete (if there were two different shells before, only one remains)
	if (peripheralLoop->toFace->toShell != face->toShell)
	{
		// change the shell for all faces of the shell
		Shell* obsoleteShell = peripheralLoop->toFace->toShell;
		for (auto f : faces) if (f->toShell == obsoleteShell) f->toShell = face->toShell;
		obsoleteShell->toSolid->removeShell(obsoleteShell);
		shells.remove(obsoleteShell);
		delete obsoleteShell;
	}
	// remove face of the peripheral loop
	faces.remove(peripheralLoop->toFace);
	delete peripheralLoop->toFace;
	// set up new connections
	face->addLoop(peripheralLoop);
	peripheralLoop->toFace = face;
	return true;
}

float HalfEdgeDS::calculateRingsWithEulerPoincare()
{
	float V = float(vertices.size());
	float E = float(edges.size());
	float F = float(faces.size());
	float S = float(shells.size());
	float H = float(loops.size() - faces.size());
	// V - E + F = 2 * (S - R) + H
	// ((V - E + F - H) / 2) - S = - R
	// (-0.5 * (V - E + F - H)) + S = R
	return (-0.5f * (V - E + F - H)) + S;
}

void HalfEdgeDS::rotateAllVerticesX(const float angleInRadian)
{
	Matrix4f m = Matrix4f::rotationXMatrix(angleInRadian);
	// Used to rotate all Vertices coordinates
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to rotate all bezier curve	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();				
			}
			edges.front()->set(BezierCurve(cps_vect));	
		}
		temp_edges.push_back(edges.front());
		edges.pop_front();	
	}
	edges = temp_edges;
	
}

void HalfEdgeDS::rotateAllVerticesY(const float angleInRadian)
{
	Matrix4f m = Matrix4f::rotationYMatrix(angleInRadian);
	// Used to rotate all Vertices coordinates
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to rotate all bezier curve	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();	
				}

			edges.front()->set(BezierCurve(cps_vect));
			}
		temp_edges.push_back(edges.front());
			edges.pop_front();	
	}
	edges = temp_edges;
}

void HalfEdgeDS::rotateAllVerticesZ(const float angleInRadian)
{
	Matrix4f m = Matrix4f::rotationZMatrix(angleInRadian);
	// Used to rotate all Vertices coordinates
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to rotate all bezier curve	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();	
						
			}

			edges.front()->set(BezierCurve(cps_vect));
			
		}
		temp_edges.push_back(edges.front());
			edges.pop_front();	
	}
	edges = temp_edges;
}

void HalfEdgeDS::scaleObjects(const float scaleX,const float scaleY,const float scaleZ){
	Matrix4f m = Matrix4f::scaleMatrix(scaleX,scaleY,scaleZ);
		// Used to scale all Edges
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to scale all bezier curves	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();	
						
			}

			edges.front()->set(BezierCurve(cps_vect));
			
		}
		temp_edges.push_back(edges.front());
			edges.pop_front();	
	}
	edges = temp_edges;
}

void HalfEdgeDS::translateObjects(int dx, int dy, int dz){
	Matrix4f m = Matrix4f::translateMatrix(dx, dy, dz);
			// Used to translate all Edges
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to translate all bezier curves	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();	
						
			}

			edges.front()->set(BezierCurve(cps_vect));
			
		}
		temp_edges.push_back(edges.front());
			edges.pop_front();	
	}
	edges = temp_edges;
}



void HalfEdgeDS::quaternion(double a, double b, double c, double d){
	Matrix4f m = Matrix4f::quaternion(a,b,c,d);
	std::cout << m << std::endl;
	// Used to rotate all Edges
	temp_vertices.clear();
	unsigned int vertices_size = vertices.size();
	for(unsigned int i=0; i < vertices_size; i++){
		vertices.front()->coordinates = m.operator*(vertices.front()->coordinates);
		temp_vertices.push_back(vertices.front());
		vertices.pop_front();
	}
	vertices = temp_vertices; 
	//Used to rotate all bezier curves	
	temp_edges.clear();
	std::vector<Vec3f> cps_vect;
	unsigned int edges_size = edges.size();
	for( unsigned int i = 0 ; i < edges_size ; i++ ){
		if(edges.front()->bezierCurve.getControlPoints().size() > 0){
			unsigned int cps_size = edges.front()->bezierCurve.getControlPoints().size();
			for(unsigned int n=0; n< cps_size; n++){
				cps_vect.push_back(m.operator*(edges.front()->bezierCurve.getControlPoints().back()));
				edges.front()->bezierCurve.getControlPoints().pop_back();	
						
			}

			edges.front()->set(BezierCurve(cps_vect));
			
		}
		temp_edges.push_back(edges.front());
			edges.pop_front();	
	}
	edges = temp_edges;
}

int HalfEdgeDS::testeBezier(HalfEdge* active_he){

	if(!active_he->toEdge->has_bezier){
    std::vector<Vec3f> cps1;
	HalfEdge* opp = active_he->oppHE();
	cps1.push_back(active_he->startV->coordinates);
	
	float  x1 = active_he->startV->coordinates.x;
	float y1 = active_he->startV->coordinates.y;
	float z1 = active_he->startV->coordinates.z;
	float x2 = opp->startV->coordinates.x;
	float y2 =opp->startV->coordinates.y;
	float z2 = opp->startV->coordinates.z;
	float x3, x4, y3, y4, z3, z4;

	if (x1 > x2){
		x3 = x1  -0.25f;
		x4 = x1 - 0.5f;
	}else if(x2 > x1) {
		x3 = x1 + 0.25f;
		x4 = x1 + 0.5f;
	}else {
		x3 = x1;
		x4 = x1;
	}
	if (y1 > y2){
		y3 = y1 - 0.25f;
		y4 = y1 - 0.5f;
	}else if(y2 > y1) {
		y3 = y1 + 0.25f;
		y4 = y1 + 0.5f;
	}else {
		y3 = y1;
		y4 = y1;
	}
	if (z1 > z2){
		z3 = z1 - 0.25f;
		z4 = z1 - 0.5f;
	}else if(z2 > z1) {
		z3 = z2 + 0.25f;
		z4 = z2 + 0.5f;
	}else {
		z3 = z1;
		z4 = z1;
	}
	if(x3 == x4 && y3 == y4){
		x3 += 1.0f;
		x4 += 1.0f;
	}
	if(y3 == y4 && z3 == z4){
		y3 += 1.0f;
		y4 += 1.0f;
	}
	if(z3 == z4 && x3 == x4){
		z3 += 1.0f;
		z4 += 1.0f;
	}

	cps1.push_back(Vec3f(x3,y3,z3));
	cps1.push_back(Vec3f(x4,y4,z4));
	cps1.push_back(opp->startV->coordinates);
    BezierCurve bezierCurve1(cps1);
	std::cout << edges.front()->bezierCurve << std::endl;
	active_he->toEdge->set(bezierCurve1);
    bezierCurve1.separateCurveAt(0.5);
	}
    
    
    return 0;
}

std::ostream& operator<< (std::ostream& os, HalfEdgeDS& ds)
{
	os	<< std::endl
		<< "Elements in the lists of the data structure:" << std::endl
		<< "  " << std::setw(3) << ds.solids.size()		<< " solids, " << std::endl
		<< "  " << std::setw(3) << ds.shells.size()		<< " shells, " << std::endl
		<< "  " << std::setw(3) << ds.faces.size()		<< " faces, " << std::endl
		<< "  " << std::setw(3) << ds.loops.size()		<< " loops, " << std::endl
		<< "  " << std::setw(3) << ds.edges.size()		<< " edges, " << std::endl
		<< "  " << std::setw(3) << ds.halfEdges.size()	<< " halfEdges, " << std::endl
		<< "  " << std::setw(3) << ds.vertices.size()	<< " vertices." << std::endl
		<< "  " << std::setw(3) << ds.calculateRingsWithEulerPoincare() << " rings calculated" << std::endl;
	return os;
}