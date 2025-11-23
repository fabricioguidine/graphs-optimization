#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

Grafo::Grafo(int ordem, bool direcionado, bool arestaComPeso, bool noComPeso)
{
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->arestaComPeso = arestaComPeso;
    this->noComPeso = noComPeso;
    this->primeiroNo = this->ultimoNo = nullptr;
    this->numAresta = 0;
}

Grafo::~Grafo()
{
    No *proxNo = this->primeiroNo;
    while(proxNo != nullptr)
    {
        proxNo->removerTodasArestas();
        No *auxNo = proxNo->getProxNo();
        delete proxNo;
        proxNo = auxNo;
    }
}

int Grafo::getOrdem()
{
    return this->ordem;
}

int Grafo::getNumAresta()
{
    return this->numAresta;
}

bool Grafo::getDirecionado()
{
    return this->direcionado;
}

bool Grafo::getArestaComPeso()
{
    return this->arestaComPeso;
}

bool Grafo::getNoComPeso()
{
    return this->noComPeso;
}

No* Grafo::getPrimeiroNo()
{
    return this->primeiroNo;
}

No* Grafo::getUltimoNo()
{
    return this->ultimoNo;
}

void Grafo::insereNo(int id)
{
    No* aux = new No(id);           //cria o novo nó
    if(this->primeiroNo == nullptr) // se o grafo estiver vazio, seta o primeiro e o ultimo nó como o novo nó criado
    {
        primeiroNo=aux;
        ultimoNo=aux;
    }
    else                            // se o grafo já tiver nós
    {
        ultimoNo->setProxNo(aux);   //seta o próx do ultimo nó para o novo
        ultimoNo = aux;             //seta o ultimo nó como o novo nó criado
    }
}

void Grafo::insereAresta(int id, int idAlvo, float peso)
{
    if(!this->procuraNo(id)) //verifica se o nó inicial existe, senão, adiciona
        this->insereNo(id);

    if(!this->procuraNo(idAlvo)) //verifica se o nó final existe, senão, adiciona
        this->insereNo(idAlvo);

    if(this->direcionado == true)
    {
        No* aux = this->primeiroNo;
        while(aux->getId() != id && aux->getProxNo()!=NULL)
        {
            aux = aux->getProxNo();
        }
        aux->inserirAresta(idAlvo, peso);
        aux->incrementaGSaida();
        this->getNo(idAlvo)->incrementaGEntrada();
    }
    else
    {
        //adiciona uma aresta de id para idAlvo
        No* aux = this->primeiroNo;
        while(aux->getId() != id && aux->getProxNo()!=NULL)
        {
            aux = aux->getProxNo();
        }
        aux->inserirAresta(idAlvo, peso);
        aux->incrementaGEntrada();

        //adiciona uma aresta de idAlvo para id
        aux = this->primeiroNo;
        while(aux->getId() != idAlvo && aux->getProxNo()!=NULL)
        {
            aux = aux->getProxNo();
        }
        aux->inserirAresta(id, peso);
        aux->incrementaGEntrada();

    }
}

void Grafo::removeNo (int id)
{
}

bool Grafo::procuraNo (int id) //retorna true se o nó existir
{
    No* aux = this->primeiroNo;
    if(aux == nullptr)
        return false;

    while(aux->getId() != id && aux->getProxNo()!=NULL)
        aux = aux->getProxNo();

    if(aux->getId() == id)
        return true;
    else
        return false;
}

No* Grafo::getNo(int id) //retorna um ponteiro para o nó se ele existir
{
    No* aux = this->primeiroNo;
    if(aux == nullptr)
        return nullptr;

    while(aux->getId() != id && aux->getProxNo()!=NULL)
        aux = aux->getProxNo();

    if(aux->getId() == id)
        return aux;
    else
        return nullptr;
}

void Grafo::imprimeGrafo()
{
    No* aux = this->primeiroNo;
    while(aux != nullptr)
    {
        cout << "No de ID: " << aux->getId() << endl;
        cout << "Grau de entrada: " << aux->getGrauEntrada() << endl;
        cout << "Grau de saída: "  << aux->getGrauSaida()  << endl;
        cout << "Arestas: ";
        aux->imprimeArestas(arestaComPeso);
        aux = aux->getProxNo();
        cout << endl;
    }
}

void Grafo::imprimeNo(int id)
{
    No* aux = this->getNo(id);
    cout << "No de ID: " << aux->getId() << endl;
    cout << "Grau de entrada: " << aux->getGrauEntrada() << endl;
    cout << "Grau de saída: "  << aux->getGrauSaida()  << endl;
    cout << "Arestas: ";
    aux->imprimeArestas(arestaComPeso);
    cout << endl;
}

void Grafo::geraSaida(string arquivoSaida)
{
    ofstream saida;
    saida.open(arquivoSaida, ios::out);

    No* noAux;
    Aresta* arestaAux;

    if(saida.is_open())
    {
        saida << this->getOrdem() << endl;
        if(this->getPrimeiroNo() != nullptr)
        {
            for(noAux =  this->getPrimeiroNo(); noAux != nullptr; noAux = noAux->getProxNo())
            {
                saida << noAux->getId() << endl;
                if(noAux->getPrimeiraAresta() != nullptr)
                {
                    for(arestaAux = noAux->getPrimeiraAresta(); arestaAux!=nullptr; arestaAux = arestaAux->getProxAresta())
                    {
                        saida << "(" << arestaAux->getIdAlvo() << "," << arestaAux->getPeso() << ")" << endl;
                    }
                }
            }
        }
    }
}


void Grafo::buscaEmLargura (int id)
{
    bool* aux = new bool[this->ordem];
    for (int i=0; i<this->ordem; i++)
    {
        aux[i] = false;
    }
    queue<No*> fila;
    aux[id] = true;
    fila.push(this->getNo(id));
    while(!fila.empty())
    {
        Aresta* auxAresta = fila.front()->getPrimeiraAresta();
        while(auxAresta!=nullptr)
        {
            if(aux[auxAresta->getIdAlvo()] == false)
            {
                cout << "("<< fila.front()->getId() << "," << auxAresta->getIdAlvo() << ") nao e aresta de retorno" << endl;
                aux[auxAresta->getIdAlvo()] = true;
                fila.push(this->getNo(auxAresta->getIdAlvo()));
            }
            else
            {
                cout << "("<< fila.front()->getId() << "," << auxAresta->getIdAlvo() << ") e uma aresta de retorno" << endl;
            }
            auxAresta = auxAresta->getProxAresta();
        }
        fila.pop();
    }
}


void Grafo::auxBuscaEmProfundidade (int id, bool* aux)
{
    aux[id] = true;
    No* noAux = getNo(id);
    for(Aresta* arestaAux = noAux->getPrimeiraAresta(); arestaAux!=nullptr; arestaAux = arestaAux->getProxAresta())
    {
        if(aux[arestaAux->getIdAlvo()] == false)
        {
            cout << "("<< id<< "," << arestaAux->getIdAlvo() << ") nao e aresta de retorno" << endl;
            auxBuscaEmProfundidade(arestaAux->getIdAlvo(), aux);
        }
        else
        {
            cout << "("<< id<< "," << arestaAux->getIdAlvo() << ") e uma aresta de retorno" << endl;
        }
    }
}

void Grafo::buscaEmProfundidade (int id)
{
    bool* aux = new bool[this->ordem];
    for (int i=0; i<this->ordem; i++)
    {
        aux[i] = false;
    }
    auxBuscaEmProfundidade(id, aux);
}

void Grafo::ftd(int id)
{
    if(this->direcionado)
    {
        bool* aux = new bool[this->ordem];
        for (int i=0; i<this->ordem; i++)
        {
            aux[i] = false;
        }
        queue<No*> fila;
        aux[id] = true;
        fila.push(this->getNo(id));
        while(!fila.empty())
        {
            Aresta* auxAresta = fila.front()->getPrimeiraAresta();
            while(auxAresta!=nullptr)
            {
                if(aux[auxAresta->getIdAlvo()] == false)
                {
                    aux[auxAresta->getIdAlvo()] = true;
                    fila.push(this->getNo(auxAresta->getIdAlvo()));
                }
                auxAresta = auxAresta->getProxAresta();
            }
            fila.pop();
        }
        aux[id] = false;
        cout << "Nos alcancaveis a partir de " << id << ": ";
        for (int i=0; i<this->ordem; i++)
        {
            if(aux[i] == true)
            {
                cout << i << " ";
            }
        }
        cout<< endl;
    }
    else
    {
        cout << "Erro: grafo nao-direcionado" << endl;
    }
}

bool Grafo::ftiAux(int id, int noFTI, bool* alcance) //basicamente a função de busca em largura
{
    //id é o nó onde vai começar a busca em largura
    //noFTI é o nó que verificar se alcança

    Aresta* auxAresta = this->getNo(id)->getPrimeiraAresta();
    while(auxAresta!=nullptr) //Verifica se o nó id é adjacente a alguém que alcança o nó noFTI, se sim retorna true.
    {
        if(alcance[auxAresta->getIdAlvo()] == true)
            return true;
        auxAresta = auxAresta->getProxAresta();
    }

    bool* aux = new bool[this->ordem];
    for (int i=0; i<this->ordem; i++)
    {
        aux[i] = false;
    }
    queue<No*> fila;
    aux[id] = true;
    fila.push(this->getNo(id));
    while(!fila.empty())
    {
        auxAresta = fila.front()->getPrimeiraAresta();
        while(auxAresta!=nullptr)
        {
            if(aux[auxAresta->getIdAlvo()] == false)
            {
                aux[auxAresta->getIdAlvo()] = true;
                fila.push(this->getNo(auxAresta->getIdAlvo()));
            }
            auxAresta = auxAresta->getProxAresta();
        }
        fila.pop();
    }

    if(aux[noFTI] == true)
        return true;
    else
        return false;
}



void Grafo::fti(int id)
{
    bool* alcance = new bool[this->ordem];
    for (int i=0; i<this->ordem; i++)
        alcance[i] = false;

    for(No* i=this->getPrimeiroNo(); i!=nullptr; i=i->getProxNo())
    {
        alcance[i->getId()] = this->ftiAux(i->getId(), id, alcance);
    }

    alcance[id] = false;
    cout << "Nos que alcancam " << id << ": ";
    for (int i=0; i<this->ordem; i++)
    {
        if(alcance[i] == true)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

float* Grafo::dijkstra(int id, int idAlvo)
{

    //Acessar o nó de origem
    No* inicio = getNo(id);

    //COMO CONSULTAR - ESTRUTURA
    //Laço que visita todos os nos nao visitados

            //Laço que acessa todas os nós adjacentes, consultando os pesos das arestas

                //Atualização das distancias
                //escolha do menor caminho

}

float** Grafo::floydMarshall(int id, int idAlvo)
{

}

Aresta* Grafo::arvorePrim()
{

}

Aresta* Grafo::arvoreKruskal()
{

}

void Grafo::fechoTriadico()
{

}


NoListaGuloso* Grafo::ordena(No* E)
{

}

NoListaGuloso* Grafo::atualizaLista()
{

}


No* Grafo::algoritmoGuloso()
{
    No* E = new No[this.ordem];

    for(int i = 0; i <this.ordem; i++)
    {
        E[i] = nullptr;
    }
    int k = 0;
    for(No* i = this.primeiroNo; i!= nullptr; i = i.getProxNo())
    {
        E[k] = i;
        k++;
    }
}
