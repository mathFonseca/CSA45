
typedef struct point_2d
{
    double x;
    double y;

} point2d;

typedef struct poligono
{

} poligono2d;

/* Adicionais */
double angulo_interno(point_2d * array_1, point_2d * array_2);
point_2d vector(point_2d ponto_1, point_2d ponto_2);
point_2d point(double x, double y);


/* Lista 1 */
point_2d soma_vetores(point_2d vetor_1, point_2d vetor_2);
double produto_interno(point_2d vetor_1, point_2d vetor_2);
point_2d produto_vetorial(point_2d vetor_1, point_2d vetor_2);
double area_triangulo_unsigned(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);
double area_triangulo_signed(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);

/* Lista 2 */

// 1 se a esquerda. 0 caso contrário
bool left(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);

// 1 se a esquerda ou em cima da reta. 0 caso contrário
bool leftOn(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);

// 1 somente se em cima da reta. 0 caso contrário.
bool collinear(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);

bool intersection(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3, point_2d ponto_4);
bool between(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);