
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

int Graph::getId() const { return this->id; }   
list<Arete*> * Graph::getAretes() const{ return this->listAretes; }
list<Sommet*> * Graph::getSommets() const { return this->listSommets; }

void Graph::setAretes(list<Arete*> *l) 
{    
    // TODO need to destroy old listAretes?
    this->listAretes = l;    
}
                      
void Graph::setSommets(list<Sommet*> *l)
{    
    // TODO need to destroy old listSommets?
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
    // TODO check if need to add some Sommet of Arete a
    this->getAretes()->push_back(a);
    Arete::Pair sommets = a->getSommetsPair();
    this->ajoute_sommet(sommets.sommet1);
    this->ajoute_sommet(sommets.sommet2);
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
    if (found1 && found2)                    
    {
        // TODO
        // take Arete with s1 and s2 and check if Arete.poids == p
    }
    else
    {
        Arete *newOne = new Arete(s1, s2, p);
        this->getAretes()->push_back(newOne);
        this->ajoute_sommet(s1);
        this->ajoute_sommet(s2);
    }    
}

void Graph::ajoute_arete(string nom1, string nom2, int poids)
{
    // TODO
}

void Graph::cloneList(list<Arete *> *src, list<Arete *> *dest)
{
    for (Arete *el : *src)
    {
        dest->push_back(el);
    }    
}

void Graph::symmetrise()
{
    list<Arete *> *aretes = this->getAretes();
    list<Arete *> *newAretes = new list<Arete *>;
    cloneList(aretes, newAretes);
        
    for (Arete *a1 : *aretes)
    {        
        Sommet* a1S1 = a1->getSommetsPair().sommet1;
        Sommet* a1S2 = a1->getSommetsPair().sommet2;

        cout << "a1S1 = " <<  a1S1->getId() << " a1S2 = " << a1S2->getId() << endl;
    
        for (Arete *a2 : *aretes)
        {            
            Sommet* a2S1 = a1->getSommetsPair().sommet1;
            Sommet* a2S2 = a1->getSommetsPair().sommet2;
                        
            cout << "a2S1 = " << a2S1->getId() << " a2S2 = " << a2S2->getId() << endl;

            if ((a1S1 == a2S2) 
             && (a1S2 == a2S1) 
             && (a1->getPoids() == a2->getPoids()))
            { // do nothing       
            }            
        } 
        cout << "I've created mirror-arete ! ";                       

        newAretes->push_back(new Arete(a1S2, a1S1, a1->getPoids())); 
        cout << "newS1 = " << a1S2->getId() 
             << " newS2 = " << a1S1->getId() 
             << " poids = " << a1->getPoids() << endl;
                      
    }    
    
    this->setAretes(newAretes);
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
        cout << n->getSommetsPair().sommet1->getNom() 
             << " - " << n->getSommetsPair().sommet2->getNom() 
             << " (" << n->getPoids() << ") " << endl;    
    }    
    return out;    
}