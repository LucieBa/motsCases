#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <string>

#include "include/Grille.h"
#include "include/Fonctions.h"



int main()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Configuration
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //srand (time(NULL));
    std::srand(std::time(0));
    //bool play               = true;
    //bool success            = false;
    Grille grille;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interactions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "Vous etes dans la phase de configuration" << std::endl;
    // todo : invite de commande, quels sont les fichiers à dl
    if( grille.chargerGrille("data/grille2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement de la grille." << std::endl;
    if( grille.chargerMots("data/mots2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement des mots." << std::endl;
    grille.afficherGrille();
    std::cout << std::endl;
    //grille.afficherDictionnaire();
    //bool chargement = chargerMots("data/mots2.txt");
    grille.genererEspaces();
    grille.trouverIntersections();
    grille.afficherIntersections();
    //grille.afficherEspaces();

    /* todo : taille de la population
    int taillePop;
    std::cout << "Veuillez définir la taille initiale de la population : " << std::endl;
    std::cin >> taillePop;*/

    /* todo : taux de mutation
    int tauxMutation;
    std::cout << "Veuillez définir le taux de mutation de la population : " << std::endl;
    std::cin >> tauxMutation;*/

    // Génération de la population + attribution de la note

    std::vector<Generation> generations;
    for(unsigned int j=0 ; j<100 ; j++)
    {
        Generation generation;
        generation.propositions = genererPopulation(grille);
        generation.note = attribuerNote(grille, generation.propositions);
        generations.push_back(generation);
    }

    Generation generationFinale;
    do
    {
        std::vector<Generation> generationBiaisee = roueBiaisee( generations, grille.getNoteMax());

        // Dans le cas ou il ne reste qu'une seule generation.
        if( generationBiaisee.size() == 1 )
        {
            generationFinale = generationBiaisee.at(0);
            break;
        }
        else
        {
            // Dans le cas ou une generation atteint la note maximale (grille parfaite)
            for (int i = 0; i < generationBiaisee.size(); i++ )
            {
                if( generationBiaisee.at(i).note == grille.getNoteMax() )
                {
                    generationFinale = generationBiaisee.at(i);
                    break;
                }
            }
        }

        // On croise les generations.
        croisement(generationBiaisee);

        // On recommence avec la nouvelle generation.
        generations = generationBiaisee;

        // On met à jour les notes suite au croisement.
        for (int i = 0; i < generations.size(); i++ )
            generations.at(i).note = attribuerNote(grille, generations.at(i).propositions);

    } while(true);

    std::cout << "Grille terminee ! (note: " << generationFinale.note << ")" << std::endl;
    grille.afficherGeneration(generationFinale.propositions);

    /*char *element = "Hello World";
    std::cout << (unsigned long)strlen(element) << std::endl;*/

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    return 0;
}
