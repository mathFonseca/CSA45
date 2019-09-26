//------------------------------------------------------------------------------
// Arquivo criado para testar a biblioteca tda.h
// Autor: Matheus Fonseca Alexandre de Oliveira

#include "tda.h"
#include <iostream>
using namespace std;

int main()
{
    points_List* lista;
    Point* ponto, *ponto2, *ponto3;
    ponto = createPoint(10, 10);
    ponto2 = createPoint(20, 20);
    ponto3 = createPoint(30, 30);
    lista = createList();
    lista = append(ponto, lista);
    lista = append(ponto2, lista);
    lista = append(ponto3, lista);
    freeList(lista);
    return 0;
}