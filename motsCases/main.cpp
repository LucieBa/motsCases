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
    std::srand((unsigned int)std::time(0));
	bool debug = true;	// True = affiche des informations sur la grille.
    Grille grille;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interactions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "--------------------------------" << std::endl;
    std::cout << "\\ Bienvenue dans \"Mot croises\" / " << std::endl;
	std::cout << "--------------------------------" << std::endl;
	
	// Noms des fichiers par defaut a charger.
	std::string nomGrille	 = "grille2";
	std::string nomListeMots = "mots2";
	
	// Invite de commande.
	{
		std::cout << "Nom de la grille a charger (sans extension) : ";
		std::cin >> nomGrille;
		std::cin.clear();
		std::cin.ignore();
		
		std::cout << "Nom de la liste de mots a charger (sans extension) : ";
		std::cin >> nomListeMots;
		std::cin.clear();
		std::cin.ignore();
	}
	
	
    if( grille.chargerGrille("data/" + nomGrille + ".txt") == false)
	{
        std::cout << "Une erreur s'est produite lors du chargement de la grille." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "-> Chargement du fichier " << nomGrille << ".txt : OK" << std::endl;

    if( grille.chargerMots("data/" + nomListeMots + ".txt") == false)
	{
        std::cout << "Une erreur s'est produite lors du chargement des mots." << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "-> Chargement du fichier " << nomListeMots << ".txt : OK" << std::endl;

    grille.genererEspaces();
    grille.trouverIntersections();
	
	// Test: Affiche certaines informations sur la grille en cours.
	if(debug)
	{
		std::cout << std::endl << "Grille : " << std::endl;
		std::cout << "----------------------" << std::endl;
		grille.afficherGrille();
		std::cout << std::endl << "Liste des mots : " << std::endl;
		std::cout << "----------------------" << std::endl;
		grille.afficherDictionnaire();
		std::cout << std::endl << "Espaces trouves : " << std::endl;
		std::cout << "----------------------" << std::endl;
		grille.afficherEspaces();
		std::cout << std::endl << "Position des intersections : " << std::endl;
		std::cout << "----------------------" << std::endl;
		grille.afficherIntersections();
	}
	
    int taillePop = 2000;
   /* std::cout << "Taille initiale de la population : ";
    std::cin >> taillePop;
	std::cin.clear();
	std::cin.ignore();*/
/*
    int tauxMutation = 1;
    std::cout << "Taux de mutation de la population : ";
    std::cin >> tauxMutation;
	std::cin.clear();
	std::cin.ignore();*/

    // Génération de la population + attribution de la note
    std::vector<Generation> generations;
    for( unsigned int j = 0 ; j< taillePop; j++ )
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

	std::cout << std::endl << "----------------------" << std::endl;
    std::cout << "Grille terminee (note: " << generationFinale.note << ")" << std::endl;
	std::cout << "----------------------" << std::endl;
    grille.afficherGeneration(generationFinale.propositions);

	std::cout << std::endl << std::endl;
    return 0;
}
