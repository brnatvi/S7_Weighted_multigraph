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
int Sommet::getId() const { return id; }
std::string Sommet::getNom() const { return nom; }
void Sommet::setNom(string nom) { nom = nom; }
int Sommet::getNbReference() const { return nbReference; }
void Sommet::setNbReference(int nbRef) { nbReference = nbRef; }

/*
void Sommet::incrReference(){
    setRef(getRef()++);
}

void Sommet::decrReference(){
    setRef(getRef()--);
}
*/

