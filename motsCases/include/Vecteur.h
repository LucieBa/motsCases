#ifndef VECTEUR_H
#define VECTEUR_H


class Vecteur
{
    public:
        Vecteur();
        Vecteur(int x, int y);
        virtual ~Vecteur();
        /*unsigned int Getx();
        void Setx(unsigned int val);
        unsigned int Gety();   
        void Sety(unsigned int val);*/
        unsigned int x;
        unsigned int y;
        void setCord(int x, int y);
};

#endif // VECTEUR_H
