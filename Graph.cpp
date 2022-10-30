
#include "Graph.hpp"
#include <typeinfo>
#include <iostream>

#include "GC.hpp"

// counterGraph initialisation
int Graph::counterGraphs = 0;

// constructors 
Graph::Graph(list<Arete *> *lAretes, list<Sommet *> *lSommets) : listAretes{nullptr}, listSommets{nullptr} 
{  
    setSommets(lSommets);
    setAretes(lAretes);    
    this->id = ++counterGraphs;
    this->nbReference = 0;
}

Graph::Graph(const Graph *oldGraph): listAretes{nullptr}, listSommets{nullptr} 
{
    setSommets(oldGraph->getSommets());
    setAretes(oldGraph->getAretes());    
    this->id = ++counterGraphs;
    this->nbReference = 0;
}        

Graph::~Graph()
{
    this->listAretes->clear();
    delete (this->listAretes);
    this->listSommets->clear();
    delete (this->listSommets);
    
    cout << "Graph     " << this << " est detruit" << endl;
}

//========================== setters ======================================================

void Graph::setAretes(list<Arete*> *l)
{
    if (this->listAretes)
    {        
        this->listAretes->clear();        
        delete this->listAretes;        
    }
    
    this->listAretes = new std::list<Arete*>();     // free memory in ~Graph()

    if (l)
    {
        for (auto el : *l)
        {
            ajoute_sommet((Sommet*)(el->getSommetsPair().sommet1));
            ajoute_sommet((Sommet*)(el->getSommetsPair().sommet2));
            this->listAretes->push_back(el);
        }    
    }
    
}
                      
void Graph::setSommets(list<Sommet*> *l)
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

// ===================== ajoute_arete() et ajoute_sommet() ==================================

// verification pour eviter d'ajouter un sommet deja present dans la liste
void Graph::ajoute_sommet(Sommet *s)
{        
    list<Sommet*> *l = this->getSommets();
    for (auto el : *l)
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
    Sommet *newOne = new Sommet(nom);             // free memory by GC
    GC::getGCInstance()->addSommet(newOne);
    this->getSommets()->push_back(newOne);
} 

// verification pour eviter d'ajouter une arete deja presente dans la liste                                                           
void Graph::ajoute_arete(Arete *a)
{
    list<Arete*> *l = this->getAretes();
    for (auto el : *l)
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
    Arete *a = new Arete(s1, s2, p);                // free memory by GC
    GC::getGCInstance()->addArete(a);

    // ajoute_sommet verifie deja presence de sommet dans liste
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    this->getAretes()->push_back(a);  
}

void Graph::ajoute_arete(string nom1, string nom2, int poids) {
    Sommet *s1 = new Sommet(nom1);                   // free memory by GC  
    Sommet *s2 = new Sommet(nom2);                   // free memory by GC 
    GC::getGCInstance()->addSommet(s1);
    GC::getGCInstance()->addSommet(s2); 
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    Arete *a = new Arete(s1, s2, poids);             // free memory by GC
    GC::getGCInstance()->addArete(a); 
    this->getAretes()->push_back(a);
}

// ======================== symetrise() ===============================================

void Graph::cloneList(list<Arete *> *src, list<Arete *> *dest)
{
    for (Arete *el : *src)
    {
        dest->push_back(el);
    }    
}


void Graph::symetrise(){
    list<Arete *> *aretes = this->getAretes();              // free memory in setAretes()
    list<Arete *> *newAretes = new list<Arete *>;           // free memory in ~Grapth()
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

            if ((a1S1 == a2S2) 
             && (a1S2 == a2S1) 
             && (a1->getPoids() == a2->getPoids()))
            { 
                isFound = true;       
            }            
        }
        if (!isFound)
        {
            Arete *newOne = new Arete(a1S2, a1S1, a1->getPoids());      // free memory by GC
            newAretes->push_back(newOne);   
            GC::getGCInstance()->addArete(newOne);
        }   
        isFound = false;    
    }    
    
    this->setAretes(newAretes);  
}

// ======================== kruskal() ===============================================


list<Arete*>* Graph::trie(){
    list<Arete*> *l = getAretesNoSym();                // alloc memory - free memory in kruskal()
    l->sort([](const Arete* a, const Arete* b) 
    { 
        return a->getPoids() < b->getPoids(); 
    });
    return l;
}

int Graph::find(const Sommet* u, list<Etiquette*> *ens_sommets){
    for(auto elt : *ens_sommets){
        if(u == (elt->v)) {
            return elt->id;
        }
    }
    return -1;
}

void Graph::doUnion(const Sommet* u, const Sommet* v, list<Etiquette*> *ens_sommets) {
    int u_id = find(u, ens_sommets);
    int v_id = find(v, ens_sommets);
    for(auto elt : *ens_sommets){
        if(elt->id == v_id){
            elt->id = u_id;
        }       
    }
}

Graph Graph::kruskal(){
    list<Graph::Etiquette*> *ens_sommets = new list<Graph::Etiquette*>();   // free memory below
    list<Sommet*> *l = this->getSommets();
    list<Arete*> *ret = new list<Arete*>();                             // free memory by GC
    
    for(auto el : *l){
        Etiquette* e1 = new Etiquette{el, el->getId()};                // free memory below
        ens_sommets->push_back(e1);
    }
    list<Arete*> *sorted_aretes = trie();                              // alloc memory - free memory below
    // cout << "SORTED ARETES" << endl;
    // for(auto pp: *sorted_aretes){
    //     cout << *pp << endl;
    // }
    for(auto p : *sorted_aretes){
        // int s1 = find(p->getSommetsPair().sommet1, ens_sommets);
        // int s2 = find(p->getSommetsPair().sommet2, ens_sommets); 
        // cout << "sorted_artes " << *p << " " << s1 << " " << s2 <<  endl;
        if(find(p->getSommetsPair().sommet1, ens_sommets) != find(p->getSommetsPair().sommet2, ens_sommets))
        {
            ret->push_back(p);
            doUnion(p->getSommetsPair().sommet1, p->getSommetsPair().sommet2, ens_sommets);
        }
    } 

    for (auto el : *ens_sommets)
    {
        delete(el);
    }
    ens_sommets->clear();
    delete ens_sommets;

    sorted_aretes->clear();
    delete sorted_aretes;

    return Graph{ret, l};    
};

// ======================== poids() ===============================================

bool Graph::hasSymetric(Arete *a, list<Arete*> *aretes){
    for (auto elt: *aretes){
        if (elt->getSommetsPair().sommet1 == a->getSommetsPair().sommet2 && 
            elt->getSommetsPair().sommet2 == a->getSommetsPair().sommet1 &&
            elt->getPoids() == a->getPoids())
            {
                return true;
            }
    }
    return false;
}

list<Arete*>* Graph::getAretesNoSym(){
    list<Arete*> *l = this->getAretes();
    list<Arete*> *no_sym = new list<Arete*>();                  // free memory in poids() and kruskal()
    for (auto elt: *l){ 
        if(!hasSymetric(elt, no_sym)){
            no_sym->push_back(elt);
        }
    }
    return no_sym;
}

int Graph::poids(){
    int p = 0;
    list<Arete*> *no_sym = getAretesNoSym();                    // alloc memory - free memory below

    for (auto e: *no_sym){
        p += e->getPoids();
    }

    no_sym->clear();
    delete no_sym;

    return p;
}


// ==========================  print ================================================================
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