#include "../include/Grille.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//      Autres fonctions (non objet)
////////////////////////////////////////////////////////////////////////////////////////////////////

std::string supprimerAccents(std::string message)
{
    std::string accent("ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç");
    std::string sansAccent("AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc");
    int i=0,j=0,k=0,taille;

    taille= (int) message.size();

    for (i=0;i<=taille;i++)
    {
        for(j=0;j<=104;j=j+2)
        {
            if((message[i]==accent[j])&&(message[i+1]==accent[j+1]))
            {
                message[i]=sansAccent[j/2];
                for(k=i+1;k<taille;k++)
                {
                    message[k]=message[k+1];
                }
                message=message.substr(0,taille-1);
                taille= (int) message.size();
            }
        }
    }
    return message;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//		Constructeur, destructeur, setters, getters
////////////////////////////////////////////////////////////////////////////////////////////////////

Grille::Grille()
{
}

Grille::~Grille()
{

}

void Grille::setH(int val)
{
    this->h = val;
}

int Grille::getH()
{
    return this->h;
}

void Grille::setL(int val)
{
    this->l = val;
}

int Grille::getL()
{
    return this->l;
}

int Grille::getNoteMax()
{
    return (int) (this->intersections.size() * 10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//		Fonctions
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Grille::chargerGrille(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier.c_str(), std::ios::in);
    if(fichier)
    {
        int i = -1;
        std::string ligne;
        while(getline(fichier, ligne))
        {
            i++;
            // on ignore les lignes de commentaires
            if( i == 0 || i == 2 )
                continue;
            else if( i == 1 )
            {
                // si c'est la deuxième ligne, alors il s'agit de la taille du tableau.
                std::vector<std::string> elements;
                split(ligne, ' ', elements);
                this->l = atoi(elements.at(0).c_str());
                this->h = atoi(elements.at(1).c_str());
                etatGrille.resize(this->l);
                // Par défaut on met toutes les cases à true
                for(int j = 0 ; j < this->l ; j++)
                {
                    etatGrille.at(j).resize(this->h);
                    for(int k = 0 ; k < this->h ; k++)
                        etatGrille.at(j).at(k) = true;
                }
            }
            else
            {
                // ensuite, on traite les cases qui sont bloquées
                std::vector<std::string> elements;
                split(ligne, ' ', elements);
                int x = atoi(elements.at(0).c_str());
                int y = atoi(elements.at(1).c_str());
                etatGrille.at(x).at(y) = false;
            }
        }
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier : " << nomFichier << std::endl;
        return false;
    }
    return true;
}

bool Grille::chargerMots(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier.c_str(), std::ios::in);
    if(fichier)
    {
        std::string ligne;
        while(getline(fichier, ligne))
        {
            // todo : vérifications sur le mots : pas d'espaces, pas de caractères spéciaux...
            ligne = supprimerAccents(ligne);
            // todo : tronquer les espaces et les chiffres
            std::transform(ligne.begin(), ligne.end(), ligne.begin(), ::toupper);
            this->dictionnaire[(int)ligne.size()].push_back(ligne);
        }
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier : " << nomFichier << std::endl;
        return false;
    }
    return true;
}

void Grille::afficherGrille()
{
    for(int i = 0; i < this->h ; i++)
    {
        for(int j = 0; j < this->l ; j++)
        {
            std::cout << (( this->etatGrille.at(j).at(i) == true) ? "o" : "x") << " ";
        }
        std::cout << std::endl;
    }
}


void Grille::afficherDictionnaire()
{
    for(unsigned int i = 0; i < this->dictionnaire.size() ; i++)
    {
        if(this->dictionnaire[i].size() != 0)
        {
            std::cout << "Mots de " << i << " caracteres : "<< std::endl;
            for(unsigned int j = 0; j < this->dictionnaire[i].size() ; j++)
            {
                std::cout << this->dictionnaire[i].at(j)<< std::endl;
            }
        }
    }
}

void Grille::afficherIntersections()
{
    for(int i = 0; i < this->h ; i++)
    {
        for(int j = 0; j < this->l ; j++)
        {
            bool intersectionAffiche = false;

            for( int k = 0; k < intersections.size(); k++ )
            {
                if( intersections.at(k).x == j && intersections.at(k).y == i )
                {
                    std::cout << "x";
                    intersectionAffiche = true;
                    break;
                }
            }

            if( intersectionAffiche == false )
                std::cout << "o";

            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Grille::genererEspaces()
{
    int longueur = 0;

    this->espaces.clear();

    // on s'occupe de l'horizontal
    for(int i = 0; i < this->h ; i++)
    {
        for(int j = 0 ; j < this->l ; j++)
        {
            if(etatGrille.at(j).at(i) == true)
            {
                longueur++;
            }
            else if(etatGrille.at(j).at(i) == false)
            {
                if(longueur > 1)
                {
                    Espace espace;
                    espace.position = Vecteur(j-longueur, i);
                    espace.orientation = HORIZONTAL;
                    espace.longueur = longueur;
                    this->espaces.push_back(espace);
                }
                longueur = 0;
            }
        }

        // arrivé en fin de ligne
        if(longueur > 1)
        {
            Espace espace;
            espace.position = Vecteur(this->l - longueur, i);
            espace.orientation = HORIZONTAL;
            espace.longueur = longueur;
            this->espaces.push_back(espace);
        }
        longueur = 0;
    }

    // on s'occupe du vertical
    for(int i = 0; i < this->l ; i++)
    {
        for(int j = 0 ; j < this->h ; j++)
        {
            if(etatGrille.at(i).at(j) == true)
            {
                longueur++;
            }
            else if(etatGrille.at(i).at(j) == false)
            {
                if(longueur > 1)
                {
                    Espace espace;
                    espace.position = Vecteur(i, j-longueur);
                    espace.orientation = VERTICAL;
                    espace.longueur = longueur;
                    this->espaces.push_back(espace);
                }
                longueur = 0;
            }
        }

        // arrivé en fin de ligne
        if(longueur > 1)
        {
            Espace espace;
            espace.position = Vecteur(i, this->h - longueur);
            espace.orientation = VERTICAL;
            espace.longueur = longueur;
            this->espaces.push_back(espace);
        }
        longueur = 0;
    }
}

void Grille::afficherEspaces()
{
    for(unsigned int i = 0 ; i < espaces.size() ; i++)
    {
        std::cout << "Position de depart :  x = " << espaces.at(i).position.x << " et y = " << espaces.at(i).position.y;
        std::cout << ". Longueur du mot : " << espaces.at(i).longueur;
        std::cout << ". Le mot est en : " << espaces.at(i).orientation << std::endl;
    }
}

void Grille::afficherGeneration( const std::vector<Proposition>& propositions )
{
	// On crée un tableau qu'on va remplir avec les lettres.
	std::vector<std::vector<int>> array;
	array.resize(this->getH());
	for( int i = 0; i < array.size(); i++)
		array.at(i).resize(this->getL());
	
	// On remplis le tableau de croix par defaut.
	for( int i = 0; i < array.size(); i++ )
		for( int j = 0; j < array.at(i).size(); j++ )
			array.at(i).at(j) = -1;
	
	// On remplis le tableau avec la liste de propositions.
	for( int i = 0; i < propositions.size(); i++)
    {
		const Proposition& proposition = propositions.at(i);

        if( proposition.orientation == HORIZONTAL )
        {
            for( int j = 0; j < proposition.mot.size(); j++)
            {
				array.at(proposition.position.y).at(proposition.position.x + j) = proposition.mot.at(j);
            }
        }
        else
        {
			for( int j = 0; j < propositions.at(i).mot.size(); j++)
			{
				//array.at(proposition.position.y+j).at(proposition.position.x) = proposition.mot.at(j);
			}
		}
	}

	// On transforme le tableau en chaine à afficher tout en mettant en forme le tout.
	for( int i = 0; i < array.size(); i++ )
	{
		for( int j = 0; j < array.at(i).size(); j++ )
		{
			if( array.at(i).at(j) == -1 )
				std::cout << (char) 35;		// Affiche le caractere "#"
			else
				std::cout << (char) array.at(i).at(j);

			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void Grille::trouverIntersections()
{
    std::vector<Vecteur> cases;
    // Horizontal
    for(unsigned int a = 0 ; a < this->espaces.size() ; a++)
    {
        if(this->espaces.at(a).orientation == HORIZONTAL)
        {
            for(int i = 0 ; i < this->espaces.at(a).longueur ; i++)
            {
                cases.push_back(Vecteur(this->espaces.at(a).position.x + i, this->espaces.at(a).position.y));
            }
        }
    }
    // Vertical
    for(unsigned int a = 0 ; a < this->espaces.size() ; a++)
    {
        if(this->espaces.at(a).orientation == VERTICAL)
        {
            for(int i = 0 ; i < this->espaces.at(a).longueur ; i++)
            {
                cases.push_back(Vecteur(this->espaces.at(a).position.x, this->espaces.at(a).position.y+i));
            }
        }
    }
    for(unsigned int i = 0 ; i < cases.size() ; i++)
    {
        for(unsigned int j = 0 ; j < cases.size() ; j++)
        {
            if( i != j )
            {
                if(cases.at(i).x == cases.at(j).x && cases.at(i).y == cases.at(j).y)
                {
                    bool present = false;

                    // On verifie que l'intersection n'est pas déjà présente
                    for( int k =0; k < intersections.size(); k++ )
                    {
                        if( cases.at(i).x == intersections.at(k).x && cases.at(i).y == intersections.at(k).y )
                        {
                            present = true;
                            break;
                        }
                    }

                    if( present == false )
                        intersections.push_back(Vecteur(cases.at(i).x, cases.at(i).y));
                }
            }

        }
    }
}


