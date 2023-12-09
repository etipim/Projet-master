#include "carte.h"
#include "point.h"
#include "affichage.h"
#include "graphics.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Destructeur
Carte::~Carte()
{
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2
// dont precedent1 et precedent2 seront les demi-c�t�s pr�c�dents respectifs.
// On suppose precedent1 et precedent2 d�j� pr�sents dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, DemiCote* precedent2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    ajouteDemiCote(precedent2, dc1);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent1 sera le demi-c�t� pr�c�dent de dc1. dc2 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p2.
// On suppose precedent1 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(DemiCote* precedent1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(precedent1, nullptr);
    ajouteDemiCote(p2, dc1);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// precedent2 sera le demi-c�t� pr�c�dent de dc2. dc1 sera issu d�un
// nouveau sommet (� cr�er) dont les coordonn�es sont celles du point p1.
// On suppose precedent2 d�j� pr�sent dans la carte.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, DemiCote* precedent2)
{
    DemiCote* dc1 = ajouteDemiCote(p1, nullptr);
    ajouteDemiCote(precedent2, dc1);
	return dc1;
}

// Ajoute dans la carte un nouveau c�t� compos� de deux demi-c�t�s dc1 et dc2.
// dc1 et dc2 seront issus de deux nouveaux sommets (� cr�er) dont les
// coordonn�es sont celles des points p1 et p2 respectivement.
// Renvoie l'adresse de dc1.
DemiCote* Carte::ajouteCote(const Point& p1, const Point& p2)
{
    DemiCote* dc1 = ajouteDemiCote(p1, nullptr);
    ajouteDemiCote(p2, dc1);
	return dc1;
}

// Ajoute un nouveau demi-c�t� dans la carte dont precedent sera le demi-c�t�
// 	pr�c�dent et oppose sera le demi-c�t� oppos�.
// On suppose que le demi-c�t� precedent est d�j� pr�sent dans la carte.
// Le demi-c�t� oppose est soit d�j� pr�sent dans la carte soit nul (valeur
// par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(DemiCote* precedent, DemiCote* oppose)
{
    DemiCote* NouveauDemiCote = new DemiCote{precedent->suivant(), precedent, oppose, precedent->sommet(), static_cast<int>(d_tabDemiCotes.size())};
    d_tabDemiCotes.push_back(NouveauDemiCote);
    precedent->d_suivant = NouveauDemiCote;
    NouveauDemiCote->d_suivant->d_precedent = NouveauDemiCote;
    if (oppose != nullptr){
        oppose->d_oppose = NouveauDemiCote;
    }
	return NouveauDemiCote;

}

// Ajoute un nouveau demi-c�t� dans la carte qui sera issu d�un nouveau
// sommet (� cr�er) dont les coordonn�es sont celles du point p.
// oppose sera le demi-c�t� oppos� du nouveau demi-c�t�.
// oppose est soit d�j� pr�sent dans la carte soit nul (valeur par d�faut).
// Renvoie l�adresse du nouveau demi-c�t�.
DemiCote* Carte::ajouteDemiCote(const Point &p, DemiCote* oppose)
{
    Sommet* NouveauSommet = new Sommet{p, nullptr, static_cast<int>(d_tabSommets.size())};
    DemiCote* NouveauDemiCote = new DemiCote{nullptr, nullptr, oppose, NouveauSommet, static_cast<int>(d_tabDemiCotes.size())};
    NouveauSommet->d_demiCote = NouveauDemiCote;
    NouveauDemiCote->d_suivant = NouveauDemiCote;
    NouveauDemiCote->d_precedent = NouveauDemiCote;
    if (oppose != nullptr){
        oppose->d_oppose = NouveauDemiCote;
    }
    d_tabDemiCotes.push_back(NouveauDemiCote);
    d_tabSommets.push_back(NouveauSommet);

	return NouveauDemiCote;
}

void Carte::addDemiCoteParticulier(DemiCote* premierDC)
{
    double bestAngle = 1000;
    DemiCote* bestDC;

    double hypo;
    double coteAdj;
    double coteOppo;
    DemiCote* dcCheck = premierDC->oppose();
    do {
        dcCheck = dcCheck->oppose()->suivant()->oppose();
        coteAdj = dcCheck->sommet()->coordonnees().y() - premierDC->sommet()->coordonnees().y();
        if (coteAdj < 0)
        {
            coteAdj = coteAdj * (-1);
        }
        coteOppo = dcCheck->sommet()->coordonnees().x() - premierDC->sommet()->coordonnees().x();
        hypo = sqrt(coteAdj*coteAdj + coteOppo*coteOppo);

        double angleEnDegre = acos(coteAdj / hypo)* (180.0 / M_PI);

        if (angleEnDegre < bestAngle)
        {
            bestAngle = angleEnDegre;
            bestDC = dcCheck;
        }
    } while (dcCheck != premierDC->oppose());

    //check sens
    if (bestDC->sommet()->coordonnees().y() < bestDC->oppose()->sommet()->coordonnees().y())
    {
        this->d_demiCoteParticulier = bestDC->oppose();
    }
    else
    {
        this->d_demiCoteParticulier = bestDC;
    }
}

void Carte::triangulation(std::vector<Point> &T)
{
    std::sort(T.begin(), T.end());

    DemiCote* dc = this->ajouteCote(T[0] , T[1]);

    DemiCote* premierCote = dc;

    for (int i = 2; i < T.size(); ++i) {
        dc = ajouteCote(T[i], dc);

        DemiCote* stock = dc;

        while (T[i].aGauche(dc->oppose()->coordonnees(), dc->oppose()->suivant()->oppose()->coordonnees())<0)
        {
            dc = ajouteCote(dc->precedent(), dc->oppose()->suivant()->oppose());
        }

        dc = stock;

        while (T[i].aGauche(dc->oppose()->coordonnees(), dc->oppose()->precedent()->oppose()->coordonnees())>0)
        {
            dc = ajouteCote(dc, dc->oppose()->precedent()->oppose()->precedent());
        }
    }

    this->addDemiCoteParticulier(premierCote);
}

void Carte::delaunay(std::vector<Point> &T)
{
    // Variable pour marquer les coté éxterieurs
    DemiCote* dcLoop = this->demiCoteParticulier();

    // Init de la pile
    vector<DemiCote*> pile;

    do {
        dcLoop->changeMarque(1);
        dcLoop->oppose()->changeMarque(1);
        //Debugge(dcLoop->coordonnees(), dcLoop->oppose()->coordonnees());
        //getch();
        dcLoop = dcLoop->oppose()->suivant();
    } while (dcLoop != this->demiCoteParticulier());

    // marque les coté et les ajoute à la pile
    for (int i = 0; i < this->nbDemiCotes(); ++i) {
        DemiCote* marque = this->demiCote(i);
        if (marque->marque() != 1)
        {
            marque->changeMarque(1);
            marque->oppose()->changeMarque(1);
            pile.push_back(this->demiCote(i));
        }
    }

    while(!pile.empty())
    {
        DemiCote* traitee = pile[pile.size()-1];
        pile.pop_back();
        traitee->changeMarque(0);
        traitee->oppose()->changeMarque(0);
        Sommet* pointOpposeeTriangle = traitee->precedent()->oppose()->sommet();
        float firstPointisInsideTheCircle;
        firstPointisInsideTheCircle = pointOpposeeTriangle->coordonnees().dansCercle(traitee->coordonnees(), traitee->suivant()->oppose()->coordonnees(), traitee->oppose()->coordonnees());

        if (firstPointisInsideTheCircle < 0)
        {
            if (traitee->suivant()->marque() == 0){
                traitee->suivant()->changeMarque(1);
                traitee->suivant()->oppose()->changeMarque(1);
                pile.push_back(traitee->suivant());
            }

            if (traitee->precedent()->marque() == 0){
                traitee->precedent()->changeMarque(1);
                traitee->precedent()->oppose()->changeMarque(1);
                pile.push_back(traitee->precedent());
            }

            if (traitee->oppose()->precedent()->marque() == 0){
                traitee->oppose()->precedent()->changeMarque(1);
                traitee->oppose()->precedent()->oppose()->changeMarque(1);
                pile.push_back(traitee->oppose()->precedent());
            }

            if (traitee->oppose()->suivant()->marque() == 0){
                traitee->oppose()->suivant()->changeMarque(1);
                traitee->oppose()->suivant()->oppose()->changeMarque(1);
                pile.push_back(traitee->oppose()->suivant());
            }

            flip(traitee);
        }
    }
}

void Carte::flip(DemiCote* d) {
    flipDemiCote(d);
    flipDemiCote(d->oppose());
}

void Carte::flipDemiCote(DemiCote* d) {
    // Defini un marqueur de la ou va se trouver le demi cote
    auto demiCoteDepart = d->suivant()->oppose();
    // Changer le demi cote représentant le sommet
    if (d->d_sommet->demiCote() == d) {
        d->d_sommet->d_demiCote = d->suivant();
    }
    // Changer les anciens voisins de d
    d->suivant()->d_precedent = d->precedent();
    d->precedent()->d_suivant = d->suivant();
    // Deplacer d
    d->d_precedent = demiCoteDepart;
    d->d_suivant = demiCoteDepart->suivant();
    // Changer les nouveaux voisins de d
    d->precedent()->d_suivant = d;
    d->suivant()->d_precedent = d;
    // Mettre à jour le sommet de d
    d->d_sommet = demiCoteDepart->sommet();
}

vector<Carte::Face> Carte::AllTriangles()
{
    vector<Face> faces;
    for (int i = 0; i < this->nbSommets(); ++i) {
        DemiCote* dc = this->sommet(i)->demiCote();
        do {
            dc = dc->suivant();
            if (dc->suivant()->oppose()->sommet() == dc->oppose()->precedent()->oppose()->sommet() && dc->oppose()->sommet()->marque() == 0 && dc->suivant()->oppose()->sommet()->marque() == 0)
            {
                faces.push_back({dc->sommet()->index(), dc->oppose()->sommet()->index(), dc->suivant()->oppose()->sommet()->index()});
            }
        } while (dc != this->sommet(i)->demiCote());

        this->sommet(i)->changeMarque(1);
    }

    return faces;
}