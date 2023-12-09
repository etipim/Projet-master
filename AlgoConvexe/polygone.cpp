#include "polygone.h"
#include "point.h"

using namespace std;

// Impl�mentation des m�thodes de la classe Polygone

// destructeur
Polygone::~Polygone()
{

}
Sommet* test = nullptr;
// Ajoute un nouveau sommet au polygone. Les coordonn�es du sommet � ajouter sont celles du point p.
// sommetPrecedent est soit un pointeur sur l�un des sommets d�j� pr�sents dans le polygone, 
// soit un pointeur nul si le polygone est vide.
// Dans le premier cas, le nouveau sommet devient le successeur du sommet d�adresse sommetPrecedent.
// Dans le deuxi�me cas, le nouveau sommet devient l�unique sommet du polygone.
// Dans tous les cas, la m�thode renvoie l�adresse du nouveau sommet.
Sommet* Polygone::ajouteSommet(const Point &p, Sommet* sommetPrecedent)
{
    Sommet* s = new Sommet{{ p.x(), p.y()}, nullptr, nullptr};
    if (sommetPrecedent == nullptr and test == nullptr){
        s->d_suivant = s;
        s->d_precedent = s;
        test = s;
    } else {
        if (sommetPrecedent == nullptr){
            sommetPrecedent = test;
        }
        s->d_precedent = sommetPrecedent->d_precedent;
        s->d_precedent->d_suivant = s;
        s->d_suivant = sommetPrecedent;


        sommetPrecedent->d_suivant = s;
        //s->suivant()->d_precedent = s;
    }


	return s;
}


// Supprime le sommet d�adresse s du polygone.
// On suppose que s est effectivement pr�sent dans le polygone.
void Polygone::supprimeSommet(Sommet* s)
{
    s->suivant()->d_precedent = s->precedent();
    s->precedent()->d_suivant = s->suivant();
    delete s;
}





