//------------------------------------------------------------------------------
// Biblioteca criada para comportar diversas estruturas de dados
// Autor: Matheus Fonseca Alexandre de Oliveira

// Estrutura de ponto 2D
typedef struct ponto
{
    double x;
    double y;
} Point;


// Estrutura de lista duplamente encadeada para pontos
typedef struct node
{
    struct ponto *point;    
    struct node *next_node;
    struct node *prev_node;
} points_List;

Point* createPoint(double x, double y);
points_List* createList();
points_List* append(Point* received_point, points_List* list);
points_List* remove(Point* received_point, points_List* list);
void printList(points_List* list);
void freeList(points_List* list);