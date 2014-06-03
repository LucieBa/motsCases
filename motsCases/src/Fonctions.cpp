#include "../include/Fonctions.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
//      Génétique
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Espace> genererPopulation(const Grille& grille)
{
   std::vector<Espace> population;
   std::vector<string> motUtilises;
   // générer aléatoirement les mots toussa
   for(int j = 0 ; j < grille.espaces.size() ; j++)
   {
       if(grille.espaces.at(j).orientation != INTERSECTION)
       {
           int longueur = grille.espaces.at(j).longueur;
           if(longueur == 0)
                continue;
           map<int, vector<string> >::const_iterator listeMots = grille.dictionnaire.find(longueur);
           if(listeMots != grille.dictionnaire.end())
           {
               //std::cout << "t " << listeMots->second.size() << std::endl;
               bool trouve = false;
                int random = 0;
               do
               {
                    random = RAND(0, listeMots->second.size()-1);
                    std::cout << random << std::endl;
                    std::vector<string>::iterator it = std::find(motUtilises.begin(), motUtilises.end(), listeMots->second.at(random));
                    if(it == motUtilises.end())
                        trouve = true;
               }while(trouve != true);
               std::cout << "d" << std::endl;
                
               Espace espace;
               espace.mot = listeMots->second.at(random);
               espace.orientation = grille.espaces.at(j).orientation;
               espace.longueur = grille.espaces.at(j).longueur;
               population.push_back(espace);
               motUtilises.push_back(espace.mot);
               std::cout << "b" << std::endl;
           }
       }
   }
    return population;
}

void attribuerNote(std::vector<Grille*> population)
{
    for(int i = 0 ; i < population.size() ; i++ )
    {
        // si intersection 10, sinon 1
    }
}

std::vector<Grille*> roueBiaisee(std::vector<Grille*> population)
{
    // Calcul taille nouvelle population
    /*unsigned long newPopulationSize = population.size() / 2;
    if( newPopulationSize % 2 != 0 )
        newPopulationSize -= 1;

    const int totalGrade = computeTotalGrade(population);

    // Populate
    CatapulteVector newPopulation;
    do
    {
        int minGrade     = rand() % totalGrade;
        int currentGrade = 0;

        for( unsigned int i = 0; i < population.size(); i++ )
        {
            currentGrade += population[i]->getGrade();
            if( currentGrade >= minGrade )
            {
                newPopulation.push_back(population[i]);
                population[i]->setGrade(0);
                break;
            }
        }
    } while(newPopulation.size() < newPopulationSize);
    return newPopulation;*/
}

void croisement(std::vector<Grille*> population)
{
    /*if(population->size() <= 1)
        return;
    // enjambement
    for(unsigned int i = 0; i < population->size(); i+=2 )
    {
        Catapulte* mother = population->at(i);
        Catapulte* father = population->at(i+1);

        int fixedPoint = FIXED_POINT;
        if(RAND(0, 100) <= 70)
            fixedPoint = RAND(0, ATTRIBUTE_COUNT);

        // on stocke les valeurs actuelles des parents avant modification
        float motherAttributes[ATTRIBUTE_COUNT];
        float fatherAttributes[ATTRIBUTE_COUNT];
        mother->toArray(motherAttributes, ATTRIBUTE_COUNT);
        father->toArray(fatherAttributes, ATTRIBUTE_COUNT);

        for(int j = 0 ; j < fixedPoint ; j++)
        {
            mother->setAttribute(j, fatherAttributes[j]);
            father->setAttribute(j, motherAttributes[j]);
        }
    }

    // mutation
    for(unsigned int i = 0; i < population->size(); i++ )
    {
        // 1% de chance de tomber sur la valeur, ici 50
        if(RAND(0, 100) == 50)
        {
            int attributeID = RAND(0, ATTRIBUTE_COUNT);
            population->at(i)->setAttribute(attributeID, Catapulte::getAttributeRandValue(attributeID));
        }
    }*/
}

