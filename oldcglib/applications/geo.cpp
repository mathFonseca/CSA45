/* Autores das bibliotecas:
* Matheus Fonseca Alexandre de Oliveira
* <matheus.2016@alunos.utfpr.edu.br>
*/

/* Libraries */
#include "geo.h"
#include <math.h>

/* Defines */
#define PI 3.1415

/* Additional <personal> comments: 
* Ao acessar uma estrutura de dados por ponteiro, 
* usamos -> ao invés de ponto.
* Exemplo:
* Acesso por ponteiro normal: ponteiro.valor
* Acesso por ponteiro (struct): ponteiro->valor
*/

/* Funções */

point_2d c_Point(double x, double y)
{
    point_2d ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

point_2d c_Vector(point_2d A, point_2d B)
{
    // Relembrando: um vetor u AB é formado por B-A
    point_2d vector;
    vector.x = B.x - A.x;
    vector.y = B.y - A.y;
    return vector;
}

// Soma os vetores u + v
point_2d sumVector(point_2d u, point_2d v)
{
    point_2d result;
    result.x = u.x + v.x;
    result.y = u.y + v.y;
    return result;
}

// Multiplicação de vetores u*v
double prodInterno(point_2d u, point_2d v)
{
    double result;
    result = u.x * v.x;
    result += u.y * v.y;
    return result;
}

/* Produto vetorial de u x v
*  Resultado é originalmente no eixo Z.
*  A função está retornando atualmente no eixo x 
*/
point_2d prodVetorial(point_2d u, point_2d v)
{
    point_2d result;
    result.x = (u.x * v.y) - (v.x * u.y);
    return result;
}

// Retorna area unsigned do triangulo formado pelos pontos ABC
double u_areaTriangle(point_2d A, point_2d B, point_2d C)
{
    // Utiliza o módulo do produto vetorial
    point_2d result;
    point_2d u;
    point_2d v;
    double valor;
    u = c_Vector(A, C); // C - A
    v = c_Vector(A, B); // B - A
    result = prodVetorial(u, v);
    valor = result.x;
    return (valor>0) ? valor/2 : (-1)*(valor/2);
}

// Retorna area signed do triangulo formado pelos pontos ABC
double s_areaTriangle(point_2d A, point_2d B, point_2d C)
{
    // utiliza o produto vetorial
    point_2d result;
    point_2d u;
    point_2d v;
    double valor;
    u = c_Vector(A, C); // C - A
    v = c_Vector(A, B); // B - A
    result = prodVetorial(u, v);
    valor = result.x;
    return valor;
}

// Retorna true se C está a left de AB. False se contrário
bool left(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area > 0) ? true : false;
}

// Retorna true se C está a left/em cima de AB. False se contrário
bool leftOn(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area >= 0) ? true : false;    
}

// Retorna true se C está em cima de AB. False se contrário
bool collinear(point_2d A, point_2d B, point_2d C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area == 0) ? true : false;        
}

// Retorna true se C está a em cima e entre de AB. False se contrário
bool between(point_2d A, point_2d B, point_2d C)
{
    // Primeiro checa se C é collinear em relação a reta AB
    if(collinear(A, B, C))
    {
        // Se a reta AB não for vertical, então verifica a coordenada x.
        if(A.x != B.x)
        {
            return ( ( (A.x <= C.x) && (C.x <= B.x) ) ||
                     ( (A.x >= C.x) && (C.x >= B.x) ) );
        }
        // Se a reta AB for vertical, então verifica a coordenada y.
        else
        {
            return ( ( (A.y <= C.y) && (C.y <= B.y) ) ||
                     ( (A.y >= C.y) && (C.y >= B.y) ) );
        }
    }
    else
    {
        return false;
    }    
}

double calculateAngle(point_2d A, point_2d B, point_2d C)
{
        // Vetores: AB e AC
    point_2d u, v;
    u.x = B.x - A.x;
    u.y = B.y = A.y;

    v.x = C.x - A.x;
    v.y = C.y - A.y;

    double modulo_AB = prodInterno(u, u);
    double modulo_AC = prodInterno(v, v);

    double aux = prodInterno(u,v);

    return (double)acos(aux / (modulo_AB * modulo_AC));
}

bool checkUpward(point_2d A, point_2d B)
{
    if(A.x > B.x)
    {
        if(A.y <= B.y)
        {
            return true;
        }

         return false;
    }
    else
    {
        return false;
    }
}

/*  Classifica os vértices do polígono entre 5 categorias.
*   Regular, Split, Merge, Start, End
*/
void classifyVertexMonotonePolygon(polygon_2d * polygon)
{
    // Pontos usados, onde o vértice Pi é A, Pi-1 é B, Pi+1 é C.
    point_2d A;
    point_2d B;
    point_2d C;

    polygon_2d * polygon_aux = polygon->prev;

    while(polygon_aux != polygon)
    {
        A = polygon_aux->info;
        B = polygon_aux->prev->info;
        C = polygon_aux->next->info;

        if(!checkUpward(B, A) && !checkUpward(C, A) &&
             calculateAngle(A, B, C) < PI)
        {
            polygon->pointType = start;
        }
        else if(!checkUpward(B, A) && !checkUpward(C, A) &&
             calculateAngle(A, B, C) > PI)
        {
            polygon->pointType = split;
        }
        else if(checkUpward(B, A) && checkUpward(C, A) &&
             calculateAngle(A, B, C) < PI) 
        {
            polygon->pointType = end;
        }
        else if(checkUpward(B, A) && checkUpward(C, A) &&
             calculateAngle(A, B, C) > PI)
        {
            polygon->pointType = merge;
        }
        else
        {
            polygon->pointType = regular;
        }
        
        polygon_aux = polygon_aux->next;
    }
}

// ==================================================================
/* List Functions */
List* createList(void)
{
    return NULL;
}

void freeList(List *lista)
{
    while(lista != NULL)
    {
        List *aux = lista->next;
        free (lista);
        lista = aux;
    }
}

List* insertList(List* lista, Point* elem)
{
    List* novo =(List*)malloc(sizeof(List));
    novo->ponto = elem;
    novo->next = lista; /*A lista anterior é anexada a novo.*/
    novo->prev = NULL;
    /* Verifica se lista não está vazia. */
    if (lista != NULL)
        lista->prev = novo; /*A ponteiro anterior da lista agora é novo.*/
    return novo;    
}

List* removeList(List *lista, Point* elem)
{
  List *aux = lookList (lista, elem);
  if (aux != NULL) {
    if (aux->prev == NULL) {
      /*Elemento na cabeça da lista!*/
      lista = aux->next;
      if (lista != NULL)
        lista->prev = NULL;
    } 
    else if (aux->next == NULL) {
      /*Elemento na cauda da lista!*/
      aux->prev->next = NULL;
    }
    else {
      /*Elemento no meio da lista!*/
      aux->prev->next = aux->next;
      aux->next->prev = aux->prev;
    }
    free(aux);
    return lista;
  }
  else {
    return NULL; 
  }    
}

List* lookList(List* lista, Point* elem)
{
  List *v; /*var. para percorrer a lista*/
  for (v = lista; v != NULL; v = v->next) 
  {
    if (v->ponto->x == elem->x && v->ponto->y == elem->y) 
    // v->ponto == elem 
    {
       return v;
    }
  }
  return NULL;    
}

/* TODO: Implement */
List* lastList(List* lista);