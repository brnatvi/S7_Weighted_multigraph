#include "Graph.hpp"

int main(){

    Sommet a{"A"};
    Sommet b{"B"};
    Sommet c{"C"};
    Sommet d1{"D"};
    Sommet d2{"D"};
    Sommet e1{"E"};
    Sommet e2{"E"};
    Sommet z{"Z"};

    cout << a << a.getId() << endl;
    cout << b << b.getId() << endl;
    cout << c << c.getId() <<  endl;
    cout << d1 << d1.getId() << endl;
    cout << d2 << d2.getId() << endl;

    // AB
    Arete ar1{&a, &b, 10};
    // "A" et "B"
    Arete ar2{"A", "B", 2};
    // CD poids 3
    Arete ar3{&c, &d1, 3};
    // CD poids 1 -> erreur de segmentation core dumped

    // Arete ar4{&ar3};
    // ar4.setPoids(1);
    cout << ar1 << endl;
    cout << ar2 << endl;
    cout << ar3 << endl;
    // cout << ar4 << endl;

    list<Arete*> lAr = {};
    // lAr -> (AB); (CD)
    lAr.push_back(&ar1);
    lAr.push_back(&ar3);

    list<Sommet*> lSommet = {};
    // A ; B ; C
    lSommet.push_back(&a);
    lSommet.push_back(&b);
    lSommet.push_back(&c);

    // D n'est pas dans liste de sommets (est-ce une erreur ?)
    Graph g1{&lAr, &lSommet};
    cout << g1 << endl;
    cout << "poids de g1 " << g1.poids() << endl;

    g1.ajoute_sommet(&d1); // rajoute -> OK
    g1.ajoute_sommet(&d2); // rajoute -> OK
    g1.ajoute_sommet(&a); // ne rajoute pas -> OK

    cout << g1 << endl;

    g1.ajoute_arete(&ar1);
    g1.ajoute_arete(&a, &a, 1); // arete boucle sur Sommet a
    g1.ajoute_arete(&b, &a, 10); // arete symetrique a ar1
    g1.ajoute_arete(&e1, &e2, 4); // rajoute -> OK (arete + sommets)
    g1.ajoute_arete("F", "G", 7); // rajoute -> OK (arete + sommets)

    cout << g1 << endl;

    cout << "poids de g1 " << g1.poids() << endl;

    g1.symetrise();; // certaines aretes sont en trop
    cout << g1 << endl;

    Graph g2{&g1};
    cout << g2 << endl;

    g2.ajoute_sommet(&z); // rajoute -> OK
    cout << g2 << endl;

}
