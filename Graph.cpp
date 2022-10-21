
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

bool Graph::hasAreteSym(Arete *a){
    list<Arete*> *aretes = this->getAretes();
    for(Arete* el: *aretes){
        if(&el->getSommets().front() == &a->getSommets().back() && 
        &el->getSommets().back() == &a->getSommets().front() &&
        el->getPoids() == a->getPoids()){
            return true;
        }
    }
    return false;
}

void Graph::symetrise(){
    list<Arete*> *aretes = this->getAretes();
    list<Arete*> newListAretes = {};
    cout << aretes << endl;
    cout << this->getAretes() << endl;
}
/*
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
*/

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