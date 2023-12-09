#include "point.h"

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
    double d = (b.x() - a.x())*(b.y() - a.y()) - (b.x() - a.x())*(b.y() - a.y());
    if(d == 0){
        return 0;
    }else if(d < 0){
        return 0;
    } else if (d > 0){
        return 1;
    }
}
