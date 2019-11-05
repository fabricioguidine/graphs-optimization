#ifndef NO_H
#define NO_H
#include "Aresta.h"

using namespace std;

class No
{
    public:
        No(int id);                                                 // construtor
        ~No();                                                      // destrutor
        int getId();                                                // retorna ID no
        int getGrauEntrada();                                       // retorna grau de entrada do no
        int getGrauSaida();                                         // retorna grau de saida do no
        float getPeso();                                            // retorna peso do no
        No* getProxNo();                                            // retorna proximo no
        Aresta* getPrimeiraAresta();                                // retorna primeira aresta
        Aresta* getUltimaAresta();                                  // retorna ultima aresta

        void setProxNo(No* no);                                     // modifica proximo no
        void setPeso(float peso);                                   // modifica peso no

        bool procuraAresta(int idAlvo);                             // procura aresta no no
        void inserirAresta(int idAlvo, float peso);                 // inserir aresta em no, passando o destino da aresta e o peso
        void removerTodasArestas();                                 // remover todas as arestas
        int removerAresta(int id, bool direcionado, No* noAlvo);    // remover arestas do no indicado, dizendo se eh direcionado
        void incrementaGSaida();                                    // incrementa grau de saida do no
        void incrementaGEntrada();                                  // incrementa grau de entrada do no
        void decrementaGSaida();                                    // decrementa grau de saida do no
        void decrementaGEntrada();                                  // decrementa grau de entrada do no
        Aresta* temAresta(int idAlvo);                              // verifica e retorna se ha aresta em
        void imprimeArestas(bool arestaComPeso);                    // imprime as arestas

    private:
        int id;
        unsigned int grauEntrada;
        unsigned int grauSaida;
        float peso;
        No* proxNo;
        Aresta* primeiraAresta;
        Aresta* ultimaAresta;
};

#endif // NO_H
