#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "Arete.hpp"

using namespace std;

class Graph {

    private :
        static int counterGraphs;
        int id;
        list<Arete*> listAretes;
        list<Sommet*> listSommets;
        int nbReference;

    public :
        Graph(list<Arete *> *listAretes, list<Sommet *> *listSommets);
        Graph(Graph *oldGraph);        

        int getId();
        list<Arete*> getAretes();
        list<Sommet*> getSommets();
        void symmetrise();
};

ostream &operator << (ostream &out, Graph &x);

#endif