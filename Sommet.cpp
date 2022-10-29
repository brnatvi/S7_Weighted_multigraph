#include "Sommet.hpp"
#include <typeinfo>

#include "GC.hpp"

// counterGraph initialisation
int Sommet::counterSommets = 0;

// ==============  constructors / destructor =======================================================
Sommet::Sommet(const string &nom) { 
    this->nom = nom;
    this->id = ++counterSommets;
    this->nbReference = 0;
}

Sommet::Sommet(const Sommet *s) {
    this->nom = s->getNom();
    this->id = ++counterSommets;
    this->nbReference = 0;
}

Sommet::~Sommet(){
    counterSommets --;
    cout << "sommet    " << this << "   [" << this->nom << "]" << " est detruit " << endl;
}

// ==========================  print ================================================================
ostream &operator << (ostream &out, Sommet &x) {     
    cout << x.getNom();
    return out;

};

ostream &operator << (ostream &out, const Sommet &x) {     
    cout << x.getNom();
    return out;
};

