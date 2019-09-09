
#define MAXPOINTS 1000

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
    */ 
    point_2d info;
    polygon_2d *next;
    polygon_2d *prev;
    int type_of_angle; 
} polygon2d;


/* Funções */

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

// Calcula o produto vetorial dos vetores. Vetor resposta com coordenada em z.
point_2d produto_vetorial(point_2d vetor_1, point_2d vetor_2);

// Calcula a área do triangulo formado pelos pontos A, B e C
double area_triangulo_unsigned(point_2d A, point_2d B, point_2d C);

// Calcula a área do triangulo com sinal, formado pelos pontos A, B e C
double area_triangulo_signed(point_2d A, point_2d B, point_2d C);

// Retorna true caso C esteja a esquerda da reta AB. False caso contrário
bool left(point_2d A, point_2d B, point_2d C);

// Retorna true caso C esteja a esquerda ou alinhado a reta AB. False caso contrário
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