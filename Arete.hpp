#ifndef ARETE_H
#define ARETE_H

#include "Sommet.hpp"
#include <list>


using namespace std;

class Arete {

    private :
        static int counterArete;
        const Sommet *sommet1; // "une arete est definie, une fois pour toutes, par deux sommets, ses extremites" => const
        const Sommet *sommet2;
        int poids; // "peut etre modifie" => no const
        int nbReference;

    public :
        Arete(string nom1, string nom2, int poids);
        Arete(Sommet *s1, Sommet *s2, int poids);
        Arete(Arete *a); // "a partir d'une arete existante" => pas de poids

    public :
        
        std::list<Sommet> getSommets(); 
        int getPoids();
        int getRef();
        void setPoids(int poids);
        void setRef(int nbRef);

//        void incrReference();
//        void decrReference();
};

ostream &operator << (ostream &out, Arete &x);


#endif