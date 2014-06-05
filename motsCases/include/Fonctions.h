#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "Grille.h"

#define RAND(min, max) rand() % (max-min) + min

struct Generation{
    std::vector<Proposition> propositions;
    int note;
};


std::vector<Proposition> genererPopulation(Grille& grille);
int attribuerNote(Grille& grille, std::vector<Proposition>& population);
std::vector<Generation> roueBiaisee(std::vector<Generation>& population, int noteMaximale);
void croisement(std::vector<Generation>& population);


#endif // FONCTIONS_H_INCLUDED
