#include "EulerOps.h"

	Mevvls* mevvls = new Mevvls;

	mevvls->newV1 = new Vertex;
	mevvls->newV2 = new Vertex;
	mevvls->newV1->coordinates = mevvls->coordinates_1;
	mevvls->newV2->coordinates = mevvls->coordinates_2;

	mevvls->newHe1->startV = mevvls->newV1;
	mevvls->newHe1->nextHE = mevvls->newHe2;
	mevvls->newHe1->prevHE = mevvls->newHe2;
	mevvls->newV1->outgoingHE = mevvls->newHe1;

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

	mevvls->newS1 ->toFace = mevvls->newF1;

	vertices.push_back(mevvls->newV1);
	vertices.push_back(mevvls->newV2);
	halfEdges.push_back(mevvls->newHe1);
	halfEdges.push_back(mevvls->newHe2);
	edges.push_back(mevvls->newE1);
	loops.push_back(mevvls->newL1);
	faces.push_back(mevvls->newF1);
	solids.push_back(mevvls->newS1);




EulerOps::EulerOps(void)
{
}


EulerOps::~EulerOps(void)
{
}
