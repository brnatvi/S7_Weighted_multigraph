
#include "Graph.hpp"
#include <typeinfo>

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

// getters/setters

int Graph::getId() const { return this->id; }   
list<Arete*> * Graph::getAretes() const { return this->listAretes; }
list<Sommet*> * Graph::getSommets() const { return this->listSommets; }
int Graph::getCounterGraphs() { return counterGraphs; };

void Graph::setAretes(list<Arete*> *l)
{
    if (this->listAretes)
    {        
        this->listAretes->clear();        
        delete this->listAretes;        
    }
    
    this->listAretes = new std::list<Arete*>();
    for (auto el:*l)
    {
        this->listAretes->push_back(el);
        //TODO: add newA to garbage collector
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

    for (Sommet* el : *l)
    {             
        this->listSommets->push_back(el);
        //TODO: add newS to garbage collector
    }       
}


// methods

// verification pour eviter d'ajouter un sommet deja present dans la liste
void Graph::ajoute_sommet(Sommet *s)
{        
    list<Sommet*> *l = this->getSommets();
    for (auto el : *l)
    {
        if (s == el)
        {
            cout << "DONT ADD SOMMET " << *s << endl;
            return;
        }       
    }
    cout << "ADD_SOMMET " << *s << endl;
    this->getSommets()->push_back(s);
} 

// pas de verification dans liste des sommets car nom d'un sommet n'est pas un identifiant
void Graph::ajoute_sommet(string nom) {  

    Sommet *newOne = new Sommet(nom);    
    //TODO: add newOne to garbage collector

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
    Arete *a = new Arete(s1, s2, p);
    //TODO: add a to garbage collector

    // ajoute_sommet verifie deja presence de sommet dans liste
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    this->getAretes()->push_back(a);  
}

void Graph::ajoute_arete(string nom1, string nom2, int poids) {
    Sommet *s1 = new Sommet(nom1);
    Sommet *s2 = new Sommet(nom2);
    //TODO: add s1 s2 to garbage collector
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    Arete *a = new Arete(s1, s2, poids);
    this->getAretes()->push_back(a);
}

bool Graph::hasSymetric(Arete *a, list<Arete*> *aretes){
    for(auto elt: *aretes){
        if(elt->getSommetsPair().sommet1 == a->getSommetsPair().sommet2 && 
        elt->getSommetsPair().sommet2 == a->getSommetsPair().sommet1 &&
        elt->getPoids() == a->getPoids()){
            return true;
        }
    }
    return false;
}

list<Arete*>* Graph::getAretesNoSym(){
    list<Arete*> *l = this->getAretes();
    list<Arete*> *no_sym = new list<Arete*>();
    cout << "ARETES_NO_SYM" << endl;
    for(auto elt: *l){ 
        if(!hasSymetric(elt, no_sym)){
            cout << *(elt) << endl;
            no_sym->push_back(elt);
        }
    }
    return no_sym;
}

int Graph::poids(){
    int p = 0;
    list<Arete*> *no_sym = getAretesNoSym();
    for(auto e: *no_sym){
        p += e->getPoids();
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
            //TODO: add newOne to garbage collector         
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
    cout << "SORTED ARETES" << endl;
    for(auto pp: *sorted_aretes){
        cout << *pp << endl;
    }
    for(auto p : *sorted_aretes){
        int s1 = find(p->getSommetsPair().sommet1, ens_sommets);
        int s2 = find(p->getSommetsPair().sommet2, ens_sommets); 
        cout << "sorted_artes " << *p << " " << s1 << " " << s2 <<  endl;
        if(find(p->getSommetsPair().sommet1, ens_sommets) != find(p->getSommetsPair().sommet2, ens_sommets)){
            ret->push_back(p);
            do_union(p->getSommetsPair().sommet1, p->getSommetsPair().sommet2, ens_sommets);
        }
    }
    cout << "ACM details" << endl;
    for(auto toto : *ret){
        cout << *(toto) << endl;
    }
    
    return {ret, l};

    
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


/*
void Graph::kruskal(){
    list<Graph::Etiquette> ens_sommets = {};
    list<Sommet*> *l = this->getSommets();
    list<Arete*> *ret = new list<Arete*>();
    cout << "push_back" << endl;
    for(auto el : *l){
        Etiquette e1 = creerEnsemble(el);
        ens_sommets.push_back(e1);
        cout << *(e1.v) << ": " << e1.v << endl;
    }
    cout << "Ens_sommets" << endl;
    for(auto a : ens_sommets){
        cout << &a << endl;
        cout << *(a.v) << ": " << a.v << endl;
        cout << "\n" << endl;
    }
    
    list<Arete*> *sorted_aretes = trie();
    cout << "SORTED ARETES" << endl;
    for(auto p : *sorted_aretes){
        int s1 = find(p->getSommetsPair().sommet1, ens_sommets);
        int s2 = find(p->getSommetsPair().sommet2, ens_sommets); 
        cout << s1 << " " << s2 << endl;
        
        if(find(p->getSommetsPair().sommet1, ens_sommets) != find(p->getSommetsPair().sommet2, ens_sommets)){
            ret->push_back(p);
            ens_sommets = do_union(p->getSommetsPair().sommet1, p->getSommetsPair().sommet2, ens_sommets);
        }
        
        cout << "FINAL" << endl;
        for(auto toto : *ret){
            cout << *(toto) << endl;
        }
        
    }   
    
}
*/