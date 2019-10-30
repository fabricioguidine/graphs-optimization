#ifndef GRAFO_H
#define GRAFO_H
#include "No.h"
#include <fstream>
#include <stack>
#include <queue>
#include <list>

using namespace std;

class Grafo
{
    public:
        Grafo(int ordem, bool direcionado, bool arestaComPeso, bool noComPeso);     // construtor
        ~Grafo();                                                                   // destrutor
        int getOrdem();                                                             // retorna ordem do grafo
        int getNumAresta();                                                         // retorna numero de arestas
        bool getDirecionado();                                                      // verifica se eh direcionado
        bool getArestaComPeso();                                                    // verifica se eh ponderado nas arestas
        bool getNoComPeso();                                                        // verifica se eh ponderado nos nos
        No* getPrimeiroNo();                                                        // retorna primeiro no
        No* getUltimoNo();                                                          // retorna ultimo no
        void insereNo(int id);                                                      // insere no
        void insereAresta(int id, int idAlvo, float peso);                          // insere aresta
        void removeNo (int id);                                                     // remove no
        bool procuraNo (int id);                                                    // procura no
        No* getNo(int id);                                                          // retorna no
        void imprimeGrafo();                                                        // imprime o grafo na tela
        void imprimeNo(int id);                                                     // imprime informação de um nó
        void geraSaida (string saida);                                            // gera arquivo de saída

        //a
        void buscaEmLargura (int id);                                               // busca em largura
        //b
        void buscaEmProfundidade (int id);                                          // busca em profundidade
        void auxBuscaEmProfundidade (int id, bool* aux);

        //d
        void ftd(int id);                                                           // fecho transitivo direto
        //e
        bool ftiAux(int id, int noFTI, bool* alcance);
        void fti(int id);                                                           // fecho transitivo indireto
        //f
        float* dijkstra(int id, int idAlvo);                                        // caminho minimo (dijkstra)
        //g
        float** floydMarshall(int id, int idAlvo);                                  // caminho minimo (floyd)
        //h
        Aresta* arvorePrim();                                                       // Árvore Geradora Mínima de Prim
        //i
        Aresta* arvoreKruskal();                                                    // Árvore Geradora Mínima de Kurskal
        //j
        void fechoTriadico();                                                       // Fecho triádico

    private:
        int ordem;
        int numAresta;
        bool direcionado;
        bool arestaComPeso;
        bool noComPeso;
        No* primeiroNo;
        No* ultimoNo;
        string saida;

        // funcoes auxiliares
};

#endif // GRAFO_H
