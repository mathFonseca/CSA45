/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/


#include "dcel.h"
#include <stdlib.h> // malloc

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

    // Associa os pontos
    new_edge->ponto_origem = NULL;
    second_edge->ponto_origem = NULL;

    return new_edge;

}

void insertEdge(Edge *edge, Point *origin, Point *destiny)
{
    // Associa o ponto a origem
    edge->ponto_origem = origin;

    // Associa o ponto de destino
    edge->twin->ponto_origem = destiny;

    // Achar aresta e1 e e2

    // Arruma os ponteiros associados a esse ponto
    edge->prev = e1;
    edge->next = e2;

    edge->twin->prev = e2->twin;
    edge->twin->next = e1->twin;
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

void connect(Point *vertex_A, Point *vertex_B)
{
    // Cria uma aresta que inicia em A e termina em B.
    Edge *edge;
    edge = createEdge();
    edge->ponto_origem = vertex_A;
    edge->twin->ponto_origem = vertex_B;

    // Acha aresta e1 e e2

    // Conecta as órbitas
    connectOrbit(edge_1, edge);
    connectOrbit(edge_2, edge->twin);
}
void connectOrbit(Edge *edge_1, Edge *edge_2)
{
    edge_2->prev = edge_1->prev;

    /*
    *
    * 
    * 
    */

    /*
    edge_1->twin->prev = edge_2->prev;
    edge_2->prev->next = edge_1->twin;
    edge_2->prev = edge_1;
    edge_1->next = edge_2;*/
}
void disconnect(Point *vertex_A, Point *vertex_B)
{
    // Encontra aresta com ponto inicial em A e final em B
    // Em outras palavras, busca todas as arestas da órbita de A.
    Edge *edge = vertex_A->aresta;
    bool foundEdge = false;
    do
    {
        // Pega a próxima aresta da órbita de A.
        if(edge->ponto_origem == vertex_A && edge->twin->ponto_origem == vertex_B)
            foundEdge = true;
    }
    while(/* Enquanto tiver vértices na órbita*/ || foundEdge == true);

    // Verifica estado da flag
    if(foundEdge)
    {
        // Acha aresta e1 e e2

        // Desconecta das órbitas
        disconnectOrbit(edge_1, edge);
        disconnectOrbit(edge_2, edge->twin);
    }
    
}
void disconnectOrbit(Edge *edge_1, Edge *edge_2)
{
    // find out
}

/* TODO: Implement */

void printEdges(Edge *edge);
void printPoints(Edge *edge);
void vertexOrbit(Point *vertex);
void insertEdge(Point *vertex_A, Point *vertex_B);
void insertVertex(Edge *edge);