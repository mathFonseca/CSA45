/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/
enum point_category{start, split, end, merge, regular};

typedef struct point_2d
{
    double x;
    double y;

} point2d;

typedef struct polygon_2d
{
    /*
    *   info = informações do vértice (x,y)
    *   next = aponta para o próximo vértice
    *   prev = aponta para o vértice anterior
    *   type_of_angle = 0 para convexo(<= 180), 1 para concavo (>180)
    *   pointType = classificação do angulo perante as 4 configurações
    *   possíveis (ref: DE BERG).
    */ 
    struct point_2d info;
    struct polygon_2d *next;
    struct polygon_2d *prev;
    int type_of_angle; 
    enum point_category pointType;
} polygon2d;

typedef struct Point
{
    /* Estrutura do ponto no espaço*/
    double x;
    double y;
    bool convex_hull_flag;  
} Point;

typedef struct node
{
   struct Point* ponto;
   struct node* next;
   struct node* prev;
} List;


// ==================================================================
/* List Functions */
List* createList();
void freeList(List *lista);
List* insertList(List* lista, Point elem);
List* removeList(List *lista, Point elem);
List* lookList(List* lista, Point elem);
List* lastList(List* lista);
// ==================================================================
/* Funções */

/* Verified Functions 10/09 */

// ==================================================================
/* Point Funtions */

// Cria um ponto com coordenadas x e y
point_2d c_Point(double x, double y);

/* Cria um vetor u
* Tal que B - A
*/
point_2d c_Vector(point_2d A, point_2d B);

// ==================================================================
/* Polygon Functions */

// Soma os vetores u + v
point_2d sumVector(point_2d u, point_2d v);

// Multiplicação de vetores u*v
double prodInterno(point_2d u, point_2d v);

/* Produto vetorial de u x v
*  Resultado é originalmente no eixo Z.
*  A função está retornando atualmente no eixo x 
*/
point_2d prodVetorial(point_2d u, point_2d v);

// Retorna area unsigned do triangulo formado pelos pontos ABC
double u_areaTriangle(point_2d A, point_2d B, point_2d C);

// Retorna area signed do triangulo formado pelos pontos ABC
double s_areaTriangle(point_2d A, point_2d B, point_2d C);

// Retorna true se C está a left de AB. False se contrário
bool left(point_2d A, point_2d B, point_2d C);

// Retorna true se C está a left/em cima de AB. False se contrário
bool leftOn(point_2d A, point_2d B, point_2d C);

// Retorna true se C está em cima de AB. False se contrário
bool collinear(point_2d A, point_2d B, point_2d C);

// Retorna true se C está a em cima e entre de AB. False se contrário
bool between(point_2d A, point_2d B, point_2d C);

/*  Classifica os vértices do polígono entre 5 categorias.
*   Regular, Split, Merge, Start, End
*/
void classifyVertex(polygon_2d Polygon);
double calculateAngle(point_2d A, point_2d B, point_2d C);
void windingNumber();
bool checkUpward(point_2d A, point_2d B);
void classifyVertexMonotonePolygon(polygon_2d * polygon);


// TODO: Implement
void intersecPropria();
void intersec();
void intersecPolygon();
