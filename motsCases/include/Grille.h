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

using namespace std;

enum Orientation { HORIZONTAL, VERTICAL, INTERSECTION };

struct Espace{
    Vecteur position;
    Orientation orientation;
    int longueur;
    // utilisé uniquement pour la génération
    string mot;
};


class Grille
{
	private:
		int h;
		int l;
        vector< vector<bool> > etatGrille;
        int note;

	public:		
        map<int, vector<string> > dictionnaire;
        vector<Espace> espaces;
		// getters et setters
		Grille();
		~Grille();
		void setH(int val);
		int getH();
		void setL(int val);
		int getL();
		// les fonctions
		bool chargerGrille(const string& nomFichier);
		bool chargerMots(const string& nomFichier);
		void genererEspaces();
		void afficherGrille();
		void afficherDictionnaire();
		void afficherEspaces();
		void trouverIntersections();
};

#endif // GRILLE_H_INCLUDED
