#include "../include/Grille.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//      Autres fonctions (non objet)
////////////////////////////////////////////////////////////////////////////////////////////////////

string supprimerAccents(string message)
{
    string accent("ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÿÑñÇç");
    string sansAccent("AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuyNnCc");
    int i=0,j=0,k=0,taille;

    taille=message.size();

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
                taille=message.size();
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

////////////////////////////////////////////////////////////////////////////////////////////////////
//		Fonctions
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Grille::chargerGrille(const std::string& nomFichier)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        int i = -1;
        string ligne;
        while(getline(fichier, ligne))
        {
            i++;
            // on ignore les lignes de commentaires
            if( i == 0 || i == 2 )
                continue;
            else if( i == 1 )
            {
                // si c'est la deuxième ligne, alors il s'agit de la taille du tableau.
                vector<string> elements;
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
                vector<string> elements;
                split(ligne, ' ', elements);
                int x = atoi(elements.at(0).c_str());
                int y = atoi(elements.at(1).c_str());
                etatGrille.at(x).at(y) = false;
            }
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }
    return true;
}

bool Grille::chargerMots(const std::string& nomFichier)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        string ligne;
        while(getline(fichier, ligne))
        {
            // todo : vérifications sur le mots : pas d'espaces, pas de caractères spéciaux...
            ligne = supprimerAccents(ligne);
            // todo : tronquer les espaces et les chiffres
            std::transform(ligne.begin(), ligne.end(), ligne.begin(), ::toupper);
            this->dictionnaire[ligne.size()].push_back(ligne);
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
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
            std::cout << (( this->etatGrille.at(j).at(i) == true) ? "o" : " ") << " ";
        }
        std::cout << std::endl;
    }
}


void Grille::afficherDictionnaire()
{
    for(int i = 0; i < this->dictionnaire.size() ; i++)
    {
        if(this->dictionnaire[i].size() != 0)
        {
            std::cout << "Mots de " << i << " caracteres : "<< std::endl;
            for(int j = 0; j < this->dictionnaire[i].size() ; j++)
            {
                std::cout << this->dictionnaire[i].at(j)<< std::endl;
            }
        }
    }
}

void Grille::genererEspaces()
{
    std::vector<Vecteur> espaceMot;
    //Vecteur v = Vecteur(0, 0);
    // boucle pour parcourir les x
    for(int i = 0; i < this->h ; i++)
    {
        for(int j = 0 ; j < this->l ; j++)
        {
            if(etatGrille.at(j).at(i) == true)
            {
                Vecteur v = Vecteur(j, i);
                espaceMot.push_back(v);
                std::cout << i << " et " << j << std::endl;
                std::cout << espaceMot.size() << std::endl;
            }
            else if(etatGrille.at(j).at(i) == false)
            {
                if(espaceMot.size() == 0)
                {
                    std::cout << i << " et " << j << std::endl;
                    std::cout << "false et 0" << std::endl;
                }
                else if(espaceMot.size() == 1)
                {
                    espaceMot.pop_back();
                }
            }
        }
    }

    //v.setCord(0, 0);
    // boucle pour parcourir les y
    /*for(int m = 0; m < this->l ; m++)
    {
        for(int n = 0 ; n < this->h ; n++)
        {
            if(etatGrille.at(m).at(n) == false)
            {
                //std::cout << n << " et " << m << std::endl;
            }
        }
    }*/
}
