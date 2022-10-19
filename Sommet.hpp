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

        int getId();
        std::string getNom();
        int getNbReference();
        void setNom(string nom);
        void setNbReference(int nbRef);

 //       int incrReference();
//        int decrReference();

};

#endif