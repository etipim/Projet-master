#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "point.h"
#include "polygone.h"

// trace un segment entre deux points a et b
void segment(const Point & a, const Point & b);

// trace le polygone P dans une fenêtre graphique
void trace(const Polygone &P);

#endif
