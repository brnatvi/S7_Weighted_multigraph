#include "Graph.hpp"

int main(){
    Sommet s{"A"};
    cout << s.getNom() << endl;
    cout << s.getId() << endl;
    Sommet z{"B"};
    cout << z.getNom() << endl;
    cout << z.getId() << endl;
    Sommet z1{"C"};  
    Sommet z2{"D"}; 
    Sommet z3{"E"};
  
    
    Arete ar1 {&s, &z, 12};
    cout << ar1 << endl;  
    Arete ar2 {&s, &z1, 8};
    Arete ar3 {&z1, &z2, 5};
    Arete ar4 {&z2, &z3, 9};  

    list<Arete*> listAr = {};
    listAr.push_back(&ar1);
    listAr.push_back(&ar2);
    listAr.push_back(&ar3);
    listAr.push_back(&ar4);

    list<Sommet*> listSomm = {};
    listSomm.push_back(&s);
    listSomm.push_back(&z);
    listSomm.push_back(&z1);
    listSomm.push_back(&z2);
    listSomm.push_back(&z3);

    Graph g1{&listAr, &listSomm};
    cout << g1 << endl;
}