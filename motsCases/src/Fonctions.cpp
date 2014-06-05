#include "../include/Fonctions.h"

/*
int calculNoteMaximale(std::vector<Generation>& generations)
{
    int noteMax = 0;

    for(unsigned int i = 0 ; i < generations.size() ; i++)
    {
        noteMax = (noteMax > generations.at(i).note) ? noteMax : generations.at(i).note;
    }

    return noteMax;
}*/

////////////////////////////////////////////////////////////////////////////////////////////////////
//      Génétique
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Proposition> genererPopulation(Grille& grille)
{
   // Vecteur à retourner
   std::vector<Proposition> population;
   // Liste des mots déjà utilisés
   std::map<int, int> motsCompteurs;
   std::vector<std::string> motUtilises;
   // pour chaque espaces détectés
   for(unsigned int j = 0 ; j < grille.espaces.size() ; j++)
   {
      // Récupère la longueur de l'espace
      int longueur = grille.espaces.at(j).longueur;
      if(longueur == 0)
          continue;

      // Récupère le vecteur contenant tous les mots correspondants à la longueur
      std::map<int, std::vector<std::string> >::iterator listeMots = grille.dictionnaire.find(longueur);
      if(listeMots != grille.dictionnaire.end())
      {
          int random = 0;
          int nombreMots = listeMots->second.size();
          if(motsCompteurs.find(longueur) != motsCompteurs.end() && motsCompteurs[longueur] == nombreMots)
          {
            std::cout << "Grille invalide !!!" << std::endl;
            throw 0;
          }
          if(nombreMots != 1)
          {
              do
              {
                  random = std::rand() % nombreMots;
              }while(std::find(motUtilises.begin(), motUtilises.end(), listeMots->second.at(random)) != motUtilises.end());
          }
          // on indique que le mot est désormais utilisé
          motUtilises.push_back(listeMots->second.at(random));
          Proposition proposition;
          proposition.position.x = grille.espaces.at(j).position.x;
          proposition.position.y = grille.espaces.at(j).position.y;
          proposition.mot = listeMots->second.at(random);
          proposition.orientation = grille.espaces.at(j).orientation;
          proposition.longueur = grille.espaces.at(j).longueur;
          population.push_back(proposition);
          motsCompteurs[proposition.longueur]++;
      }
   }
    return population;
}

int attribuerNote(Grille& grille, std::vector<Proposition>& propositions)
{
    std::vector< std::vector<char> > tempGrille;
    // initialise la grille
    tempGrille.resize(grille.getL());
    for(unsigned int i = 0; i < grille.getL() ; i++)
    {
        tempGrille.at(i).resize(grille.getH());
        for(unsigned int j = 0; j < grille.getH() ; j++)
        {
            tempGrille.at(i).at(j) = '0';
        }
    }

    // remplissage de la grille avec les mots
    for(unsigned int a = 0 ; a < propositions.size() ; a++)
    {
        if(propositions.at(a).orientation == HORIZONTAL)
        {
            for(int i = 0 ; i < propositions.at(a).longueur ; i++)
            {
                char cell = tempGrille.at(propositions.at(a).position.x + i).at(propositions.at(a).position.y);
                if(cell == '0' || cell == propositions.at(a).mot.at(i))
                    tempGrille.at(propositions.at(a).position.x + i).at(propositions.at(a).position.y) = propositions.at(a).mot.at(i);
                else
                    tempGrille.at(propositions.at(a).position.x + i).at(propositions.at(a).position.y) = '1';
            }
        }
    }
    // Vertical
    for(unsigned int a = 0 ; a < propositions.size() ; a++)
    {
        if(propositions.at(a).orientation == VERTICAL)
        {
            for(int i = 0 ; i < propositions.at(a).longueur ; i++)
            {
                char cell = tempGrille.at(propositions.at(a).position.x).at(propositions.at(a).position.y + i);
                if(cell == '0' || cell == propositions.at(a).mot.at(i))
                    tempGrille.at(propositions.at(a).position.x).at(propositions.at(a).position.y + i) = propositions.at(a).mot.at(i);
                else
                    tempGrille.at(propositions.at(a).position.x).at(propositions.at(a).position.y + i) = '1';
            }
        }
    }

    // on parcout les cases pour attribuer une note
    int note = 0;
    for(unsigned int i = 0; i < grille.getL() ; i++)
    {
        for(unsigned int j = 0; j < grille.getH() ; j++)
        {
            if(tempGrille.at(i).at(j) == '1')
                note++;
            else if(tempGrille.at(i).at(j) == '2')
                note+=10;
        }
    }
    return note;
}

std::vector<Generation> roueBiaisee(std::vector<Generation>& generations, int noteMaximale )
{
    // Calcul taille nouvelle population
    unsigned long newPopulationSize = generations.size() / 2;
    if( newPopulationSize % 2 != 0 )
        newPopulationSize -= 1;

    int noteCumule = 0;
    for (int i = 0; i < generations.size(); i++ )
        noteCumule += generations.at(i).note;

    // Populate
    std::vector<Generation> newPopulation;
    do
    {
        int minGrade     = rand() % noteCumule;
        int currentGrade = 0;

        for( unsigned int i = 0; i < generations.size(); i++ )
        {
            currentGrade += generations.at(i).note;
            if( currentGrade >= minGrade )
            {
                newPopulation.push_back(generations.at(i));
                generations.at(i).note = 0;
                break;
            }
        }
    } while(newPopulation.size() < newPopulationSize);

    return newPopulation;
}

void croisement(std::vector<Generation>& generations)
{
    if(generations.size() <= 1)
        return;

    // enjambement
    for(unsigned int i = 0; i < generations.size(); i+=2 )
    {
        Generation& mother = generations.at(i);
        Generation& father = generations.at(i+1);

        int fixedPoint = 3;
        if(RAND(0, 100) <= 70)
            fixedPoint = RAND(0, mother.propositions.size());

        for( int j = 0; j < fixedPoint; j++ )
        {
          Proposition& motherProposition = mother.propositions.at(j);
          mother.propositions.at(j) = father.propositions.at(j);
          father.propositions.at(j) = motherProposition;
        }
    }
/*
    // mutation
    for(unsigned int i = 0; i < generations->size(); i++ )
    {
        // 1% de chance de tomber sur la valeur, ici 50
        if(RAND(0, 100) == 50)
        {
            int attributeID = RAND(0, ATTRIBUTE_COUNT);
            generations->at(i)->setAttribute(attributeID, Catapulte::getAttributeRandValue(attributeID));
        }
    }
*/
}
