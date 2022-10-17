#include "Sommet.h"
#include <array>
using namespace std;

class Arete {

    private :
        const Sommet *_sommet1; // "une arete est definie, une fois pour toutes, par deux sommets, ses extremites" => const
        const Sommet *_sommet2;
        int _poids; // "peut etre modifie" => no const
        int _nbReference = 0;

    public :
        Arete(string nom1, string nom2, int poids);
        Arete(Sommet *s1, Sommet *s2, int poids);
        Arete(Arete *a); // "a partir d'une arete existante" => pas de poids

    public :
        // a verifier + comment l'ecrire sur une ligne
        const Sommet* getSommets(){
            const Sommet* x[2] ;
            x[0] = _sommet1; x[1] = _sommet2;
            return *x;
        }

        int getPoids() { return _poids; }
        int getRef() { return _nbReference; }
        void setPoids(int poids) { _poids = poids; }
        void setRef(int nbRef) { _nbReference = nbRef; }

    public :
        void incrReference();
        void decrReference();
};
