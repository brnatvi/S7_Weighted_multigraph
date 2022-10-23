
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
list<Arete*> * Graph::getAretes() const { return this->listAretes; }
list<Sommet*> * Graph::getSommets() const { return this->listSommets; }

void Graph::setAretes(list<Arete*> *l) 
{
    // TODO destroy old listAretes ?
    this->listAretes = l;    
}
                      
void Graph::setSommets(list<Sommet*> *l)
{       
    // TODO destroy old listSommets ?
    this->listSommets = l;    
}


// methods

// verification pour eviter d'ajouter un sommet deja present dans la liste
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

// pas de verification dans liste des sommets car nom d'un sommet n'est pas un identifiant
void Graph::ajoute_sommet(string nom) {  
    Sommet *newOne = new Sommet(nom);
    this->getSommets()->push_back(newOne);
} 

// verification pour eviter d'ajouter une arete deja presente dans la liste                                                           
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

// "Il peut y avoir plusieurs aretes (chacune avec son poids propre) avec les memes extremites" => pas besoin de verification dans liste aretes
void Graph::ajoute_arete(Sommet *s1, Sommet *s2, int p){  
    Arete *a = new Arete(s1, s2, p);
    // ajoute_sommet verifie deja presence de sommet dans liste
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    this->getAretes()->push_back(a);  
}

void Graph::ajoute_arete(string nom1, string nom2, int poids) {
    Sommet *s1 = new Sommet(nom1);
    Sommet *s2 = new Sommet(nom2);
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    Arete *a = new Arete(s1, s2, poids);
    this->getAretes()->push_back(a);
}

int Graph::poids(){
    list<Arete*> *l = this->getAretes();
    int p = 0;
    for(Arete* el: *l){
        p += el->getPoids();
    }
    return p;
}

void Graph::cloneList(list<Arete *> *src, list<Arete *> *dest)
{
    for (Arete *el : *src)
    {
        dest->push_back(el);
    }    
}


void Graph::symetrise(){
    list<Arete *> *aretes = this->getAretes();
    list<Arete *> *newAretes = new list<Arete *>;
    cloneList(aretes, newAretes);
        
    for (Arete *a1 : *aretes)
    {        
        const Sommet* a1S1 = a1->getSommetsPair().sommet1;
        const Sommet* a1S2 = a1->getSommetsPair().sommet2;

        cout << "a1S1 = " <<  a1S1->getId() << " a1S2 = " << a1S2->getId() << endl;
    
        for (Arete *a2 : *aretes)
        {            
            const Sommet* a2S1 = a1->getSommetsPair().sommet1;
            const Sommet* a2S2 = a1->getSommetsPair().sommet2;
                        
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