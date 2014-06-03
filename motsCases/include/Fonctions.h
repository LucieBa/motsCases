#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include "Grille.h"

#define RAND(min, max) rand() % (max-min) + min


vector<Espace> genererPopulation(const Grille& grille);
void attribuerNote(std::vector<Grille*> population);
std::vector<Grille*> roueBiaisee(std::vector<Grille*> population);
void croisement(std::vector<Grille*> population);


#endif // FONCTIONS_H_INCLUDED