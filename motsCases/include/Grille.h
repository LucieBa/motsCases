#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "Vecteur.h"


enum Orientation { HORIZONTAL, VERTICAL };

struct Espace{
    Vecteur position;
    Orientation orientation;
    int longueur;
};

struct Proposition:public Espace{
    std::string mot;
};


class Grille
{
	private:
		int h;
		int l;
        std::vector< std::vector<bool> > etatGrille;

	public:
        std::map<int, std::vector<std::string> > dictionnaire;
        std::vector<Espace> espaces;
        std::vector<Vecteur> intersections;
		// getters et setters
		Grille();
		~Grille();
		void setH(int val);
		int getH();
		void setL(int val);
		int getL();
		int getNoteMax();
		// les fonctions
		bool chargerGrille(const std::string& nomFichier);
		bool chargerMots(const std::string& nomFichier);
		void genererEspaces();
		void afficherGrille();
		void afficherDictionnaire();
		void afficherEspaces();
		void afficherGeneration( const std::vector<Proposition>& propositions );
		void afficherIntersections();
		void trouverIntersections();
};

#endif // GRILLE_H_INCLUDED
