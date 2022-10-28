#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>
#include "Arete.hpp"


class Graph {

    private :
        static int counterGraphs;
        int id;
        std::list<Arete*> *listAretes;
        std::list<Sommet*> *listSommets;
        int nbReference;

        // copy one list to another one (for intern usage)
        void cloneList(std::list<Arete*> *src, std::list<Arete*> *dest); 

    public :
        Graph(std::list<Arete *> *listAretes, std::list<Sommet *> *listSommets);
        Graph(Graph *oldGraph);        

        static int getCounterGraphs() { return counterGraphs; };  

        int getId() const { return this->id; }

        std::list<Arete*> * getAretes()  const { return this->listAretes; }
        std::list<Sommet*> * getSommets() const { return this->listSommets; }

        // attach new list of Aretes* to graph
        void setAretes(std::list<Arete*> *list);   

        // attach new list of Aretes* to graph
        void setSommets(std::list<Sommet*> *list); 
                                     
        void ajoute_sommet(Sommet *s);  
        void ajoute_sommet(string nom);  
                                                            
        void ajoute_arete(Arete *a);                        
        void ajoute_arete(Sommet *s1, Sommet *s2, int p); 
        void ajoute_arete(string nom1, string nom2, int p);

        int poids();
        
        void symetrise();
};

ostream &operator << (ostream &out, Graph &x);

#endif