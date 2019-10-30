#ifndef ARESTA_H
#define ARESTA_H
#include "Aresta.h"

using namespace std;

class Aresta
{
    public:
        Aresta(int idAlvo);                     // construtor
        ~Aresta();                              // destrutor
        int getIdAlvo();                        // retorna ID alvo
        Aresta* getProxAresta();                // retorna proxima aresta
        float getPeso();                        // retorna peso
        void setProxAresta(Aresta* aresta);     // modifica a proxima aresta
        void setPeso(float peso);               // modifica o peso

    private:
        int idAlvo;                             // ID de qual no é o destino da ligacao
        Aresta* proxAresta;                     // proxima aresta
        float peso;                             // peso da aresta

};

#endif // ARESTA_H
