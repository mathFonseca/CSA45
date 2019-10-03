#include "dcel.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
void testeCriaAresta();
void testeCriaPonto();
void testaLeft();
void testaConnect();
int main()
{
    Edge *aresta;
    Point *ponto_1, *ponto_2, *ponto_3;

    //testeCriaAresta();
    //testeCriaPonto();
    //testaLeft();
    testaConnect();
    
    return 0;
}

void testeCriaAresta()
{
    Edge *aresta_1;
    aresta_1 = createEdge();
    cout << "Aresta: \n";
    cout << aresta_1 << "\n" << aresta_1->next << "\n" << aresta_1->prev << "\n" << aresta_1->twin << "\n";
    cout << aresta_1->left_face << "\n";
    cout << aresta_1->point << "\n";
}

void testeCriaPonto()
{
    Point *ponto;
    ponto = createPoint(0, 0);
    cout << "Ponto: \n";
    cout << ponto << "\n" << ponto->x << "," << ponto->y << "\n";
    cout << ponto->edge << "\n";
}

void testaLeft()
{
    Point *A, *B, *C;
    A = createPoint(0, 0);
    B = createPoint(3, 0);
    C = createPoint(4, -1);
    if(left(A, B, C))
    {
        cout << "It's Left\n";
    }
    else
    {
        cout << "It's Not Left\n";
    }

    if(leftOn(A, B, C))
    {
        cout << "It's Left On\n";
    }
    else
    {
        cout << "It's Not Left On\n";
    }
    
}

void testaConnect()
{
    Point *A, *B, *C, *D;
    A = createPoint(0, 0);
    B = createPoint(0, 5);   
    C = createPoint(0, -5);
    D = createPoint(5, 0);
    connect(A, B);
    connect(A, C);
    connect(A, D);
    cout << "Points: \n";
    cout << "A: " << A << "\n";
    cout << "B: " << B << "\n";
    cout << "C: " << C << "\n";
    cout << "D: " << D << "\n";    

    cout << "Print Sequence: \n";
    cout << "A->(B): " << A->edge->point << "\n";
    cout << "B->(A): " << A->edge->next->point << "\n";
    cout << "A->(C): " << A->edge->next->next->point << "\n";
    cout << "C->(A): " << A->edge->next->next->next->point << "\n";
    cout << "A->(D): " << A->edge->next->next->next->next->point << "\n";
    cout << "D->(A): " << A->edge->next->next->next->next->next->point << "\n";

}

