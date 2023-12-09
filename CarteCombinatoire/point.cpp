#include "point.h"
#include <cmath>

// renvoie 1, -1 ou 0 selon que le point auquel la m�thode est appliqu�e est
// � gauche de, � droite de, ou sur la droite (ab) orient�e de a vers b.
int Point::aGauche(const Point &a, const Point &b) const
{
    double d = (b.x() - a.x())*(this->d_y - a.d_y)-(this->x() - a.x())*(b.y() - a.y());
    // ni à droite ni à gauche
    if(d == 0){
        return 0;
    }
    // A droite
    else if(d < 0){
        return -1;
    }
    // A gauche
    else if (d > 0){
        return 1;
    }
}

int Point::dansCercle( const Point &a, const Point &b,const Point &c) const
{
    double A = (a.x() - this->x());
    double B = (a.y() - this->y());
    double C = (pow(a.x() - this->x(), 2) + pow(a.y() - this->y(), 2));
    double D = (b.x() - this->x());
    double E = (b.y() - this->y());
    double F = (pow(b.x() - this->x(), 2) + pow(b.y() - this->y(), 2));
    double G = (c.x() - this->x());
    double H = (c.y() - this->y());
    double I = (pow(c.x() - this->x(), 2) + pow(c.y() - this->y(), 2));
    // Matrice:
    // |A B C|
    // |D E F|
    // |G H I|
    // Calcul du déterminant
    // det=a(ei−fh)−b(di−fg)+c(dh−eg)
    double resultat = /* A*(E*I - F*H) - B*(D*I - F*G)+C*(D*H - E*G); */ (A*E*I)-(A*F*H)+(B*F*G)-(B*D*I)+(C*D*H)-(C*E*G);
    if(resultat > 0){
        //Dans le cercle
        return 1;
    }else if(resultat < 0){
        //Ext du cercle
        return -1;
    }else{
        //Sur le cercle
        return 0;
    }
}

