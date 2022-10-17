#include <iostream>
using namespace std;

class Sommet {

    private :
        int _id;
        string _nom;
        int _nbReference = 0;

    public :
        Sommet(string nom);
        Sommet(Sommet *s);

    public :
        int getId() { return _id; }
        string getName() { return _nom; }
        int getRef() { return _nbReference; }
        void setNom(string nom) { _nom = nom; }
        void setRef(int nbRef) { _nbReference = nbRef; }

    public :
        int incrReference();
        int decrReference();
        static int identifiant();
    
};