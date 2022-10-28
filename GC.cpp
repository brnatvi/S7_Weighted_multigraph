#include "GC.hpp"


GC *GC::getGCInstance()
{
    static GC g_pGC;
    return &g_pGC;
}


// ==============  constructors / destructor =======================================================             
GC::GC(){     
   cout << "GC " << this << " viens d'être creé" << endl;
}

GC::~GC(){       
    cout << endl << "==== Report GC Destructor: il y avaient "
         << listSommets.size() 
         << " sommets et " 
         << listAretes.size() 
         << " aretes creé par malloc ==== " 
         <<  endl;

    while(!listAretes.empty()){
        Arete* p_arret = listAretes.front();
        cout << "GC Arret: " << p_arret << "   (" << p_arret->getPoids() << ")" << endl;
        listAretes.pop_front();      
        delete p_arret;
    }    

    while(!listSommets.empty()){   
        Sommet* p_sommet = listSommets.front();
        cout << "GC Sommet:" << p_sommet << endl;
        listSommets.pop_front();      
        delete p_sommet;
    }
}        

void GC::addArete(Arete *newArete){
    if (!newArete){
        cout << "ERROR: NULL arete" << endl;
        return;
    }

    for (auto el: listAretes){
        if (el == newArete){
            cout << "WARNING: Arete déjà existe" << *newArete << endl;
            return;
        }    
    }

    listAretes.push_back(newArete);
}

void GC::addSommet(Sommet *newSommet){
    if (!newSommet){
        cout << "ERROR: NULL sommet" << endl;
        return;
    }

    for (auto el: listSommets){
        if (el == newSommet){
            cout << "WARNING: Sommet déjà existe" << *newSommet << endl;
            return;
        }    
    }

    listSommets.push_back(newSommet);
}
