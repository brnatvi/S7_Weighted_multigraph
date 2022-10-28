#ifndef GC_H
#define GC_H

#include <iostream>
#include <cstring>
#include "Graph.hpp"

class GC        // made by singletone pattern
{
    private:
        std::list<Arete *> listAretes;
        std::list<Sommet *> listSommets;

        GC();
    public:
        ~GC();

        static GC *getGCInstance();

        GC(GC const&)               = delete;
        void operator = (GC const&) = delete;        

        void addArete(Arete *newArete);
        void addSommet(Sommet *newSommet);
};

#endif