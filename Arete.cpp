#include "Arete.hpp"
#include <typeinfo>

#include "GC.hpp"

// counterArete initialisation
int Arete::counterArete = 0;

// ==============  constructors / destructor =======================================================
Arete::Arete(const string &nom1, const string &nom2, int poids) {
    sommet1_nom = nom1;
    sommet2_nom = nom2; 

    Sommet *s1 = new Sommet(nom1);
    Sommet *s2 = new Sommet(nom2);

    GC::getGCInstance()->addSommet(s1);
    GC::getGCInstance()->addSommet(s2);

    this->sommet1 = s1;
    this->sommet2 = s2;
    this->poids = poids; 
   
    counterArete ++;
}

Arete::Arete(const Sommet *s1, const Sommet *s2, int poids){
    this->sommet1 = s1;
    this->sommet2 = s2;
    this->poids = poids; 
    
    counterArete ++;

    sommet1_nom = s1->getNom();
    sommet2_nom = s2->getNom();
}


Arete::Arete(const Arete *a) {
    this->sommet1 = a->getSommetsPair().sommet1;
    this->sommet2 = a->getSommetsPair().sommet2;
    this->poids = a->getPoids();
       
    counterArete ++;

    sommet1_nom = sommet1->getNom();
    sommet2_nom = sommet2->getNom();
}

Arete::~Arete(){
    //nous utilisons ici des copies de noms de sommet, 
    //car lors du processus de destruction nous ne sommes pas sûrs que les pointeurs sommet1 & sommet2 
    //soient encore valides, peut-être ils ont déjà été détruits !
    counterArete--;
    cout << "arete     " << this << "   [" << sommet1_nom << " - " << sommet2_nom << "]" << " est detruite " << endl;
}

// ==========================  print ================================================================
ostream &operator << (ostream &out, Arete &x)
{     
    Arete::Pair sommets = x.getSommetsPair();
    cout << "arete " << *(sommets.sommet1) << " - " << *(sommets.sommet2) << " ayant poids = " << x.getPoids();    
    return out;
}