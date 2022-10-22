#ifndef ARETE_H
#define ARETE_H

#include "Sommet.hpp"
#include <list>


using namespace std;

class Arete {
    public :
        struct Pair {
            const Sommet *sommet1;
            const Sommet *sommet2;
        };

    private :
        static int counterArete;
        // pourquoi enlever const ici ?
        const Sommet *sommet1; // "une arete est definie, une fois pour toutes, par deux sommets, ses extremites" => const
        const Sommet *sommet2;
        int poids; // "peut etre modifie" => no const
        int nbReference;

    public :
        Arete(string nom1, string nom2, int poids);
        Arete(const Sommet *s1, const Sommet *s2, int poids);
        Arete(Arete *a); // "a partir d'une arete existante" => pas de poids

    public :  
        Arete::Pair getSommetsPair() const;
        int getPoids() const;
        int getRef() const;
        void setPoids(int poids);
        void setRef(int nbRef);

//        void incrReference();
//        void decrReference();
};

ostream &operator << (ostream &out, Arete &x);


#endif