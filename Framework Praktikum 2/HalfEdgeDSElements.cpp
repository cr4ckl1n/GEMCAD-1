#include "HalfEdgeDSElements.h"

#include <iostream>
#include <iomanip>

Solid::Solid()
	: ID(0)
	, outerShell(nullptr)
	, innerShell(nullptr)
{
}

void Solid::addShell(Shell* shell)
{
	// create a new outer shell if there was none
	if (!outerShell) outerShell = shell;
	// create a new inner shell if there was no inner one before
	else if (!innerShell) innerShell = shell;
	// append the shell at the back
	else innerShell->prevShell->addShell(shell); 
}

bool Solid::removeShell(Shell* shell)
{
	if (shell == outerShell)
	{
		if (innerShell)
		{
			std::cout << "removeShell error: shell " << shell->ID << " can not be removed, since it is the outer shell and inner shells still exist." << std::endl;
			return false;
		}
		outerShell = nullptr;
		return true;
	}
	// remove inner shell
	if (shell == innerShell)
	{
		// only one inner shell available
		if (shell->nextShell == innerShell)
		{
			innerShell = nullptr;
			return true;
		}
		// change inner shell pointer to a different shell that remains
		innerShell = innerShell->nextShell;		
	}
	shell->removeShell();
	return true;
}

Shell::Shell()
	: ID(0)
	, toSolid(nullptr)
	, nextShell(nullptr)
	, prevShell(nullptr)
	, toFace(nullptr)
{
}

void Shell::set(Solid* toSolid_, Shell* nextShell_, Shell* prevShell_, Face* toFace_)
{
	if (toSolid_) toSolid = toSolid_;
	if (nextShell_) nextShell = nextShell_;
	if (prevShell_) prevShell = prevShell_;
	if (toFace_) toFace = toFace_;
}

void Shell::addShell(Shell* shell)
{
	Shell* oldNextShell = nextShell;
	nextShell = shell;
	shell->prevShell = this;
	shell->nextShell = oldNextShell;
	shell->toSolid = toSolid;
	oldNextShell->prevShell = shell;
}

void Shell::removeShell()
{
	// unlink itself
	prevShell->nextShell = nextShell;
	nextShell->prevShell = prevShell;
	nextShell = nullptr;
	prevShell = nullptr;
}

Shell* Shell::nextShellInSolid()
{
	// if this loop is the outer loop => return the first inner loop if it exists, else return the outer loop again since there is no other loop
	if (toSolid->outerShell == this)
	{
		if (toSolid->innerShell) return toSolid->innerShell;
		else return this;
	}
	// now we know, this is a inner loop. if it is the last inner loop => return the outer loop, else return the next inner loop
	if (nextShell == toSolid->innerShell) return toSolid->outerShell;
	return nextShell;
}

Face::Face()
	: ID(0)
	, toShell(nullptr)
	, outerLoop(nullptr)
	, innerLoop(nullptr)
{
}

void Face::set(Shell* toShell_, Loop* outerLoop_, Loop* innerLoop_)
{
	if (toShell_) toShell = toShell_;
	if (outerLoop_) outerLoop = outerLoop_;
	if (innerLoop_) innerLoop = innerLoop_;
}

void Face::addLoop(Loop* loop)
{
	// create a new outer loop if there was none
	if (!outerLoop) outerLoop = loop;
	// create a new inner loop if there was no inner one before
	else if (!innerLoop) innerLoop = loop;
	// append the loop at the back
	else innerLoop->prevLoop->addLoop(loop); 
}

std::vector<Loop*> Face::getAllLoops()
{
	std::vector<Loop*> loops;
	if (!outerLoop) return loops;
	Loop* currentLoop = outerLoop;
	do 
	{
		loops.push_back(currentLoop);
		currentLoop = currentLoop->nextLoopInFace();
	} while (currentLoop != outerLoop);
	return loops;
}

Loop::Loop()
	: ID(0)
	, toFace(nullptr)
	, nextLoop(nullptr)
	, prevLoop(nullptr)
	, toHE(nullptr)
{
}

void Loop::set(Face* toFace_, Loop* nextLoop_, Loop* prevLoop_, HalfEdge* toHE_)
{
	if (toFace_) toFace = toFace_;
	if (nextLoop_) nextLoop = nextLoop_;
	if (prevLoop_) prevLoop = prevLoop_;
	if (toHE_) toHE = toHE_;
}

void Loop::addLoop(Loop* loop)
{
	Loop* oldNextLoop = nextLoop;
	nextLoop = loop;
	loop->prevLoop = this;
	loop->nextLoop = oldNextLoop;
	loop->toFace = toFace;
	oldNextLoop->prevLoop = loop;
}

Loop* Loop::nextLoopInFace()
{
	// if this loop is the outer loop => return the first inner loop if it exists, else return the outer loop again since there is no other loop
	if (toFace->outerLoop == this)
	{
		if (toFace->innerLoop) return toFace->innerLoop;
		else return this;
	}
	// now we know, this is a inner loop. if it is the last inner loop => return the outer loop, else return the next inner loop
	if (nextLoop == toFace->innerLoop) return toFace->outerLoop;
	return nextLoop;
}

std::vector<HalfEdge*> Loop::getAllHalfEdges()
{
	return toHE->getAllHalfEdges();
}

bool Loop::isOuterLoop()
{
	if (toFace->outerLoop == this) return true;
	return false;
}

Edge::Edge()
	: ID(0)
	, he1(nullptr)
	, he2(nullptr)
{
}

void Edge::set(HalfEdge* he1_, HalfEdge* he2_)
{
	if (he1_) he1 = he1_;
	if (he2_) he2 = he2_;
}

void Edge::set(const BezierCurve& bezierCurve_)
{
	bezierCurve = bezierCurve_;
}

void Edge::set(HalfEdge* he1_, HalfEdge* he2_, const BezierCurve& bezierCurve_)
{
	set(he1_, he2_);
	set(bezierCurve_);
}

HalfEdge::HalfEdge()
	: ID(0)
	, toLoop(nullptr)
	, toEdge(nullptr)
	, nextHE(nullptr)
	, prevHE(nullptr)
	, startV(nullptr)
{
}

void HalfEdge::set(Loop* toLoop_, Edge* toEdge_, HalfEdge* nextHE_, HalfEdge* prevHE_, Vertex* startV_)
{
	if (toLoop_) toLoop = toLoop_;
	if (toEdge_) toEdge = toEdge_;
	if (nextHE_) nextHE = nextHE_;
	if (prevHE_) prevHE = prevHE_;
	if (startV_) startV = startV_;
}

HalfEdge* HalfEdge::oppHE()
{
	if (toEdge)
	{
		if (toEdge->he1 == this) return toEdge->he2;
		else return toEdge->he1;
	}
	else return nullptr;
}

std::vector<HalfEdge*> HalfEdge::getAllHalfEdges()
{
	std::vector<HalfEdge*> hes;
	HalfEdge* currentHE = this;
	do 
	{
		hes.push_back(currentHE);
		currentHE = currentHE->nextHE;
	} while (currentHE != this);
	return hes;
}

std::ostream& operator<<(std::ostream& os, HalfEdge& he)
{
	os	<< "he " << std::setw(3) << he.ID
		<< ",  edge " << std::setw(3) << he.toEdge->ID
		<< ",  vertex " << std::setw(3) << he.startV->ID
		<< ",  loop " << std::setw(3) << he.toLoop->ID
		<< ",  face " << std::setw(3) << he.toLoop->toFace->ID
		<< ",  shell " << std::setw(3) << he.toLoop->toFace->toShell->ID
		<< ",  solid " << std::setw(3) << he.toLoop->toFace->toShell->toSolid->ID;
	return os;
}

Vertex::Vertex()
	: ID(0)
	, outgoingHE(nullptr)
	, coordinates(Vec3f())
{
}

void Vertex::set(HalfEdge* outgoingHE_, Vec3f& coordinates_)
{
	if (outgoingHE_) outgoingHE = outgoingHE_;
	coordinates = coordinates_;
}

std::vector<HalfEdge*> Vertex::getAllOutgoingHalfEdges()
{
	std::vector<HalfEdge*> outgoingHEs;
	if (!outgoingHE) return outgoingHEs;
	HalfEdge* currentHE = outgoingHE;
	do 
	{
		outgoingHEs.push_back(currentHE);
		currentHE = currentHE->oppHE()->nextHE;
	} while (currentHE != outgoingHE);	
	return outgoingHEs;
}

HalfEdge* Vertex::getOutgoingHalfEdgeInLoop(Loop* loop)
{
	if (!loop) return nullptr;
	auto hes = getAllOutgoingHalfEdges();
	for (auto he : hes)
		if (he->toLoop == loop)
			return he;
	return nullptr;
}
