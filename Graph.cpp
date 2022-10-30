
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

Graph::Graph(Graph *oldGraph): listAretes{nullptr}, listSommets{nullptr} 
{
    setSommets(oldGraph->getSommets());
    setAretes(oldGraph->getAretes());    
    this->id = ++counterGraphs;
    this->nbReference = 0;
}        

// setters

void Graph::setAretes(list<Arete*> *l)
{
    if (this->listAretes)
    {        
        this->listAretes->clear();        
        delete this->listAretes;        
    }
    
    this->listAretes = new std::list<Arete*>();

    if (l)
    {
        for (auto el : *l) {
            const Arete::Pair el_pair = el->getSommetsPair();

            ajoute_sommet((Sommet*)(el_pair.sommet1));
            ajoute_sommet((Sommet*)(el_pair.sommet2));

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


// methods

// verification pour eviter d'ajouter un sommet deja present dans la liste
void Graph::ajoute_sommet(Sommet *s)
{        
    list<Sommet*> *l = this->getSommets();
    if(l){
        for(auto el : *l){
            if(s == el){
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
void Graph::ajoute_arete(Arete *a)
{
    list<Arete*> *l = this->getAretes();
    if(l){
        for(auto el: *l){
            if(a == el) {
                return;
            }
        }
        l->push_back(a);
    }
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
    Sommet *s1 = new Sommet(nom1);
    Sommet *s2 = new Sommet(nom2);
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    Arete *a = new Arete(s1, s2, poids);
    GC::getGCInstance()->addArete(a);
    this->getAretes()->push_back(a);
}

bool Graph::hasSymetric(Arete *a, list<Arete*> *aretes){
    if(aretes){
        for(auto elt: *aretes){
            const Arete::Pair elt_pair = elt->getSommetsPair();
            const Arete::Pair a_pair = a->getSommetsPair();
            if(elt_pair.sommet1 == a_pair.sommet2 && elt_pair.sommet2 == a_pair.sommet1 &&
            elt->getPoids() == a->getPoids()){
                return true;
            }
        }
    }
    
    return false;
}

list<Arete*>* Graph::getAretesNoSym(){
    list<Arete*> *l = this->getAretes();
    list<Arete*> *no_sym = new list<Arete*>();
    if(l){
        for(auto elt: *l){ 
            if(!hasSymetric(elt, no_sym)){
                no_sym->push_back(elt);
            }
        }
    }
    
    return no_sym;
}

int Graph::poids(){
    int p = 0;
    list<Arete*> *no_sym = getAretesNoSym();
    if(no_sym){
        for(auto e: *no_sym){
            p += e->getPoids();
        }
    }
    delete no_sym;
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
            Arete *newOne = new Arete(a1S2, a1S1, a1->getPoids());
            newAretes->push_back(newOne);   
            GC::getGCInstance()->addArete(newOne);
        }   
        isFound = false;    
    }    

    this->setAretes(newAretes); 
}

Graph::Etiquette* Graph::creerEnsemble(Sommet *u) {
    Etiquette *e = new Etiquette{u, u->getId()};
    return e;
}

list<Arete*>* Graph::trie(){
    list<Arete*> *l = getAretesNoSym();
    l->sort([](const Arete* a, const Arete* b) { return a->getPoids() < b->getPoids(); });
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

void Graph::do_union(const Sommet* u, const Sommet* v, list<Etiquette*> *ens_sommets) {
    int u_id = find(u, ens_sommets);
    int v_id = find(v, ens_sommets);
    for(auto elt : *ens_sommets){
        if(elt->id == v_id){
            elt->id = u_id;
        }       
    }
}

Graph Graph::kruskal(){
    list<Graph::Etiquette*> *ens_sommets = new list<Graph::Etiquette*>();
    list<Sommet*> *l = this->getSommets();
    list<Arete*> *ret = new list<Arete*>();
    
    for(auto el : *l){
        Etiquette* e1 = creerEnsemble(el);
        ens_sommets->push_back(e1);
    }

    list<Arete*> *sorted_aretes = trie();
    
    for(auto p : *sorted_aretes){
        const Sommet* s1 = p->getSommetsPair().sommet1;
        const Sommet* s2 = p->getSommetsPair().sommet2;

        if(find(s1, ens_sommets) != find(s2, ens_sommets)){
            ret->push_back(p);
            do_union(s1, s2, ens_sommets);
        }
    }
    return {ret, l};
};

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