#include "dcel.h"
#include <stdlib.h> 
#include <iostream>
using namespace std;

#define CONNECT_DEBUGs
#define LEFT_DEBUGs
#define CREATE_POINT_DEBUGs
#define INCONE_DEBUG

/* 
*   Cria dinamicamente uma aresta
*   Aresta é isolada, sem pontos definidos.
*   Next de new_edge é sua twin. Prev de new_edge é sua twin.
*   Ambas apontam para a mesma face, que é todo o resto do plano (null)
*/
Edge* createEdge()
{
    // Aloca os espaços
    Edge *edge = new(Edge);
    Edge *edge_twin = new(Edge);
    
    // Associa os twins.
    edge->twin = edge_twin;
    edge_twin->twin = edge;

    // Associa os next e prev
    edge->next = edge->twin;
    edge->prev = edge->twin;

    edge_twin->next = edge_twin->twin;
    edge_twin->prev = edge_twin->twin;

    // Associa as faces
    edge->left_face = NULL;
    edge_twin->left_face = NULL;

    // Associa os pontos
    edge->point = NULL;
    edge_twin->point = NULL;

    return edge;
}

/*
*   Cria dinamicamente um ponto
*   Ponto utiliza as coordenadas x,y
*   Inicialmente, não tem nenhuma aresta associdada. (null) 
*/
Point* createPoint(double x, double y)
{
    Point *new_point = new(Point);
    new_point->x = x;
    new_point->y = y;
    new_point->edge = NULL;
    #ifdef CREATE_POINT_DEBUG
        cout << "Point created: " << new_point << "\n";
        cout << "Values: (" << new_point->x << "," << new_point->y << ")\n";
    #endif
    return new_point;
}

/*
*   Verifica a condição de left de C para a aresta AB.
*/
bool left(Point *A, Point *B, Point *C)
{
    double area;
    area = ((B->x - A->x) * (C->y - A->y)) - ((C->x - A->x) * (B->y - A->y) );
    area = area/2;
    return (area > 0) ? true : false;
}

/*
*   Verifica a condição de leftOn de C para a aresta AB.
*/
bool leftOn(Point *A, Point *B, Point *C)
{
    double area;
    area = ((B->x - A->x) * (C->y - A->y)) - ((C->x - A->x) * (B->y - A->y) );
    area = area/2;
    return (area >= 0) ? true : false;
}
/*
*   Verifica se a aresta que AB está dentro do polígono.
*   Para isso, verifica se essa aresta está dentro do cone formado por A, A- e A+.
*   Achar A- e A+ é a nossa prioridade.
*/
Edge* inCone_dcel(Edge *edge)
{
    /*
    *   A aresta AB é encontrada usando a estrutura DCEL.
    *   A é a origem da edge, B é a origem de sua twin.
    */ 
    Point *ponto_inicial = edge->point;
    Point *ponto_final = edge->twin->point;

    /*
    *    Percorre a órbita de A
    *    A0 é aresta AA-
    *    A1 é a aresta AA+
    *    Sentido Anti Horário
    */ 
    Edge *vertex_A0 = ponto_inicial->edge->twin->next;
    Edge *vertex_A1 = vertex_A0->twin->next;

    #ifdef INCONE_DEBUG
        cout << "Incone Debug = ***\n";
        cout << "Vertex AO: " << vertex_A0->point->x << "," << vertex_A0->point->y << "\n";
        cout << "Vertex A1: " << vertex_A1->point->x << "," << vertex_A1->point->y << "\n";
    #endif
    /*
    *    Estrutura de do/while para achar as aretas A0 e A1 que queremos.
    *    While só encerra quando A0 se torna a aresta inicial de novo.
    */

    do
    {
        if( leftOn(ponto_inicial, vertex_A1->point, vertex_A0->point))
        {
            /*
            * Se LeftOn retornar verdadeiro, é porque A0 A A1 é um vértice convexo
            * Checamos agora usando Left se são os vértices que queremos
            */ 
        if( left(ponto_inicial, ponto_final, vertex_A0->point) &&
            left(ponto_final, ponto_inicial, vertex_A1->point))
            {
                /* 
                * Achamos nossas arestas E1 e E2 
                * Retornamos apenas E1, pois E2 já sabemos como acessar
                */
                break;
            }
        }
        else
        {
            /*
            * Se leftOn retornar falso, é porque A0 A A1 é um vértice reflexo
            * Checamos agora usando um "Right" se são os vértices que queremos
            */
            if(!(leftOn(ponto_inicial, ponto_final, vertex_A1->point) &&
                leftOn(ponto_final, ponto_inicial, vertex_A0->point)))
                {
                    /*
                    * Achamos nossas arestas E1 e E2
                    * Retornamos apenas E1, pois E2 já sabemos como acessar
                    */
                    break; 
                }
        }
        /*
        * Não achamos a aresta
        * Movemos as arestas A0 e A1 e checamos novamente.
        */
        vertex_A0 = vertex_A1;
        vertex_A1 = vertex_A1->twin->next;      
    }
    while(vertex_A1 != ponto_inicial->edge);

    return vertex_A0;
}
  
/* 
*   Conecta 2 pontos do plano.
*   Para isso, cria uma aresta entre esses dois pontos.
*   Arruma os ponteiros das arestas
*   Arruma a órbita dos pontos.
*/
void connect(Point *vertex_A, Point *vertex_B)
{
    // Cria uma aresta
    Edge *edge;
    edge = createEdge();

    // Associa os pontos a essa aresta.
    edge->point = vertex_A;
    edge->twin->point = vertex_B;

    // Verifica se o ponto A e B já tem uma aresta associada
    if(vertex_A->edge != NULL && vertex_B->edge != NULL)
    {
        /* 
        *   Acha aresta e1 e e2 (ver material de aula) para arrumar os ponteiros.
        *   Para isso, utiliza a função inCone_dcel
        */ 
        Edge *edge_1, *edge_2;
        edge_1 = inCone_dcel(edge);
        edge_2 = edge_1->twin->next;

        // Conecta as órbitas
        connectOrbit(edge_1, edge);
        connectOrbit(edge_2, edge->twin);
    }
    // Caso contrário, é a primeira aresta que o ponto recebe.
    else
    {
        if(vertex_A->edge == NULL)
        {
            // Associa ao ponto A a aresta criada.
            #ifdef CONNECT_DEBUG
                cout << "Points A: " << vertex_A;
                cout << " doesn't have any orbit.\n";
            #endif
            vertex_A->edge = edge;
        }

        if(vertex_B->edge == NULL)
        {
            // Associa ao ponto B a aresta criada.
            #ifdef CONNECT_DEBUG
                cout << "Points B: " << vertex_B;
                cout << " doesn't have any orbit.\n";
            #endif
            vertex_B->edge = edge->twin;
        }
    }
    
}

/*
*   Arruma a órbita de c,
*   Inserindo a nova aresta e corretamente
*/
void connectOrbit(Edge *edge_c, Edge *edge_e)
{
    /* 
    *   Nova aresta: edge_e
    *   Aresta que vamos mudar: edge_c
    *   Previous da nova aresta é agora o previous da aresta c
    *   Assim, quando percorrermos a face dessa aresta, não passamos direto,
    *   e "viramos" na aresta nova inserida 
    */
    edge_e->prev = edge_c->prev;
    /* 
    *   Agora que e tem o previous certo, vamos fazer essa aresta apontar 
    *   para e (seu next) 
    */ 
    edge_c->prev->next = edge_e;
    /* 
    *   Agora que a aresta anterior de c tem seus ponteiros certos (ela aponta)
    *   para e, e tem seu previous para ela.
    *   Vamos arrumar c.
    *   Previous de c tem que ser a aresta nova (twin) (afinal, a nova ta no outro sentido)
    */ 
    edge_c->prev = edge_e->twin;
    /* 
    *   Por fim, arrumamos a next do twin de e. 
    *   Por ser uma aresta nova, atualmente ela aponta para seu irmão
    *   Agora, ela ponta corretamente para sua next, c.
    */ 
   edge_e->twin->next = edge_c;
}

/*
*   Apaga a existência da aresta entre os pontos A e B.
*   A aresta vai continuar existindo, mas as órbitas de A e B não vão mais 
*   estar relacionadas com essa aresta
*   Será necessário desalocar esse vetores manualmente.
*/
void disconnect(Point *vertex_A, Point *vertex_B)
{   
    /* 
    *   Busca aresta com origem em A, cuja sua irmã gêmea tem origem em B
    *   Se sua irmã não tem a origem em B, pega sua próxima da órbita 
    */
   Edge *vertex_auxiliar;
   do
   {
       vertex_auxiliar = vertex_A->edge;
       if(vertex_auxiliar->twin->point == vertex_B)
       {
           break;
       } 
        vertex_auxiliar = vertex_auxiliar->twin->next;    
   } while ( vertex_auxiliar != vertex_A->edge);
   
    /*
    *   Uma vez com aresta encontrada, vamos encontrar e1 e e2.
    *   Aqui, elas já estão óbvias.
    *   e1 é a previous (da órbita).
    *   e2 é a next (da órbita).
    */

    Edge *e1, *e2; 
    e1 = vertex_auxiliar->next;
    e2 = vertex_auxiliar->twin->next;
    disconnectOrbit(e1, vertex_auxiliar);
    disconnectOrbit(e2, vertex_auxiliar->next);    
}

/*
*   Arruma a órbita de 1,
*   Apagando a aresta 2 e arrumando os ponteiros corretamente
*/
void disconnectOrbit(Edge *edge_1, Edge *edge_2)
{
    edge_1->prev = edge_2->twin->prev;
    edge_1->twin->next = edge_2;
    edge_2->twin->prev->next = edge_1;
    edge_2->prev = edge_1->twin;
}

/*
*   Printa os ponteiros no terminal para visualização.
*/

void printEdge(Edge *edge)
{
    cout << " * Edge * \n";
    cout << " Edge: " << edge << "\n";
    cout << " Point: " << edge->point->x << ", " << edge->point->y << "\n";
    cout << " Edge->next: " << edge->next << "\n";
    cout << " Edge->prev: " << edge->prev << "\n";
    cout << " * Edge Twin * \n";
    cout << " Twin: " << edge->twin << "\n";
    cout << " Point: " << edge->twin->point->x << ", " << edge->twin->point->y << "\n";
    cout << " Twin->next: " << edge->twin->next << "\n";
    cout << " Twin->prev: " << edge->twin->prev << "\n";
    cout << " Twin->twin: " << edge->twin->twin << "\n";
}

void percorreFace(Face *face)
{
    Edge *aresta;
    aresta = face->edge;
    int i = 0;
    do
    {
        // Aqui entra algum print / cout
        cout << "Aresta: " << i;
        cout << aresta->point->x << "," << aresta->point->y;
        cout << aresta->twin->point->x << "," << aresta->twin->point->y;
        cout << "\n";
        aresta = aresta->next;
        i++;
    } while (aresta != face->edge);  

}

void percorreOrbita(Point *ponto)
{
    Edge *aresta;
    aresta = ponto->edge;
    int i = 0;
    do
    {
        // Aqui entra algum print / cout
        cout << "Aresta: " << i;
        cout << aresta->point->x << "," << aresta->point->y;
        cout << aresta->twin->point->x << "," << aresta->twin->point->y;
        cout << "\n";
        aresta = aresta->prev->twin;
        i++;        
    } while (aresta != ponto->edge);
    
}

void splitFace()
{
    /* TODO: Implement */
    
}

void splitEdge()
{
    /* TODO: Implement */
}

/*
*   Limpa os ponteiros da aresta, desalocando a memória
*   Cuidado com arestas que apontam para ela!, pode dar merda
*/
void freeEdge(Edge *edge)
{
    free(edge);
}

void freePoint(Point *point)
{
    free(point);
}

