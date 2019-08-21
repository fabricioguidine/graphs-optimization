#ifndef ARESTA_H
#define ARESTA_H



class Aresta
{
public:
    Aresta();
    ~Aresta();
    int idAresta;
    int noAdj;
    float pesoAresta;

private:
    Aresta *proxAresta;
    Aresta *antAresta;
};

#endif // ARESTA_H
