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

using namespace std;

class Grille
{
	private:
		int h;
		int l;
        map<int, vector<string> > dictionnaire;
        vector< vector<bool> > etatGrille; 
	public:
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
		void afficherGrille();
		void afficherDictionnaire();
};

#endif // GRILLE_H_INCLUDED
