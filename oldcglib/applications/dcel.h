/* Autor da biblioteca:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/

/* Estrutura DCEL */
typedef struct Edge
{
    /* Ponto de origem da aresta */
    struct Point *ponto_origem;
    /* Ponteiro para a próxima aresta */
    struct Edge *next;
    /* Ponteiro para a aresta anterior*/    
    struct Edge *prev;
    /* Ponteiro para a aresta gêmea */    
    struct Edge *twin;
    /* Ponteiro para a face a sua esquerda */
    struct Face *left_face;
} Edge;

/* Estrutura do ponto no espaço 2D*/
typedef struct Point
{
    /* Valor x no espaço */
    double x;
    /* Valor y no espaço */
    double y;
    /* Aresta que tem como origem este ponto */
    struct Edge *aresta;    
} Point;

/* Estrutura da face no espaço 2D */
typedef struct Face
{
    /* Aresta que pertence a face */
    struct Edge *edge;
} Face;

Edge* createEdge(Point *ponto_origem, Point *ponto_destino);
Point* createPoint(double x, double y);
bool left(Point *A, Point *B, Point *C);
bool leftOn(Point *A, Point *B, Point *C);
Edge* inCone_dcel(Edge *edge);
void connect(Point *vertex_A, Point *vertex_B);
void connectOrbit(Edge *edge_1, Edge *edge_2);
void disconnect(Point *vertex_A, Point *vertex_B);
void disconnectOrbit(Edge *edge_1, Edge *edge_2);
void printEdge(Edge *edge);
void freeEdge(Edge *edge);