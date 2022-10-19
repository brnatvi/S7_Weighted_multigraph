#include "Sommet.hpp"


// counterGraph initialisation
int Sommet::counterSommets = 0;

// constructors
Sommet::Sommet(string nom) : nom{nom} { 
    this->id = ++counterSommets;
    this->nbReference = 0;
}

Sommet::Sommet(Sommet *s) {
    *this = s;
}

// setters/getters
int Sommet::getId() { return id; }
std::string Sommet::getNom() { return nom; }
void Sommet::setNom(string nom) { nom = nom; }
int Sommet::getNbReference() { return nbReference; }
void Sommet::setNbReference(int nbRef) { nbReference = nbRef; }

/*
void Sommet::incrReference(){
    setRef(getRef()++);
}

void Sommet::decrReference(){
    setRef(getRef()--);
}
*/

