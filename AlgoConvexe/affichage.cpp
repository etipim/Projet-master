#include "affichage.h"
#include "point.h"
#include "polygone.h"
#include "graphics.h"

// trace un segment entre deux points a et b
void segment(const Point & a, const Point & b)
{
    setcolor(GREEN);
    line(a.x(), a.y(), b.x(), b.y());
}


// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P)
{
    if(P.premier() == nullptr){ return; }

    Sommet* s = P.premier();
    do{
        segment(s->coordonnees(), s->suivant()->coordonnees());
        s = s->suivant();
    } while (s != P.premier());

}

