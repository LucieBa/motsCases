#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string.h>


std::string supprimerAccents(std::string message);

bool chargerMots(const std::string& nomFichier);

/*bool chargerSommetNom(const std::string& nomFichier, std::vector<Sommet>& sommets);
bool chargerSommetPosition(const std::string& nomFichier, std::vector<Sommet>& sommets);
bool chargerLignes(const std::string& nomFichier, std::vector<Ligne>& lignes);
bool chargerAretes(const std::string& nomFichier, std::vector<Arete>& aretes, std::vector<Ligne>& lignes, std::vector<Sommet>& sommets);
void afficherSommets(std::vector<Sommet>& sommets);
void afficherLignes(std::vector<Ligne>& lignes);
int trouverLigne(std::vector<Ligne>& lignes, std::string texte);
int trouverArete(std::vector<Arete> aretes, std::string texte);
int trouverSommet(std::vector<Sommet> sommets, int indice);
*/
#endif // FICHIER_H_INCLUDED
