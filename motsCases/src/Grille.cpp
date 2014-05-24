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
                //
                this->l = 5;
                this->h = 3;               
                etatGrille.resize(this->l);
                for(int j = 0 ; j < this->l ; j++)
                {
                    etatGrille.at(j).resize(this->h);
                    for(int k = 0 ; k < this->h ; k++)
                        etatGrille.at(j).at(k) = true;
                }
            }
            else
            {
                //
                int x = 1;
                int y = 0;
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
            std::cout << (( this->etatGrille.at(j).at(i) == true) ? "o" : "x") << " ";
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
