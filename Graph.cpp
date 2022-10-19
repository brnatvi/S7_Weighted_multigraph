
#include "Graph.hpp"

// counterGraph initialisation
int Graph::counterGraphs = 0;

// constructors             
Graph::Graph(list<Arete *> *lAretes, list<Sommet *> *lSommets): listAretes{lAretes}, listSommets{lSommets} 
{  
    this->id = ++counterGraphs; 
    this->nbReference = 0;
}

Graph::Graph(Graph *oldGraph)
{
    this->listAretes = oldGraph->getAretes();
    this->listSommets = oldGraph->getSommets();
    this->id = ++counterGraphs;
    this->nbReference = 0;
}        

// getters/setters

int Graph::getId(){ return this->id; }   
list<Arete*> * Graph::getAretes(){ return this->listAretes; }
list<Sommet*> * Graph::getSommets(){ return this->listSommets; }

void Graph::setAretes(list<Arete*> *l) 
{
/*    while(!this->listAretes.empty()) 
    {
        delete (this->listAretes.front());
    }
 */   
    this->listAretes = l;    
}
                      
void Graph::setSommets(list<Sommet*> *l)
{       
 /*   while(!this->listSommets.empty()) 
    {
        delete (this->listAretes.front());
    }
  */  
    this->listSommets = l;    
}


// methods

void Graph::ajoute_sommet(Sommet *s)
{        
    list<Sommet*> *l = this->getSommets();
    for (Sommet *el : *l)
    {
        if (s == el)
        {
            return;
        }        
    }
    this->getSommets()->push_back(s);
} 

void Graph::ajoute_sommet(string nom)
{
    list<Sommet*> *l = this->getSommets();
    for (Sommet *el : *l)
    {
        if (el->getNom().compare(nom) == 0) 
        {
            return;
        }        
    }
    Sommet *newOne = new Sommet(nom);
    this->getSommets()->push_back(newOne);
} 
                                                            
void Graph::ajoute_arete(Arete *a)
{
    list<Arete*> *l = this->getAretes();
    for (Arete *el : *l)
    {
        if (el == a) 
        {
            return;
        }
    }
    this->getAretes()->push_back(a);
}

void Graph::ajoute_arete(Sommet *s1, Sommet *s2, int p)
{   
    list<Sommet*> *l = this->getSommets();
    bool found1 = false;
    bool found2 = false;
    // check if s1 and s2 are in listAretes
    for (Sommet *el : *l)
    {
        if (el == s1) 
        {
            found1 = true;
        }
        else if (el == s2)
        {
            found2 = true;    
        }
    }
    if (!found1 && !found2)
    {                      
        // create Arete and add to graph
        Arete *newOne = new Arete(s1, s2, p);
        this->getAretes()->push_back(newOne);
    }
    else 
    {    
        if (found1 && found2)                    
        {
            // TODO
            // take Arete with s1 and s2 and check if Arete.poids == p
        }
        else
        {
            Arete *anotherOne = new Arete(s1, s2, p);
            this->getAretes()->push_back(anotherOne);
        }
    }

}

void Graph::ajoute_arete(string nom1, string nom2, int poids)
{
    // TODO
}

void Graph::symmetrise()
{
    list<Arete *> *aretes = this->getAretes();
    list<Arete *> newAretes = {};
    
    for (Arete *a1 : *aretes)
    {
        std::list<Sommet> sommetsA1 = a1->getSommets();
        
        std::string firstA1 = sommetsA1.front().getNom();
        std::string secondA1 = sommetsA1.back().getNom();

        cout << "first1 = " << firstA1 << "secondA1" << secondA1;
    
        for (Arete *a2 : *aretes)
        {
            std::list<Sommet> sommetsA2 = a2->getSommets();
            std::string firstA2 = sommetsA2.front().getNom();
            std::string secondA2 = sommetsA2.back().getNom();
            
            cout << "first2 = " << firstA2 << "secondA2" << secondA2;

            if ((firstA1.compare(firstA2) != 0) && (firstA2.compare(firstA1) != 0) && 
                (a1->getPoids() != a2->getPoids()))
            {
                cout << "I've found something new !";
                Arete newOne = new Arete (firstA2, secondA2, a1->getPoids());
                newAretes.push_back(&newOne);
            }
        }
                
    }    
    this->setAretes(&newAretes);
};

// print
ostream &operator << (ostream &out, Graph &x)
{     
    list<Sommet *> *sommets = x.getSommets();
    list<Arete *> *aretes = x.getAretes();

    cout << "graph "<< x.getId() << " avec les sommets : " ;
    for (Sommet *n : *sommets)
    {       
        cout << n->getNom() << " ";    
    }
    cout << endl;
    cout << "et les aretes : " << endl;
    for (Arete *n : *aretes)
    {
        cout << *n << endl;    
    }
    
    return out;    
}