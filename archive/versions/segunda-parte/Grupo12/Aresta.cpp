#include "Aresta.h"
#include <iostream>

using namespace std;

Aresta::Aresta(int idAlvo)
{
    this->idAlvo = idAlvo;
    this->proxAresta = nullptr;
    this->peso = 0;
}

Aresta::~Aresta()
{
    if(this->proxAresta != nullptr)
    {
        delete this->proxAresta;
        this->proxAresta = nullptr;
    }
}

int Aresta::getIdAlvo()
{
    return this->idAlvo;
}

Aresta* Aresta::getProxAresta()
{
    return this->proxAresta;
}

float Aresta::getPeso()
{
    return this->peso;
}

void Aresta::setProxAresta(Aresta* aresta)
{
    this->proxAresta = aresta;
}

void Aresta::setPeso(float peso)
{
    this->peso = peso;
}
