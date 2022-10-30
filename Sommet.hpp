#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>
#include <string>
using namespace std;

class Sommet {

    private :
        static int counterSommets;
        int id;
        string nom;        

    public :
        Sommet(const string &nom);
        Sommet(const Sommet *s);
        ~Sommet();

        static int getCounterSommets() { return counterSommets; };
  
        const string & getNom() const { return nom; }

        int getId() const {return id; }
        void setNom(const string &nom) { this->nom = nom; } 
};

ostream &operator << (ostream &out, Sommet &x);
ostream &operator << (ostream &out, const Sommet &x);

#endif