#include "../include/Vecteur.h"


Vecteur::Vecteur()
{

}

Vecteur::Vecteur(int x, int y)
{
    this-> x = x;
    this-> y = y;
}

Vecteur::~Vecteur()
{
    //dtor
}

/*unsigned int Vecteur::Getx()
{
	return x; 
}

void Vecteur::Setx(unsigned int val)
{
	x = val; 
}

unsigned int Vecteur::Gety()
{
	return y; 
}

void Vecteur::Sety(unsigned int val)
{
	y = val; 
}*/

void Vecteur::setCord(int x, int y)
{
	this-> x = x;
    this-> y = y;
}