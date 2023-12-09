#include "enveloppe.h"
#include "point.h"
#include "polygone.h"

#include <vector>

using namespace std;


// Construit dans le polygone P l’enveloppe convexe des trois points a,b,c. On suppose P initialement vide.
// La fonction renvoie l’adresse du sommet de coordonnées c.
Sommet* enveloppe(const Point &a, const Point &b, const Point &c, Polygone &P)
{
    int topSens = (b.x()-a.x()) * (c.y()-a.y()) - (c.x()-a.x()) * (b.y()-a.y());
    Sommet* sa = P.ajouteSommet(a);
    if (topSens < 0){
        Sommet* sb = P.ajouteSommet(b, sa);
        Sommet* sc = P.ajouteSommet(c, sb);
        //sa->precedent() = sc;
    } else {
        Sommet* sc = P.ajouteSommet(c, sa);
        Sommet* sb = P.ajouteSommet(b, sc);
        //sa->precedent() = sb;
    }

	return sa;
}


// Construit dans le polygone P l’enveloppe convexe de l'ensemble de points donné dans T.
// On suppose P initialement vide.
void enveloppe(vector<Point>&T, Polygone &P)
{
}
