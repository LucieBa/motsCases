#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
#include "Sommet.h"
#include "Arete.h"



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

bool chargerSommetNom(const std::string& nomFichier, std::vector<Sommet>& sommets);
bool chargerSommetPosition(const std::string& nomFichier, std::vector<Sommet>& sommets);
bool chargerLignes(const std::string& nomFichier, std::vector<Ligne>& lignes);
bool chargerAretes(const std::string& nomFichier, std::vector<Arete>& aretes, std::vector<Ligne>& lignes, std::vector<Sommet>& sommets);
void afficherSommets(std::vector<Sommet>& sommets);
void afficherLignes(std::vector<Ligne>& lignes);
int trouverLigne(std::vector<Ligne>& lignes, std::string texte);
int trouverArete(std::vector<Arete> aretes, std::string texte);
int trouverSommet(std::vector<Sommet> sommets, int indice);

#endif // FICHIER_H_INCLUDED
