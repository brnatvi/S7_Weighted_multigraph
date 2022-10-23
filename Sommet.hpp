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
        int nbReference;

    public :
        Sommet(string nom);
        Sommet(Sommet *s);

        int getId() const;
        static int getCounterSommets();
        string getNom() const; 
        int getNbReference() const;
        void setNom(string nom);
        void setNbReference(int nbRef);

 //       int incrReference();
//        int decrReference();

};

ostream &operator << (ostream &out, Sommet &x);
ostream &operator << (ostream &out, const Sommet &x);

#endif