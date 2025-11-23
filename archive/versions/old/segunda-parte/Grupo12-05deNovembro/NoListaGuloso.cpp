#include "NoListaGuloso.h"

NoListaGuloso::NoListaGuloso(No* id)
{
    ponteiro = id;
}

NoListaGuloso::~NoListaGuloso()
{
    if(proximo != nullptr)
        proximo.setAnt(this.anterior);
    if(anterior != nullptr)
        anterior.setProx(this.proximo);
}

void NoListaGuloso::setProx(NoListaGuloso* prox)
{
    this.proximo = prox;
}

void NoListaGuloso::setAnt(NoListaGuloso* ant)
{
    this.anterior = ant;
}

NoListaGuloso NoListaGuloso::getProx()
{
    return proximo;
}

NoListaGuloso NoListaGuloso::getAnt()
{
    return anterior;
}
