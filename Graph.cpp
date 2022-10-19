
#include "Graph.hpp"

// counterGraph initialisation
int Graph::counterGraphs = 0;

// constructors             
Graph::Graph(list<Arete *> *lAretes, list<Sommet *> *lSommets): listAretes{*lAretes}, listSommets{*lSommets} 
{  
    this->id = ++counterGraphs; 
    this->nbReference = 0;
}

Graph::Graph(Graph *oldGraph)
{
    
}        

// getters/setters

int Graph::getId(){ return this->id; }   
list<Arete*> Graph::getAretes(){ return this->listAretes; }
list<Sommet*> Graph::getSommets(){ return this->listSommets; }


// methods
void Graph::symmetrise()
{

}

// print
ostream &operator << (ostream &out, Graph &x)
{     
    list<Sommet *> sommets = x.getSommets();
    list<Arete *> aretes = x.getAretes();

    cout << "graph avec les sommets : " ;
    for (Sommet *n : sommets)
    {       
        cout << n->getNom() << " ";    
    }
    cout << endl;
    cout << "et les aretes : " << endl;
    for (Arete *n : aretes)
    {
        cout << *n << endl;    
    }
    
    return out;    
}