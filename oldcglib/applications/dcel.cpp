#include "dcel.h"
#include <stdlib.h> // malloc

/*
typedef struct Edge
{
    /* Ponto de origem da aresta
    struct Point ponto_origem;
    /* Ponteiro para a próxima aresta
    struct Edge *next;
    /* Ponteiro para a aresta anterior   
    struct Edge *prev;
    /* Ponteiro para a aresta gêmea  
    struct Edge *twin;
    /* Ponteiro para a face a sua esquerda
    struct Face *left_face;
} Edge;
*/

/* Cria dinamicamente uma aresta
*  Aresta é isolada, sem pontos definidos
*  Next de e é sua twin. Prev de e é sua twin.
*  Ambas apontam para a mesma face, que é todo o resto do plano (null)
*/
Edge* createEdge()
{
    // Aloca os espaços
    Edge *new_edge = (Edge*) malloc (sizeof(Edge));
    Edge *second_edge = (Edge*) malloc (sizeof(Edge));
    
    // Associa os twins.
    new_edge->twin = second_edge;
    second_edge->twin = new_edge;

    // Associa os next e prev
    new_edge->next = new_edge->twin;
    new_edge->prev = new_edge->twin;

    second_edge->next = second_edge->twin;
    second_edge->prev = second_edge->twin;

    // Associa as faces
    new_edge->left_face = NULL;
    second_edge->left_face = NULL;

    return new_edge;

}

/* Essa função precisa ser repensada
*/
void printFaces(Face *face)
{
    Edge* aresta_aux = face->edge;
    do
    {
        printEdges(aresta_aux->next);
        aresta_aux = aresta_aux->next;
    }
    while(aresta_aux != face->edge);
}

/* TODO: Lista 4 */

void connect(Point *vertex_A, Point *vertex_B);
void connectOrbit(Edge *edge_1, Edge *edge_2);
void disconnect(Point *vertex_A, Point *vertex_B);
void disconnectOrbit(Edge *edge_1, Edge *edge_2);

/* TODO: Implement */
void printEdges(Edge *edge);
void printPoints(Edge *edge);
void vertexOrbit(Point *vertex);
void insertEdge(Point *vertex_A, Point *vertex_B);
void insertVertex(Edge *edge);