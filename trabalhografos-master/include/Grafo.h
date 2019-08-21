#ifndef GRAFO_H
#define GRAFO_H
//#include "No.h"
//#include "Aresta.h"


class Grafo
{
public:
    Grafo();
    ~Grafo();
    int ordem;
    void caminLarg (int id);
    void caminProf (int id);
    void transDir (int id);
    void transIndir (int id);
    void caminMinD (int saida, int chegada);
    void caminMinF (int saida, int chegada);
    Aresta *prim ();
    Aresta *kruskal ();
    float triade (); // dividir o resultado das triades fechadas por 3!!!!!!!!

private:
    No *inicio;
    No *ultimo;
    int n; // número de nós do grafo
    bool pond;
    bool dir;
    bool ponderado();  // verifica se o grafo é ponderado
    bool dir();  // verifica se o grafo é orientado/direcionado
};

#endif // GRAFO_H
