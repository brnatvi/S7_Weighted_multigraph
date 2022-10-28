
#include "Graph.hpp"
#include <typeinfo>

// counterGraph initialisation
int Graph::counterGraphs = 0;

#include "GC.hpp"

// ==============  constructors / destructor =======================================================
Graph::Graph(std::list<Arete *> *lAretes, std::list<Sommet *> *lSommets)
    : id(++counterGraphs), listAretes{nullptr}, listSommets{nullptr}, nbReference(0)
{  
    setSommets(lSommets);
    setAretes(lAretes); 

    // ajouter les aretes dans la liste de GC
   /* for (auto el : *lAretes)
    {
        GC::getGCInstance()->addArete(el);
    }
    */
    
}

Graph::Graph(Graph *oldGraph): listAretes{nullptr}, listSommets{nullptr}
{
    setSommets(oldGraph->getSommets());
    setAretes(oldGraph->getAretes());
    this->id = ++counterGraphs;
    this->nbReference = 0;
}

// ===================  getters / setters ===========================================================
void Graph::setAretes(std::list<Arete*> *l)
{
    if (this->listAretes)
    {        
        this->listAretes->clear();        
        delete this->listAretes;        
    }
    
    this->listAretes = new std::list<Arete*>();

    if (l)
    {
        for (auto el : *l)
        {
            this->listAretes->push_back(el);
        }    
    }
}
                      
void Graph::setSommets(std::list<Sommet*> *l)
{       
    if (this->listSommets)
    {
        this->listSommets->clear();
        delete this->listSommets;
    }

    this->listSommets = new std::list<Sommet*>();

    if (l)
    {
        for (Sommet* el : *l)
        {             
            this->listSommets->push_back(el);
        }       
    }
}


// =============================  methods =========================================================

// verification pour eviter d'ajouter un sommet deja present dans la liste
void Graph::ajoute_sommet(Sommet *s) {        
    std::list<Sommet*> *l = this->getSommets();
    if (l)
    {
        for (auto el : *l)
        {
            if (s == el)
            {
                return;
            }       
        }
        l->push_back(s);
    }
} 

// pas de verification dans liste des sommets car nom d'un sommet n'est pas un identifiant
void Graph::ajoute_sommet(string nom) {  
    Sommet *newOne = new Sommet(nom);    
    GC::getGCInstance()->addSommet(newOne);
    this->getSommets()->push_back(newOne);
} 

// verification pour eviter d'ajouter une arete deja presente dans la liste                                                           
void Graph::ajoute_arete(Arete *a) {
    std::list<Arete*> *l = this->getAretes();
    for (auto el : *l) {
        if (el == a) {
            return;
        }
    }
    this->getAretes()->push_back(a);
}

// "Il peut y avoir plusieurs aretes (chacune avec son poids propre) avec les memes extremites" => pas besoin de verification dans liste aretes
void Graph::ajoute_arete(Sommet *s1, Sommet *s2, int p){  
    Arete *a = new Arete(s1, s2, p);
    GC::getGCInstance()->addArete(a);

    // ajoute_sommet verifie deja presence de sommet dans liste
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    this->getAretes()->push_back(a);  
}

void Graph::ajoute_arete(string nom1, string nom2, int poids) {
    Arete *a = new Arete(nom1, nom2, poids);
    GC::getGCInstance()->addArete(a);
    this->getAretes()->push_back(a);
}


void Graph::cloneList(std::list<Arete *> *src, std::list<Arete *> *dest)
{
    for (Arete *el : *src)
    {
        dest->push_back(el);
    }    
}

int Graph::poids(){
    std::list<Arete*> *l = this->getAretes();
    int p = 0;
    for(Arete* el: *l){
        p += el->getPoids();
    }    
    return p;
}

void Graph::symetrise(){
    std::list<Arete *> *aretes = this->getAretes();
    std::list<Arete *> *newAretes = new std::list<Arete *>;
    cloneList(aretes, newAretes);
    bool isFound = false;
        
    for (Arete *a1 : *aretes)
    {        
        const Sommet* a1S1 = a1->getSommetsPair().sommet1;
        const Sommet* a1S2 = a1->getSommetsPair().sommet2;
    
        for (Arete *a2 : *aretes)
        {            
            const Sommet* a2S1 = a2->getSommetsPair().sommet1;
            const Sommet* a2S2 = a2->getSommetsPair().sommet2;

            if (((a1S1 == a2S2) 
              && (a1S2 == a2S1) 
              && (a1->getPoids() == a2->getPoids())) || 
             (a1S1 == a1S2))
            { 
                isFound = true;       
            }            
        }
        if (!isFound)
        {
            Arete *newOne = new Arete(a1S2, a1S1, a1->getPoids());
            newAretes->push_back(newOne);   
            GC::getGCInstance()->addArete(newOne);
        }   
        isFound = false;    
    }    
    
    this->setAretes(newAretes);  
};

// ==========================  print ================================================================
ostream &operator << (ostream &out, Graph &x)
{     
    std::list<Sommet *> *sommets = x.getSommets();
    std::list<Arete *> *aretes = x.getAretes();
   
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
