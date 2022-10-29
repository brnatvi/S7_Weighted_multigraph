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
        const Sommet *sommet1; // "une arete est definie, une fois pour toutes, par deux sommets, ses extremites" => const
        const Sommet *sommet2;
        int poids; 
        int nbReference;
        string sommet1_nom; // copie de nom pour etre sure qu'il toujours existe apres sommet1 destruction
        string sommet2_nom; // copie de nom pour etre sure qu'il toujours existe apres sommet1 destruction

    public :
        Arete(const string &nom1, const string &nom2, int poids);
        Arete(const Sommet *s1, const Sommet *s2, int poids);
        Arete(const Arete *a); // "a partir d'une arete existante" => pas de poids
        ~Arete();

        // ===================  getters / setters ===========================================================
        static int getCounterAretes()   { return counterArete; };

        int getPoids() const     { return poids; }
        int getRef() const       { return nbReference; }
        void setPoids(int poids) { this->poids = poids; }
        void setRef(int nbRef)   { nbReference = nbRef; }
        Arete::Pair getSommetsPair() const {return {this->sommet1, this->sommet2};}

};

ostream &operator << (ostream &out, Arete &x);


#endif