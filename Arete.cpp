#include "Arete.h"

Arete::Arete(string nom1, string nom2, int poids) : _sommet1(Sommet(nom1)), _sommet2(Sommet(nom2)), _poids(poids) {}

Arete::Arete(Sommet *s1, Sommet *s2, int poids): _sommet1(s1), _sommet2(s2), _poids(poids) {}

Arete::Arete(Arete *a) {
    *this = a;
}

void incrReference(){
    setRef(getRef()++);
}

void decrReference(){
    setRef(getRef()--);
}