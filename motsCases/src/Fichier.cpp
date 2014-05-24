#include "../include/Fichier.h"
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;


/*string supprimerAccents(string message)
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
}*/

/*********************************************************************************************
*                                   Chargement des fichiers
*********************************************************************************************/
bool chargerMots(const std::string& nomFichier)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        string ligne;
        while(getline(fichier, ligne))
        {
            // todo : vérifications sur le mots : pas d'espaces, pas de caractères spéciaux...
            ligne = supprimerAccents(ligne);
            // todo : tronquer les espaces
            std::transform(ligne.begin(), ligne.end(), ligne.begin(), ::toupper);
            cout << ligne.size() << endl;
            
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }
    return true;
}

/*bool chargerSommetPosition(const std::string& nomFichier, std::vector<Sommet>& sommets)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        string ligne;
        int i = 0;
        while(getline(fichier, ligne))
        {
            vector<string> elements;
            split(ligne, ' ', elements);
            sommets.at(i).Setposition(atoi(elements.at(1).c_str()), atoi(elements.at(2).c_str()));
            i++;
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }
    return true;
}

bool chargerLignes(const std::string& nomFichier, std::vector<Ligne>& lignes)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        string ligne;
        while(getline(fichier, ligne))
        {
            // récupération de la chaine + split
            vector<string> elements;
            split(ligne, ' ', elements);
            // création du nouveau sommet
            Ligne ligne;
            ligne.Setnom(elements.at(0));
            ligne.Setr(atoi(elements.at(1).c_str()));
            ligne.Setg(atoi(elements.at(2).c_str()));
            ligne.Setb(atoi(elements.at(3).c_str()));
            // on enregistre dans la liste des sommets
            lignes.push_back(ligne);
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }
    return true;
}

bool chargerAretes(const std::string& nomFichier, std::vector<Arete>& aretes, std::vector<Ligne>& lignes, std::vector<Sommet>& sommets)
{
    ifstream fichier(nomFichier.c_str(), ios::in);
    if(fichier)
    {
        int i = 0;
        string ligne;
        while(getline(fichier, ligne))
        {
            // récupération de la chaine + split
            vector<string> elements;
            split(ligne, ' ', elements);

            // on récupère les sommets qui composent l'arête
            // création d'une arête
            Arete arete;
            int sommet1 = trouverSommet(sommets, atoi(elements.at(0).c_str()));
            int sommet2 = trouverSommet(sommets, atoi(elements.at(1).c_str()));
            arete.Setsommet1(&sommets.at(sommet1));
            arete.Setsommet2(&sommets.at(sommet2));
            // on impute une valeur à l'arete
            arete.Setvaleur(atoi(elements.at(2).c_str()));
            arete.Setindice(i);
            i++;
            aretes.push_back(arete);
            // on attribue l'arete à une ligne
            int ligne = trouverLigne(lignes, elements.at(3));
            if(ligne == -1)
            {
                cout << "impossible de trouver la ligne " << elements.at(3) << endl;
                return false;
            }
            lignes.at(ligne).ajouterArete(arete);
        }
    }
    else
    {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }
    return true;
}


/*********************************************************************************************
*                                   Affichages
*********************************************************************************************/
/*void afficherSommets(std::vector<Sommet>& sommets)
{
    for(int i=0;i<sommets.size(); i++)
        cout << sommets.at(i).Getindice() << " " << sommets.at(i).Getnom() << endl;
}

void afficherLignes(std::vector<Ligne>& lignes)
{
    for(int i=0;i<lignes.size(); i++)
        cout << lignes.at(i).Getnom() << " " << lignes.at(i).Getr() << " " << lignes.at(i).Getg() << " " << lignes.at(i).Getb() <<endl;
}


/*********************************************************************************************
*
*********************************************************************************************/
/*int trouverLigne(std::vector<Ligne>& lignes, string texte)
{
    for(int i = 0 ; i < lignes.size() ; i++)
    {
        if(texte == lignes.at(i).Getnom())
            return i;
    }
    return -1;
}

/*int trouverArete(std::vector<Arete> aretes, string texte)
{
    for(int i = 0 ; i < aretes.size() ; i++)
    {
        if(texte == aretes.at(i).Getnom())
            return i;
    }
    return NULL;
}*/

/*int trouverSommet(std::vector<Sommet> sommets, int indice)
{
    for(int i = 0 ; i < sommets.size() ; i++)
    {
        if(indice == sommets.at(i).Getindice())
            return i;
    }
    return -1;
}*/
