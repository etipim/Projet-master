#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "carte.h"
#include "affichage.h"
#include "point.h"
#include "graphics.h"

#define SCREEN_W 1280
#define SCREEN_H 500

int main() {

    // récupérer les points de l'ile Saint Christof
    const char* nomFichier = "C:\\Users\\etipi\\CLionProjects\\CarteCombinatoire\\ileSaintChristof.txt";

    // Ouvrir le fichier en mode lecture
    std::ifstream fichier(nomFichier);

    // Vérifier si l'ouverture a réussi
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    // Lire le nombre de points
    int nombreDePoints;
    fichier >> nombreDePoints;

    // Vector pour stocker les points
    std::vector<Point> pointsIle;

    // Lire les coordonnées depuis le fichier
    int x, y;
    for (int i = 0; i < nombreDePoints; ++i) {
        fichier >> x >> y;

        // Créer un point avec les coordonnées lues
        Point point{x, y};

        // Ajouter le point au vector
        pointsIle.push_back(point);
    }

    // Fermer le fichier
    fichier.close();

    // ouvrir le graf
    opengraphsize(1280, 500);

    // Code pour la première utilisation du graph
    Point p1 {0, 0};
    Point p2 { 450, 720};
    Point p3 {820, 810};
    Carte c {};
    DemiCote* c1 = c.ajouteCote(p1, p2);
    DemiCote* c2 = c.ajouteCote(c1, p3);
    c.ajouteCote(c1->oppose(), c2->oppose());
    //trace(c);


    // Triangulation et triangulation de delaunay
    std::vector<Point> points = {};

    // création des point
    for (int i = 0; i < 1000; i++) {
        points.emplace_back(rand() % SCREEN_W, rand() % SCREEN_H);
    }
    //std::sort(points.begin(), points.end());
    //points.erase(std::unique(points.begin(), points.end()), points.end());

    Carte newc {};

    //newc.triangulation(points);  // Points de test
    newc.triangulation(pointsIle);  // Points de l ile
    trace(newc);

    getch();

    cleardevice();

    newc.delaunay(points);
    trace(newc);

    getch();

    closegraph();
    return 0;
}
