#include "Arete.hpp"

// counterArete initialisation
int Arete::counterArete = 0;

// constructors
Arete::Arete(string nom1, string nom2, int poids) {
    Sommet new1 = new Sommet(nom1);
    Sommet new2 = new Sommet(nom2);
    this->sommet1 = &new1;
    this->sommet2 = &new2;
    this->poids = poids;    
    this->nbReference = 0;
    counterArete ++;
}

Arete::Arete(Sommet *s1, Sommet *s2, int poids){
    this->sommet1 = s1;
    this->sommet2 = s2;
    this->poids = poids;
    this->nbReference = 0;
    counterArete ++;
}



// TODO question: is it constructor by copy ?
Arete::Arete(Arete *a) {
    *this = a;
}

// getters/setters
int Arete::getPoids() { return poids; }
int Arete::getRef() { return nbReference; }
void Arete::setPoids(int poids) { poids = poids; }
void Arete::setRef(int nbRef) { nbReference = nbRef; }

std::list<Sommet> Arete::getSommets() {
    std::list<Sommet> sommets;  
    sommets.push_back(*this->sommet1);     
    sommets.push_back(*this->sommet2);
    return sommets;
}


// print
ostream &operator << (ostream &out, Arete &x)
{     
    std::list<Sommet> sommets = x.getSommets();
    cout << "arete " << sommets.front().getNom() << " - " << sommets.back().getNom() << " ayant poids = " << x.getPoids();    
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