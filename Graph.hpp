#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>
#include <list>
#include "Arete.hpp"

using namespace std;

class Graph {

    public :
        struct Etiquette {
            const Sommet *v;
            int id;
        };

    private :
        static int counterGraphs;
        int id;
        list<Arete*> *listAretes;
        list<Sommet*> *listSommets;
        int nbReference;

        void cloneList(list<Arete*> *src, list<Arete*> *dest); 

    

    public :
        Graph(list<Arete *> *listAretes, list<Sommet *> *listSommets);
        Graph(Graph *oldGraph);        

        int getId() const;
        list<Arete*> * getAretes() const;
        list<Sommet*> * getSommets() const;  
        static int getCounterGraphs();              
        void setAretes(list<Arete*> *list);
        void setSommets(list<Sommet*> *list);
                                        
        // étant donné soit un sommet existant, soit une étiquette, crée
        // le sommet dans ce dernier cas et ajoute le sommet au graphe ;
        void ajoute_sommet(Sommet *s);  
        void ajoute_sommet(string nom);  
                                                            
        // étant donné soit une arête existante, soit deux sommets existants et un poids, 
        // soit deux étiquettes et un poids, crée les sommets et l’arête si nécessaire et les ajoute au graphe ;
        void ajoute_arete(Arete *a);                        
        void ajoute_arete(Sommet *s1, Sommet *s2, int p); 
        void ajoute_arete(string nom1, string nom2, int p);

        // retourne le poids de G, soit la somme des poids de ses aretes
        int poids(); 
        
        // rajoute aretes symetriques si besoin
        void symetrise();

        // algorithme de kruskal 
        void kruskal(); // return Graph
        Etiquette creerEnsemble(Sommet *v);
        list<Arete*>* trie();
        int find(const Sommet* u, list<Etiquette> ens_sommets);
        list<Etiquette> do_union(const Sommet* u, const Sommet* v, list<Etiquette> ens_sommets) ;
        
        
};

ostream &operator << (ostream &out, Graph &x);

#endif