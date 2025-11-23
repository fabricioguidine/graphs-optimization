#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

No::No(int id)
{
    this->id = id;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->peso = 0;
    this->primeiraAresta = nullptr;
    this->ultimaAresta = nullptr;
    this->proxNo = nullptr;
}

No::~No()
{
    Aresta* proxAresta = this->primeiraAresta;
    while(proxAresta != nullptr)
    {
        Aresta* auxAresta = proxAresta->getProxAresta();
        delete proxAresta;
        proxAresta = auxAresta;
    }
}

Aresta* No::getPrimeiraAresta()
{
    return this->primeiraAresta;
}

Aresta* No::getUltimaAresta()
{
    return this->ultimaAresta;
}

int No::getId()
{
    return this->id;
}

int No::getGrauEntrada()
{
    return this->grauEntrada;
}

int No::getGrauSaida()
{
    return this->grauSaida;
}

float No::getPeso()
{
    return this->peso;
}

No* No::getProxNo()
{
    return this->proxNo;
}

void No::setProxNo(No* proxNo)
{
    this->proxNo = proxNo;
}

void No::setPeso(float peso)
{
    this->peso = peso;
}

void No::inserirAresta(int idAlvo, float peso)
{
    if(this->primeiraAresta != nullptr)
    {
        Aresta* aresta = new Aresta(idAlvo);
        aresta->setPeso(peso);
        this->ultimaAresta->setProxAresta(aresta);
        this->ultimaAresta = aresta;
    }
    else
    {
        this->primeiraAresta = new Aresta(idAlvo);
        this->primeiraAresta->setPeso(peso);
        this->ultimaAresta = this->primeiraAresta;
    }
}

void No::removerTodasArestas()
{
    if(this->primeiraAresta != nullptr)
    {
        Aresta* proximo = nullptr;
        Aresta* aux = this->primeiraAresta;
        while(aux != nullptr)
        {
            proximo = aux->getProxAresta();
            delete aux;
        }
    }
    this->primeiraAresta = this->ultimaAresta = nullptr;
}

int No::removerAresta(int id, bool direcionado, No* idAlvo)
{
    if(this->procuraAresta(id))
    {
        Aresta* aux = this->primeiraAresta;
        Aresta* anterior = nullptr;
        while(aux->getIdAlvo() != id)
        {
            anterior = aux;
            aux = aux->getProxAresta();
        }
        if(anterior != nullptr)
            anterior->setProxAresta(aux->getProxAresta());

        else
            this->primeiraAresta = aux->getProxAresta();

        if(aux == this->ultimaAresta)
            this->ultimaAresta = anterior;

        if(aux->getProxAresta() == this->ultimaAresta)
            this->ultimaAresta = aux->getProxAresta();

        delete aux;

        if(direcionado)
            this->decrementaGSaida();

        else
        {
            this->decrementaGEntrada();
            idAlvo->decrementaGEntrada();
        }
        return 1;
    }
    return 0;
}

bool No::procuraAresta(int idAlvo)
{
    if(this->primeiraAresta != nullptr)
    {
        for(Aresta* aux = this->primeiraAresta; aux != nullptr; aux = aux->getProxAresta())
            if(aux->getIdAlvo() == idAlvo)
                return true;
    }
    return false;
}

void No::incrementaGEntrada()
{
    this->grauEntrada++;
}

void No::incrementaGSaida()
{
    this->grauSaida++;
}

void No::decrementaGEntrada()
{
    this->grauEntrada--;
}

void No::decrementaGSaida()
{
    this->grauSaida--;
}

Aresta* No::temAresta(int idAlvo)
{
    for(Aresta *auxAresta = this->primeiraAresta; auxAresta != nullptr; auxAresta->getProxAresta())
    {
        if(auxAresta->getIdAlvo() == idAlvo)
            return auxAresta;
    }
    return nullptr;
}

void No::imprimeArestas(bool arestaComPeso)
{
    Aresta* aux = this->primeiraAresta;
    while(aux != nullptr)
    {
        if(!arestaComPeso) // falso = aresta sem peso /// verdadeiro = aresta com peso
            cout << "(" << aux->getIdAlvo() << "," << aux->getPeso() <<") ";
        else
            cout << "(" << aux->getIdAlvo() << ") ";
        aux = aux->getProxAresta();
    }
    cout << endl;
}
