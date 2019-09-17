/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/

/* Estrutura DCEL */
typedef struct Edge
{
    /* Ponto de origem da aresta */
    struct Point ponto_origem;
    /* Ponteiro para a próxima aresta */
    struct Edge *next;
    /* Ponteiro para a aresta anterior*/    
    struct Edge *prev;
    /* Ponteiro para a aresta gêmea */    
    struct Edge *twin;
    /* Ponteiro para a face a sua esquerda */
    struct Face *left_face;
} Edge;

typedef struct Point
{
    /* Estrutura do ponto no espaço*/
    double x;
    double y;
    /* Aresta que tem como origem este ponto */
    struct Edge *aresta;    
} Point;

typedef struct Face
{
    /* Aresta que pertence a face */
    struct Edge *edge;
} Face;

Edge* createEdge();
/* TODO: Lista 4 */

void connect(Point *vertex_A, Point *vertex_B);
void connectOrbit(Edge *edge_1, Edge *edge_2);
void disconnect(Point *vertex_A, Point *vertex_B);
void disconnectOrbit(Edge *edge_1, Edge *edge_2);

/* TODO: Implement */
void insertEdge(Edge *edge, Point *origin, Point *destiny);
void printFaces(Face *face);
void printEdges(Edge *edge);
void printPoints(Edge *edge);
void vertexOrbit(Point *vertex);
void insertEdge(Point *vertex_A, Point *vertex_B);
void insertVertex(Edge *edge);

