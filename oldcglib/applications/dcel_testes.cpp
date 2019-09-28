#include "dcel.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    Edge* aresta;
    Point* ponto;
    ponto = createPoint(10, 10);
    aresta = createEdge(ponto, ponto);
    printEdge(aresta);
    freeEdge(aresta);
    return 0;
}
