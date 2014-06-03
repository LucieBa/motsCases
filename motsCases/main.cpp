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
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Configuration
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    srand( (unsigned int)time(NULL));
    vector<Espace> population;
    //bool play               = true;
    //bool success            = false;
    Grille grille;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Interactions
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // todo : invite de commande, quels sont les fichiers à dl
    if( grille.chargerGrille("data/grille2-2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement de la grille." << std::endl;
    if( grille.chargerMots("data/mots2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement des mots." << std::endl;
    //grille.afficherGrille();
    //grille.afficherDictionnaire();
    //bool chargement = chargerMots("data/mots2.txt");
    grille.genererEspaces();
    grille.trouverIntersections();
    //grille.afficherEspaces();
    /* todo : taille de la population
    int taillePop;
    std::cout << "Veuillez définir la taille initiale de la population : " << std::endl;
    std::cin >> taillePop;*/
    /* todo : taux de mutation
    int tauxMutation;
    std::cout << "Veuillez définir le taux de mutation de la population : " << std::endl;
    std::cin >> tauxMutation;*/

    // todo : générer la population

    population = genererPopulation(grille);
    std::cout << "population " << 0 << std::endl;
    for(int i=0 ; i<population.size() ; i++)
    {
        std::cout << population.at(i).mot << std::endl;
    }
    //attribuerNote(population);

    /*char *element = "Hello World";
    std::cout << (unsigned long)strlen(element) << std::endl;*/

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    return 0;
}
