#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo.h"
#include "No.h"

using namespace std;

Grafo* leituraInstancia(ifstream& arquivoEntrada, bool direcionado, bool arestaComPeso, bool noComPeso)
{
    //Variáveis para auxiliar na criação dos nós no Grafo
    int id;
    int idAlvo;
    int ordem;
    float peso;

    //Pegando a ordem do grafo
    arquivoEntrada >> ordem;

    //Criando objeto grafo
    Grafo* G = new Grafo(ordem, direcionado, arestaComPeso, noComPeso);

    //Leitura de arquivo
    if(!G->getArestaComPeso() && !G->getNoComPeso())             /// aresta sem peso e no sem peso
    {
        while(arquivoEntrada >> id >> idAlvo)
            G->insereAresta(id, idAlvo, 0);         // insere arestas sem peso
    }
    else if(G->getArestaComPeso() && !G->getNoComPeso())         /// aresta com peso e no sem peso
    {
        float peso;
        while(arquivoEntrada >> id >> idAlvo >> peso)
            G->insereAresta(id, idAlvo, peso);      // insere arestas com peso
    }

/*
    else if(G->getNoComPeso() && !G->getArestaComPeso())          /// no com peso e aresta sem peso
    {
        float idPeso, idAlvoPeso;
        while(arquivoEntrada >> id >> idPeso >> idAlvo >> idAlvoPeso)
        {
            G->insereAresta(id, idAlvo, 0);         // insere aresta sem peso
            G->getNo(id)->setPeso(idPeso);          // seta no inicial com peso
            G->getNo(idAlvo)->setPeso(idAlvoPeso);  // seta no alvo com peso
        }
    }
    else if(G->getNoComPeso() && G->getArestaComPeso())           /// no com peso e aresta com peso
    {
        float idPeso, idAlvoPeso, pesoAresta;
        while(arquivoEntrada >> id >> idPeso >> idAlvo >> idAlvoPeso)
        {
            G->insereAresta(id, idAlvo, pesoAresta);        // insere aresta com peso
            G->getNo(id)->setPeso(idPeso);                  // seta no inicial com peso
            G->getNo(idAlvo)->setPeso(idAlvoPeso);          // seta no alvo com peso
        }
    }
*/
    return G;
}

//

int main(int argc, char const *argv[])
{

// nome do arquivo de entrada
// nome de arquivo de saída
// uma flag 0 ou 1 para indicar que o grafo é não orientado ou orientado (nesta ordem)
// uma flag 0 ou 1 para indicar que o grafo é não ponderado ou ponderado nas arestas (nesta ordem)
// uma flag 0 ou 1 para indicar que o grafo é não ponderado ou ponderado nos nós (nesta ordem)

    ifstream arquivoEntrada;
    bool dir, areP, noP;
    arquivoEntrada.open(argv[1]);

    Grafo* G;

    if(arquivoEntrada.is_open())
    {
        cout << "O grafo e direcionado? Digite 0 para nao e 1 para sim." << endl;
        cin >> dir;
        cout << "O grafo e ponderado nas arestas? Digite 0 para nao e 1 para sim. "<< endl;
        cin >> areP;
        cout << "O grafo e ponderado nos vertices? Digite 0 para nao e 1 para sim." << endl;
        cin >> noP;
        G = leituraInstancia(arquivoEntrada, dir, areP, noP);
        system ("CLS");
    }
    else
    {
        cout << "Nao e possivel abrir: " << argv[1];
        return 0;
    }
    unsigned long int menu = 99;  //bug: caso haja overflow o menu é impresso repetida e infinitamente
    while(menu !=0)
    {
        cout << "Digite o numero da operacao que você deseja realizar" << endl <<endl;
        cout << "0 - Salvar saida e fechar fechar programa" << endl;
        cout << "1 - Inserir no" << endl;
        cout << "2 - Remover no" << endl;
        cout << "3 - Inserir aresta" << endl;
        cout << "4 - Remover aresta" << endl;
        cout << "5 - Buscar no" << endl;
        cout << "6 - Imprimir grafo" << endl;
        cout << "7 - Imprimir no" << endl;
        cout << "8 - Busca em Largura" << endl;
        cout << "9 - Busca em Profundidade" << endl;
        cout << "10 - Fecho Transitivo Direto" << endl;
        cout << "11 - Caminho minimo por algoritmo de Dijkstra" << endl;
        cout << "12 - Caminho minimo por algoritmo de Floyd-Marshall" << endl;
        cout << "13 - Arvore Geradora de Primm" << endl;
        cout << "14 - Arvore Geradora de Kruskall" << endl;
        cout << "15 - Fecho triadico" << endl;
        cout << endl;
        cin >> menu;

        int noSaidaTemp, noEntradaTemp;
        int pesoTemp =0;
        switch (menu)
        {

            case 0: //Salvar saida e fechar fechar programa
                G->geraSaida(argv[2]);
                break;
            case 1: //Inserir no
                cout << "Insira o ID do no" << endl;
                cin >> noSaidaTemp;
                G->insereNo(noSaidaTemp);
                system("CLS");
                break;
            case 2: //Remover no
                cout << "Insira o ID do no" << endl;
                cin >> noSaidaTemp;
                G->removeNo(noSaidaTemp);
                system("CLS");
                break;
            case 3: //Inserir aresta
                cout << "Insira o ID do no de saída" << endl;
                cin >> noSaidaTemp;
                cin >> noEntradaTemp;
                if(G->getArestaComPeso())
                    cin >> pesoTemp;
                G->insereAresta(noSaidaTemp, noEntradaTemp, pesoTemp);
                system("CLS");
                break;
            case 4: // Remover aresta
                break;
            case 5: // Buscar no
                break;
            case 6: // Imprimir grafo
                break;
            case 7: // Imprimir no
                break;
            case 8: // Busca em Largura
                break;
            case 9: // Busca em Profundidade
                break;
            case 10: // Fecho Transitivo Direto
                break;
            case 11: // Caminho minimo por algoritmo de Dijkstra
                break;
            case 12: //Caminho minimo por algoritmo de Floyd-Marshall
                break;
            case 13: //Arvore Geradora de Primm
                break;
            case 14: //Arvore Geradora de Kruskall
                break;
            case 15: //Fecho triadico
                break;
            default:
                system("CLS");
                break;
        }
    }
//    G->imprimeNo(33);
//    G->imprimeGrafo();
//    G->buscaEmProfundidade(33);
//    G->buscaEmLargura(33);
//    G->ftd(33);
//    G->fti(28);
    return 0;
}
