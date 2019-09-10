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
    point_2d info;
    polygon_2d *next;
    polygon_2d *prev;
    int type_of_angle; 
    enum point_category pointType;
} polygon2d;

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

// ==================================================================
/* OLD Functions */
/*
// Insere ponto A no polígono.
void insertPolygon(point_2d Point, polygon_2d Polygon);

// write comment
double angulo_interno(point_2d * array_1, point_2d * array_2);

// cria o vetor AB
point_2d vector(point_2d A, point_2d B);

// cria o ponto x,y
point_2d point(double x, double y);

// Soma os vetores coordenada por coordenada
point_2d soma_vetores(point_2d vetor_1, point_2d vetor_2);

// Calcula o produto interno dos vetores.
double produto_interno(point_2d vetor_1, point_2d vetor_2);

// Calcula o produto vetorial dos vetores. 
// Vetor resposta com coordenada em z.

point_2d produto_vetorial(point_2d vetor_1, point_2d vetor_2);

// Calcula a área do triangulo formado pelos pontos A, B e C
double a_triangulo_unsigned(point_2d A, point_2d B, point_2d C);

// Calcula a área do triangulo com sinal, formado pelos pontos A, B e C
double a_triangulo_signed(point_2d A, point_2d B, point_2d C);


// Retorna true caso C esteja a esquerda ou alinhado a reta AB. 
// False caso contrário
//
bool leftOn(point_2d A, point_2d B, point_2d C);

// Retorna true caso C esteja dentro da reta AB. False caso contrário
bool collinear(point_2d A, point_2d B, point_2d C);

// Retorna true quando não tem intersecção própria. False caso contrário
bool intersectPropria(point_2d A, point_2d B, point_2d C, point_2d D);

// Retorna true quando C está dentro do segmento AB
bool between(point_2d A, point_2d B, point_2d C);

// Retorna true quando a reta AB intersecta a reta CD
bool intersect(point_2d A, point_2d B, point_2d C, point_2d D);

// Classifica os vertices do poligono. 1 se concavo, 0 se convexo
void classifica_vertice(polygon_2d polygon);

// Calcula o angulo entre os pontos ABC, sendo B o centro.
double computa_angulo(point_2d A, point_2d B, point_2d C);

// Classifica os pontos do polígono
void classifyPoints(polygon_2d polygon);

// Retorna 1 se A está acima de B. 0 caso contrário
bool checkUpwardPoint(point_2d A, point_2d B);
*/