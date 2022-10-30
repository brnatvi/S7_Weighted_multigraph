
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
}

Graph::Graph(const Graph *oldGraph) : listAretes{nullptr}, listSommets{nullptr}
{
    setSommets(oldGraph->getSommets());
    setAretes(oldGraph->getAretes());
    this->id = ++counterGraphs;
}

Graph::~Graph()
{
    this->listAretes->clear();                          // AZ
    delete (this->listAretes);
    this->listSommets->clear();                         // AZ
    delete (this->listSommets);
    counterGraphs --;
    cout << "Graph     " << this << " est detruit" << endl;
}

//========================== setters ======================================================

void Graph::setAretes(list<Arete *> *l)
{
    if (this->listAretes)                                   // free old list
    {
        this->listAretes->clear();
        delete this->listAretes;
    }

    this->listAretes = new std::list<Arete *>();            // free memory in ~Graph()

    if (l)
    {
        for (auto el : *l)
        {
            const Arete::Pair el_pair = el->getSommetsPair();
            ajoute_sommet((Sommet *)(el_pair.sommet1));
            ajoute_sommet((Sommet *)(el_pair.sommet2));
            this->listAretes->push_back(el);
        }
    }
}

void Graph::setSommets(list<Sommet *> *l)
{
    if (this->listSommets)                              // free old list
    {
        this->listSommets->clear();
        delete this->listSommets;
    }

    this->listSommets = new std::list<Sommet *>();      // free memory in ~Graph()

    if (l)
    {
        for (Sommet *el : *l)
        {
            this->listSommets->push_back(el);
        }
    }
}

// ===================== ajoute_arete() et ajoute_sommet() ==================================

// verification pour eviter d'ajouter un sommet deja present dans la liste
void Graph::ajoute_sommet(Sommet *s)
{
    list<Sommet *> *l = this->getSommets();
    if(l){
        for (auto el : *l)
        {
            if (s == el) { return; }
        }
        l->push_back(s);
    }
    
}

// pas de verification dans liste des sommets car nom d'un sommet n'est pas un identifiant
void Graph::ajoute_sommet(string nom)
{
    Sommet *newOne = new Sommet(nom); // free memory by GC
    GC::getGCInstance()->addSommet(newOne);
    this->getSommets()->push_back(newOne);
}

// verification pour eviter d'ajouter une arete deja presente dans la liste
void Graph::ajoute_arete(Arete *a)
{
    list<Arete *> *l = this->getAretes();
    if (l)
    {
        for (auto el : *l)
        {
            if (a == el) { return; }
        }
        l->push_back(a);
    }
}

// "Il peut y avoir plusieurs aretes (chacune avec son poids propre) avec les memes extremites" => pas besoin de verification dans liste aretes
void Graph::ajoute_arete(Sommet *s1, Sommet *s2, int p)
{
    Arete *a = new Arete(s1, s2, p); // free memory by GC
    GC::getGCInstance()->addArete(a);

    // ajoute_sommet verifie deja presence de sommet dans liste
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    this->getAretes()->push_back(a);
}

void Graph::ajoute_arete(string nom1, string nom2, int poids)
{
    Sommet *s1 = new Sommet(nom1); // free memory by GC
    Sommet *s2 = new Sommet(nom2); // free memory by GC
    GC::getGCInstance()->addSommet(s1);
    GC::getGCInstance()->addSommet(s2);
    ajoute_sommet(s1);
    ajoute_sommet(s2);
    Arete *a = new Arete(s1, s2, poids); // free memory by GC
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

void Graph::symetrise()
{
    list<Arete *> *aretes = this->getAretes();    // free memory in setAretes()
    list<Arete *> *newAretes = new list<Arete *>; // free memory in ~Graph()
    cloneList(aretes, newAretes);
    bool isFound = false;

    for (Arete *a1 : *aretes)
    {
        const Sommet *a1S1 = a1->getSommetsPair().sommet1;
        const Sommet *a1S2 = a1->getSommetsPair().sommet2;

        for (Arete *a2 : *aretes)
        {
            const Sommet *a2S1 = a2->getSommetsPair().sommet1;
            const Sommet *a2S2 = a2->getSommetsPair().sommet2;

            if ((a1S1 == a2S2) && (a1S2 == a2S1) && (a1->getPoids() == a2->getPoids()))
            {
                isFound = true;
            }
        }
        if (!isFound)
        {
            Arete *newOne = new Arete(a1S2, a1S1, a1->getPoids()); // free memory by GC
            newAretes->push_back(newOne);                          // free memory by GC
            GC::getGCInstance()->addArete(newOne);
        }
        isFound = false;
    }

    this->setAretes(newAretes);
}

// ======================== kruskal() ===============================================

list<Arete *> *Graph::trie()
{
    list<Arete *> *l = getAretesNoSym(); // alloc memory - free memory in kruskal()
    l->sort([](const Arete *a, const Arete *b)
            { return a->getPoids() < b->getPoids(); });
    return l;
}

int Graph::find(const Sommet *u, list<Etiquette *> *ens_sommets)
{
    for (auto elt : *ens_sommets)
    {
        if (u == (elt->v))
        {
            return elt->id;
        }
    }
    return -1;
}

void Graph::doUnion(const Sommet *u, const Sommet *v, list<Etiquette *> *ens_sommets)
{
    int u_id = find(u, ens_sommets);
    int v_id = find(v, ens_sommets);
    for (auto elt : *ens_sommets)
    {
        if (elt->id == v_id)
        {
            elt->id = u_id;
        }
    }
}

Graph Graph::kruskal()
{
    list<Graph::Etiquette *> *ens_sommets = new list<Graph::Etiquette *>(); // free memory below
    list<Sommet *> *l = this->getSommets();
    list<Arete *> *ret = new list<Arete *>(); // free memory by GC

    for (auto el : *l)
    {
        Etiquette *e1 = new Etiquette{el, el->getId()}; // free memory below
        ens_sommets->push_back(e1);
    }

    list<Arete *> *sorted_aretes = trie();

    for (auto el : *sorted_aretes)
    {
        const Sommet *s1 = el->getSommetsPair().sommet1;
        const Sommet *s2 = el->getSommetsPair().sommet2;

        if (find(s1, ens_sommets) != find(s2, ens_sommets))
        {
            ret->push_back(el);
            doUnion(s1, s2, ens_sommets);
        }
    }
    for (auto el : *ens_sommets)
    {
        delete (el);
    }

    ens_sommets->clear();
    delete ens_sommets;

    sorted_aretes->clear();
    delete sorted_aretes;

    return {ret, l};
}

// ======================== poids() ===============================================

bool Graph::hasSymetric(Arete *a, list<Arete *> *aretes)
{
    for (auto el : *aretes)
    {
        const Arete::Pair el_pair = el->getSommetsPair();
        const Arete::Pair a_pair = a->getSommetsPair();

        if (el_pair.sommet1 == a_pair.sommet2 &&
            el_pair.sommet2 == a_pair.sommet1 &&
            el->getPoids() == a->getPoids())
        {
            return true;
        }
    }
    return false;
}

list<Arete *> *Graph::getAretesNoSym()
{
    list<Arete *> *l = this->getAretes();
    list<Arete *> *no_sym = new list<Arete *>(); // free memory in poids() and kruskal()
    for (auto el : *l)
    {
        if (!hasSymetric(el, no_sym))
        {
            no_sym->push_back(el);
        }
    }
    return no_sym;
}

int Graph::poids()
{
    int p = 0;
    list<Arete *> *no_sym = getAretesNoSym(); // alloc memory - free memory below

    for (auto el : *no_sym)
    {
        p += el->getPoids();
    }

    no_sym->clear();
    delete no_sym;

    return p;
}

// ==========================  print ================================================================
ostream &operator<<(ostream &out, Graph &x)
{
    list<Sommet *> *sommets = x.getSommets();
    list<Arete *> *aretes = x.getAretes();

    cout << "graph " << x.getId() << " avec les sommets : ";
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