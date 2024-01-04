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
    int x, y, z;
    for (int i = 0; i < nombreDePoints; ++i) {
        fichier >> x >> y >> z;

        // Créer un point avec les coordonnées lues
        Point point{x, y, z};

        // Ajouter le point au vector
        pointsIle.push_back(point);
    }

    // Fermer le fichier
    fichier.close();

    // ouvrir le graf
    opengraphsize(1280, 500);


    // Triangulation et triangulation de delaunay
    std::vector<Point> points = {};

    // création des point
    for (int i = 0; i < 1000; i++) {
        points.emplace_back(rand() % SCREEN_W, rand() % SCREEN_H, 0);
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
    //newc.AllTriangles();

    // Nom du fichier .obj
    const char* nomFichierObj = "C:\\Users\\etipi\\CLionProjects\\IleProject\\FinalIsland.obj";

    // Ouvrir le fichier en mode écriture
    std::ofstream fichierObj(nomFichierObj);

    // Vérifier si l'ouverture a réussi
    if (!fichierObj) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << nomFichierObj << " en écriture." << std::endl;
        return 1;
    }
    fichierObj << "mtllib maTexture.mtl"<< std::endl;
    // Écrire les points dans le fichier .obj
    for (int i = 0; i < newc.nbSommets(); ++i) {
        fichierObj << "v " << newc.sommet(i)->coordonnees().x() << " " << newc.sommet(i)->coordonnees().y() << " " << newc.sommet(i)->coordonnees().z() << std::endl;
    }

    for (const auto& point : newc.AllTriangles()) {
        if (newc.sommet(point.point1)->coordonnees().z() == 0 && newc.sommet(point.point2)->coordonnees().z() == 0 && newc.sommet(point.point3)->coordonnees().z() == 0){
            fichierObj << "usemtl Eau"<< std::endl;
        }
        if (newc.sommet(point.point3)->coordonnees().z() < 70 && (newc.sommet(point.point3)->coordonnees().z() >= 1 || newc.sommet(point.point1)->coordonnees().z() >= 1 || newc.sommet(point.point2)->coordonnees().z() >= 1)){
            fichierObj << "usemtl Sable"<< std::endl;
        }
        if (newc.sommet(point.point3)->coordonnees().z() < 500 && newc.sommet(point.point3)->coordonnees().z() >= 70){
            fichierObj << "usemtl Gazon"<< std::endl;
        }
        if (newc.sommet(point.point3)->coordonnees().z() >= 500){
            fichierObj << "usemtl Neige"<< std::endl;
        }

        fichierObj << "f " << point.point1+1 << " " << point.point2+1 << " " << point.point3+1 << std::endl;
    }

    // Fermer le fichier
    fichierObj.close();

    trace(newc);

    getch();

    closegraph();
    return 0;
}
