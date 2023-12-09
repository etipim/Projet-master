#include <iostream>
#include <vector>
#include "affichage.h"
#include "point.h"
#include "polygone.h"
#include "graphics.h"

int main() {
    opengraphsize(600, 450);



    // INIT POINT
    const std::vector<Point> points = {
            {35, 110},
            {43, 70},
            {100, 130},
            {10, 50},
            {120, 10},
            {123, 95},
            {135, 50},
            {145, 80},
            {200, 75},
    };

    Sommet* s = new Sommet(points[0]);
    Polygone* P = new Polygone();

    for (int i = 0; i < points.size(); ++i) {
        P->ajouteSommet(points[i]);
    }

    trace(*P);

    //getch();
    //closegraph();

    return 0;
}
