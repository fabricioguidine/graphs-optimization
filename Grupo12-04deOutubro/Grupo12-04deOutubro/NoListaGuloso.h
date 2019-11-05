#ifndef NOLISTAGULOSO_H
#define NOLISTAGULOSO_H
#include "No.h"

using namespace std;

class NoListaGuloso
{
    public:
        NoListaGuloso(No* id);
        ~NoListaGuloso();
        void setProx(NoListaGuloso* prox);
        void setAnt(NoListaGuloso* ant);
        NoListaGuloso getProx();
        NoListaGuloso getAnt();

    private:
        No* ponteiro;
        NoListaGuloso* proximo;
        NoListaGuloso* anterior;
};
#endif
