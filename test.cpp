#include "Graph.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

string TEST_FAIL = "Test failed";
string TEST_PASS = "Test passed";

int main(){
    srand(time(0));
    int p = 0;  
    int poidsTotal = 0;  

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
    int p1 = p;     // pour faire un arc miroir
    cout << "Test de constructeur par references : A - B (poids " << p << ")" << endl;
    Arete ar1{&a, &b, p};
    poidsTotal += p;
    cout << ar1 << endl;
    
    cout << "Test de constructeur par references : B - C (poids " << p << ")" << endl;
    p = rand()%100;    
    Arete ar2{&b, &c, p};
    poidsTotal += p;
    cout << ar2 << endl;

    p = rand()%100;
    cout << "Test de constructeur par noms : B - C (poids " << p << ")" << endl;        
    Arete ar3{"B", "C", p}; 
    poidsTotal += p;
    cout << ar3 << endl;
    
    cout << "Test de constructeur par references :  B - A (poids " << p1 << ")" << endl;      
    Arete ar4{&b, &a, p1};
    cout << ar4 << endl;

    cout << "4 Aretes ont ete cree" << endl;
    if (Arete::getCounterAretes() != 4) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl << endl;    }

    cout << endl << "Tests #3 - setPoids()" << endl;
    Arete ar5{&ar3};
    poidsTotal += p;
    int oldPoids = ar3.getPoids();
    p = rand()%100;
    poidsTotal -= oldPoids;    
    ar3.setPoids(p);
    poidsTotal += p;
    if ((ar3.getPoids() != p) || (ar5.getPoids() != oldPoids)) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl;    }
    cout << ar3 << endl;
    cout << ar5 << endl << endl;

   
    cout << endl << "Tests #4 - Creation des Graphs" << endl;    
    cout << "test de constructeur avec une liste des Sommets et une liste des Aretes" << endl;
    list<Arete*> *lAr = new list<Arete*>();
    lAr->push_back(&ar1);
    lAr->push_back(&ar2);
    lAr->push_back(&ar3);
    lAr->push_back(&ar4);

    list<Sommet*> *lSommet = new list<Sommet*>();    
    lSommet->push_back(&a);
    lSommet->push_back(&b);
    lSommet->push_back(&c);
    lSommet->push_back(&d1);

    Graph g1{lAr, lSommet};   
    cout << g1 << endl;

    cout << "test de constructeur par copie" << endl;
    Graph g2{&g1};
    cout << g2 << endl;

    cout << "2 Graphs ont ete creé" << endl;
    if (Graph::getCounterGraphs() != 2) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl;    }


    cout << endl << "Tests #5 - ajoute_sommet()" << endl;
    cout << "trois sommets seraint ajouteés: les deux neuves (D, E) et l'un déjà present dans le graph (A)" << endl;
    unsigned int size_sommets = g1.getSommets()->size();
    g1.ajoute_sommet(&a);
    g1.ajoute_sommet(&d2);
    g1.ajoute_sommet(&e1);
    if(g1.getSommets()->size() != size_sommets + 2) { cout << TEST_FAIL << endl; }
    else { cout << TEST_PASS << endl; }
    cout << g1 << endl;

    cout << endl << "Tests #6 - ajoute_arete()" << endl;
    cout << "trois aretes seraint ajoutees:  B-C et E-E(boucle) et l'une déjà presente dans le graph (A-B)" << endl;
    unsigned int size_aretes = g1.getAretes()->size();
    size_sommets = g1.getSommets()->size();
    g1.ajoute_arete(&ar1);
    g1.ajoute_arete(&ar5);
    g1.ajoute_arete(&e1, &e1, 2);
    poidsTotal += 2;
    if(g1.getAretes()->size() != size_aretes + 2 || g1.getSommets()->size() != size_sommets) 
    { cout << TEST_FAIL << endl;  }
    else { cout << TEST_PASS << endl; }
    cout << g1 << endl;

    cout << endl << "Tests #8 - symetrise()" << endl;  
    g1.symetrise();
    cout << g1 << endl;


    cout << endl << "Tests #9 - poids()" << endl;
    int graph_weight = g1.poids();
    cout << "Poids du graphe         " << graph_weight << endl;
    cout << "Sum de poids destribués " << poidsTotal << endl;
    if(poidsTotal != graph_weight) { cout << TEST_FAIL << endl << endl;  }
    else { cout << TEST_PASS << endl << endl; }  

    Graph acm = g1.kruskal(); 
    cout << "ARBRE COUVRANT MINIMAL" << endl;
    cout << acm << endl; 
}
