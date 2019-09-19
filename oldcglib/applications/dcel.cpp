/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/


#include "dcel.h"
#include "geo.h"
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
    Edge *edge, *edge_1, *edge_2;
    edge = createEdge();
    edge->ponto_origem = vertex_A;
    edge->twin->ponto_origem = vertex_B;

    // Acha aresta e1 e e2
    // Aresta e1 (pertencente a B)
    Edge *aux = vertex_B->aresta;
    Edge *aux_next = aux->twin->next;
    do
    {
        /* 
        * Teste que eu pensei
        * "edge aux" tem que estar a esquerda da aresta que vou inserir.
        * "edge aux_net" tem que estar a direita da aresta que vou inserir.
        */ 

        /* Teste de left */
        if(left(edge->ponto_origem,edge->twin->ponto_origem,aux->twin->ponto_origem))
        {
            /* Teste de Right*/
            if(!left(edge->ponto_origem, edge->twin->ponto_origem,aux_next->twin->ponto_origem))
            {
                // Se deu certo, achamos nossa edge. (aux)
                break;
            }
        }
        // Move as arestas
        aux = vertex_B->aresta->twin->next;
        aux_next = aux->twin->next;
    } while (aux != vertex_B->aresta);
    

    // Conecta as órbitas
    connectOrbit(edge_1, edge);
    connectOrbit(edge_2, edge->twin);
}
void connectOrbit(Edge *edge_c, Edge *edge_e)
{
    /* Nova aresta: edge_e
    * Aresta que vamos mudar: edge_c
    * Previous da nova aresta é agora o previous da aresta c
    * Assim, quando percorrermos a face dessa aresta, não passamos direto,
    * e "viramos" na aresta nova inserida 
    */
    edge_e->prev = edge_c->prev;
    /* Agora que e tem o previous certo, vamos fazer essa aresta apontar 
    * para e (seu next) 
    */ 
    edge_c->prev->next = edge_e;
    /* Agora que a aresta anterior de c tem seus ponteiros certos (ela aponta)
    * para e, e tem seu previous para ela.
    * Vamos arrumar c.
    * Previous de c tem que ser a aresta nova (twin) (afinal, a nova ta no outro sentido)
    */ 
    edge_c->prev = edge_e->twin;
    /* Por fim, arrumamos a next do twin de e. 
    * Por ser uma aresta nova, atualmente ela aponta para seu irmão
    * Agora, ela ponta corretamente para sua next, c.
    */ 
   edge_e->twin->next = edge_c;
}
void disconnect(Point *vertex_A, Point *vertex_B)
{   
    /* 
    * Busca aresta com origem em A, cuja sua irmã gêmea tem origem em B
    * Se sua irmã não tem a origem em B, pega sua próxima da órbita 
    */
   Edge *v;
   do
   {
       v = vertex_A->aresta;
       if(v->twin->ponto_origem == vertex_B)
       {
           break;
       } 
        v = v->twin->next;    
   } while ( v != vertex_A->aresta);
   
    /*
    * Uma vez com aresta encontrada, vamos encontrar e1 e e2.
    * Aqui, elas já estão óbvias.
    * e1 é a previous (da órbita).
    * e2 é a next (da órbita).
    */

    Edge *e1, *e2; 
    e1 = v->next;
    e2 = v->twin->next;
    disconnectOrbit(e1, v);
    disconnectOrbit(e2,v->next);    
}
void disconnectOrbit(Edge *edge_1, Edge *edge_2)
{
    edge_1->prev = edge_2->twin->prev;
    edge_1->twin->next = edge_2;
    edge_2->twin->prev->next = edge_1;
    edge_2->prev = edge_1->twin;
}

/* TODO: Implement */

void printEdges(Edge *edge);
void printPoints(Edge *edge);
void vertexOrbit(Point *vertex);
void insertEdge(Point *vertex_A, Point *vertex_B);
void insertVertex(Edge *edge);

bool left(Point *A, Point *B, Point *C)
{
    double area;
    area = ((B->x - A->x) * (C->y - A->y)) - ((C->x - A->x) * (B->y - A->y) );
    area = area/2;
    return (area > 0) ? true : false;
}