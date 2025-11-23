#ifndef NO_H
#define NO_H


class No
{
public:
    No();
    ~No();
    int idNo;
    int din; //grau de entrada
    int dout; //grau de saída
    float pesoNo;


private:
    void auxTransDir ();
    void auxTransIndir ();
    No *proxNo;
    No *antNo;
    Aresta *adj;
};

#endif // NO_H
