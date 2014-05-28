#include <SFML/Graphics.hpp>
#include "include/Grille.h"
#include <string.h>

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
    Grille grille;
    if( grille.chargerGrille("data/grille2-2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement de la grille." << std::endl;
    if( grille.chargerMots("data/mots2.txt") == false)
        std::cout << "Une erreur s'est produite lors du chargement des mots." << std::endl;
    //grille.afficherGrille();
    //*grille.afficherDictionnaire();*/
    //bool chargement = chargerMots("data/mots2.txt");
    grille.genererEspaces();
    grille.trouverIntersections();
    grille.afficherEspaces();

    /*char *element = "Hello World";
    std::cout << (unsigned long)strlen(element) << std::endl;*/

    

    return 0;
}
