#include "Graph.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

string TEST_FAIL = "Test failed";
string TEST_PASS = "Test passed";

int main(){

    srand(time(0));
    int p = 0;    

    Sommet a{"A"};
    Sommet b{"B"};
    Sommet c{"C"};
    Sommet d1{"D"};
    Sommet d2{"D"};
    Sommet e1{"E"};
    Sommet e2{"E"};
    Sommet z{"Z"};

    cout << endl << "Tests #1 - Creation des Sommets" << endl << "8 Sommets ont ete cree" << endl;
    if (Sommet::getCounterSommets() != 8) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl;    }

    cout << endl << "Tests #2 - Creation des Aretes" << endl ;
    p = rand()%100;
    int p1 = p;
    cout << "Test de constructeur par references : A - B (poids " << p << ")" << endl;
    Arete ar1{&a, &b, p};
    cout << ar1 << endl;
    
    cout << "Test de constructeur par references : B - C (poids " << p << ")" << endl;
    p = rand()%100;
    Arete ar2{&b, &c, p};
    cout << ar2 << endl;

    cout << "Test de constructeur par noms : B - C (poids " << p << ")" << endl;
    p = rand()%100;
    Arete ar3{"B", "C", p};
    cout << ar3 << endl;
    
    cout << "Test de constructeur par references :  B - A (poids " << p1 << ")" << endl;    
    Arete ar4{&b, &a, p1};
    cout << ar4 << endl;

    cout << "4 Aretes ont ete cree" << endl;
    if (Arete::getCounterAretes() != 4) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl << endl;    }

    cout << endl << "Tests #3 - setPoids()" << endl;
    Arete ar5{&ar3};
    int aldPoids = ar3.getPoids();
    int newPoids = 15;
    ar3.setPoids(newPoids);
    if ((ar3.getPoids() != newPoids) || (ar5.getPoids() != aldPoids)) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl;    }
    cout << ar3 << endl;
    cout << ar5 << endl << endl;

   
    cout << endl << "Tests #4 - Creation des Graphs" << endl;    
    cout << "test de constructeur avec une liste des Sommets et une liste des Areres" << endl;
    list<Arete*> lAr = {};
    lAr.push_back(&ar1);
    lAr.push_back(&ar2);
    lAr.push_back(&ar3);
    lAr.push_back(&ar4);

    list<Sommet*> lSommet = {};    
    lSommet.push_back(&a);
    lSommet.push_back(&b);
    lSommet.push_back(&c);
    lSommet.push_back(&d1);

    Graph g1{&lAr, &lSommet};
    cout << g1 << endl;

    cout << "test de constructeur par copie" << endl;
    Graph g2{&g1};
    cout << g2 << endl;

    cout << "2 Graphs ont ete cree" << endl;
    if (Graph::getCounterGraphs() != 2) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl;    }


    cout << endl << "Tests #5 - ajoute_sommet()" << endl;
    //TODO


    cout << endl << "Tests #6 - ajoute_arete()" << endl;
    //TODO


    cout << endl << "Tests #5 - symetrise()" << endl;  
    g1.symetrise();
    cout << g1 << endl;


    cout << endl << "Tests #8 - poids()" << endl;
    //TODO


/*
    
    // D n'est pas dans liste de sommets (est-ce une erreur ?)
    Graph g1{&lAr, &lSommet};
    cout << "D n'est pas dans liste de sommets (est-ce une erreur ?)" << endl;
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
    

*/
}
