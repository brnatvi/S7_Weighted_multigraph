#include "Sommet.h"

int Sommet::identifiant(){
    static int counter = 0 ;
    return ++counter ;
}

Sommet::Sommet(string nom) : _id(identifiant()), _nom(nom) { }

Sommet::Sommet(Sommet *s) {
    *this = s;
}

void incrReference(){
    setRef(getRef()++);
}

void decrReference(){
    setRef(getRef()--);
}

int main(){
    Sommet s("A");
    cout << s.getName() << endl;
    cout << s.getId() << endl;
    Sommet z("B");
    cout << z.getName() << endl;
    cout << z.getId() << endl;
}