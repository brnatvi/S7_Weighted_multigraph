#include "Arete.hpp"
#include <typeinfo>

// counterArete initialisation
int Arete::counterArete = 0;

// constructors
Arete::Arete(string nom1, string nom2, int poids) {
    Sommet *new1 = new Sommet(nom1);
    Sommet *new2 = new Sommet(nom2);
    this->sommet1 = new1;
    this->sommet2 = new2;
    this->poids = poids;    
    this->nbReference = 0;
    counterArete ++;
}

Arete::Arete(const Sommet *s1, const Sommet *s2, int poids){
    this->sommet1 = s1;
    this->sommet2 = s2;
    this->poids = poids;
    this->nbReference = 0;
    counterArete ++;
}

// TODO test
Arete::Arete(Arete *a) {
    this->sommet1 = a->getSommetsPair().sommet1;
    this->sommet2 = a->getSommetsPair().sommet2;
    this->poids = a->getPoids();
    ++counterArete;
    this->nbReference = 0;
}

// getters/setters
int Arete::getPoids() const { return poids; }
int Arete::getRef() const { return nbReference; }
void Arete::setPoids(int poids) { this->poids = poids; }
void Arete::setRef(int nbRef) { nbReference = nbRef; }

Arete::Pair Arete::getSommetsPair() const {
    
    return {this->sommet1, this->sommet2};
}


// print
ostream &operator << (ostream &out, Arete &x)
{     
    Arete::Pair sommets = x.getSommetsPair();
    cout << "arete " << *(sommets.sommet1) << " - " << *(sommets.sommet2) << " ayant poids = " << x.getPoids();    
    return out;

};


/*
void Arete::incrReference(){
    setRef(getRef()++);
}

void Arete::decrReference(){
    setRef(getRef()--);
}
*/