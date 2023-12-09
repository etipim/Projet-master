#include "affichage.h"
#include "point.h"
#include "carte.h"
#include "graphics.h"

// trace un segment entre deux points a et b
void segment(const Point &a, const Point &b)
{
    setcolor(RED);
    line(a.x(), 500 - a.y(), b.x(),  500 - b.y());
}

// trace un segment entre deux points a et b
void Debugge(const Point &a, const Point &b)
{
    setcolor(BLUE);
    line(a.x(), 500 - a.y(), b.x(),  500 - b.y());
}

// trace la carte C dans une fen�tre graphique
void trace(const Carte &C)
{
    for (int i = 0; i < C.nbDemiCotes(); ++i) {
        if(C.demiCote(i)->index() < C.demiCote(i)->oppose()->index()){
            segment(C.demiCote(i)->coordonnees(), C.demiCote(i)->oppose()->coordonnees());
        }
    }
}


