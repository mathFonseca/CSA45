
// Bibliotecas Utilizadas
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;

// Defines 
#define DEBUG
#define POINTER_DEBUG
#define FUNCTIONS_DEBUG

// Estruturas Utilizadas
typedef struct node
{
   struct Point* ponto;
   struct node* next;
   struct node* prev;
} List;

typedef struct Point
{
    /* Estrutura do ponto no espaço*/
    double x;
    double y;
    bool convex_hull_flag;  
} Point;

// Funções Utilizadas
List* createList(void);
List* generatePoints(int number_of_points);
void printPoints(List *vetor_pontos, int number_of_points);
void freeList(List *lista);
List* removeList(List *lista, Point* elem);
List* lookList(List* lista, Point* elem);
List* insertList(List* lista, Point* elem);
double randomNumber(int scale);
List* giftWrapping(List* points);

int main()
{
    int number_of_points;
    srand(time(NULL));
    /* Requisita a quantidade de pontos a serem criados*/
    cout << "Digite o número de pontos a serem criados: \n";
    cin >> number_of_points;

    /* Gera n pontos aleatórios */
    List *lista_de_pontos = createList();
    #ifdef DEBUG
        cout << "Lista criada com sucesso.\n";
    #endif
    #ifdef FUNCTIONS_DEBUG
        #ifdef POINTER_DEBUG
            cout << "First pointer: "<< lista_de_pontos;
        #endif
    #endif    
    lista_de_pontos = generatePoints(number_of_points);
    #ifdef FUNCTIONS_DEBUG
        #ifdef POINTER_DEBUG
            cout << lista_de_pontos << "\n";
        #endif
    #endif
    /* Printa os pontos no terminal */
    printPoints(lista_de_pontos, number_of_points);

    cout << "print points finished";
    /* Computa o Fecho Convexo */
    List *convexHull = createList();
    cout << "convex hull list created";
    convexHull = giftWrapping(lista_de_pontos);
    /* Printa pontos do Fecho Convexo */

    /* Libera lista criada */
    freeList(lista_de_pontos);
    freeList(convexHull);
    #ifdef DEBUG
        cout << "Lista liberada com sucesso \n";
    #endif
    return 0;
}

// ====================================================================================
/*
* Funções Extras
*/

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
    #ifdef FUNCTIONS_DEBUG
        #ifdef POINTER_DEBUG
            cout << "New pointer created: " << novo << "\n";
            cout << "List header: " << lista << "\n";
        #endif
    #endif
    novo->ponto = (Point*)malloc(sizeof(Point));
    novo->ponto->x = elem->x;
    novo->ponto->y = elem->y;
    /*
    novo->ponto->x = elem->x;
    novo->ponto->y = elem->y;*/
    novo->next = lista; /*A lista anterior é anexada a novo.*/
    novo->prev = NULL;
    #ifdef FUNCTIONS_DEBUG
        #ifdef POINTER_DEBUG
            cout << "Next pointer is now defined as: " << novo->next << "\n";
        #endif
    #endif
    /* Verifica se lista não está vazia. */
    if (lista != NULL)
    {
        lista->prev = novo; /*A ponteiro anterior da lista agora é novo.*/
        #ifdef FUNCTIONS_DEBUG
            #ifdef POINTER_DEBUG
                cout << "Prev pointer is now defined as: " << novo->prev << "\n";
            #endif
        #endif
    }
    #ifdef FUNCTIONS_DEBUG
        #ifdef POINTER_DEBUG
            cout << "New head of the list is now: " << novo << "\n";
        #endif
    #endif
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

/* Cria estaticamente a estrutura ponto
* Atualiza os parametros recebidos
* e retorna a estutura
*/
Point createPoint(double x, double y, bool flag)
{
    Point ponto;
    ponto.x = x;
    ponto.y = y;
    ponto.convex_hull_flag = flag;
    return ponto;
}

/* Gera um número aleatório. 
* Scale pode ser usada para determinar o tamanho limite do número gerado
*/
double randomNumber(int scale)
{
    double number;
    number = rand() % scale;
    return number;
}

List* generatePoints(int number_of_points)
{
    List *lista_de_pontos = createList();
    Point *ponto_gerado = (Point*)malloc(sizeof(Point));
    
    /* Gera valores de x e y para cada ponto, usando a função randomNumber
    * A função recebe 513 como parametro, assim, se for imprimir no OpenGL,
    * os pontos sempre caem dentro da tela.
    */ 
   
    for(int i=0; i < number_of_points; i++)
    {
        ponto_gerado->x = randomNumber(500);
        ponto_gerado->y = randomNumber(500);
        #ifdef FUNCTIONS_DEBUG
            #ifdef POINTER_DEBUG
                cout << "\n\n\n";
                cout << "List header before insert of new point.\n";
                cout << lista_de_pontos << "\n";
            #endif
        #endif
        lista_de_pontos = insertList(lista_de_pontos, ponto_gerado);
        #ifdef FUNCTIONS_DEBUG
            #ifdef POINTER_DEBUG
                cout << "\n\n\n";
                cout << "List header after insert of new point.\n";
                cout << lista_de_pontos << "\n";
            #endif        
            #ifdef DEBUG
                cout << "\n";
                cout << "Ponto inserido: " << lista_de_pontos->ponto->x << ", " << lista_de_pontos->ponto->y << "\n";
            #endif  
            #ifdef POINTER_DEBUG
                cout << "\n\n\n";
                cout << "Actual Header: " << lista_de_pontos << "\n";
                cout << "Next pointer: " << lista_de_pontos->next << "\n";
                cout << "Prev pointer: " << lista_de_pontos->prev << "\n";
            #endif    
        #endif
    }

    /* Retorna o vetor criado */
    return lista_de_pontos;
}
/* Essa função não precisa receber necessariamente o número de pontos
*/
void printPoints(List *vetor_pontos, int number_of_points)
{
    #ifdef FUNCTIONS_DEBUG
        cout << "\n\n";
        cout << "==========\n";
        cout << "printPoints iniciated.";
        cout << "\n";
    #endif
    List* auxiliar_leitura;
    int number_point = 0;
    cout << "entrando no while\n";

    auxiliar_leitura = vetor_pontos->next;
    while(auxiliar_leitura != vetor_pontos)
    {
        cout << "ponto: " << auxiliar_leitura->ponto->x << ", " << auxiliar_leitura->ponto->y << "\n";
        auxiliar_leitura = auxiliar_leitura->next;
    }


    /*
    for(auxiliar_leitura = vetor_pontos; number_point < 1; auxiliar_leitura = auxiliar_leitura->next)
    {
        #ifdef FUNCTIONS_DEBUG
            #ifdef POINTER_DEBUG
                cout << vetor_pontos << "\n";
                cout << auxiliar_leitura << "\n";
                cout << "Actual Header: " << auxiliar_leitura << "\n";
                cout << "Actual Header point: " << auxiliar_leitura->ponto->x << ", " << auxiliar_leitura->ponto->y << "\n";
                cout << "Next point: " << auxiliar_leitura->next << "\n";
            #endif
        #endif
        cout << "Ponto " << number_point <<": " << auxiliar_leitura->ponto->x << ", " << auxiliar_leitura->ponto->y << "\n";
        number_point++;
        cout << number_point << "\n";
    }  */
    cout << "print points finished";
}

bool left(Point A, Point B, Point C)
{
    double area;
    area = ((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y) );
    area = area/2;
    return (area > 0) ? true : false;    
}

double prodInterno(Point u, Point v)
{
    double result;
    result = u.x * v.x;
    result += u.y * v.y;
    return result;
}


double calculateAngle(Point A, Point B, Point C)
{
        // Vetores: AB e AC
    Point u, v;
    u.x = B.x - A.x;
    u.y = B.y = A.y;

    v.x = C.x - A.x;
    v.y = C.y - A.y;

    double modulo_AB = prodInterno(u, u);
    double modulo_AC = prodInterno(v, v);

    double aux = prodInterno(u,v);

    return (double)acos(aux / (modulo_AB * modulo_AC));
}

double orientedAngle(Point A, Point O, Point B)
{
    /* 
    * Vector u = OA
    * Vector v = OB
    * Angle: u -> v
    */

   if(left(O, A, B))
   {
       /* Se B estiver a esquerda da reta OA, então só precisamos do angulo */
        return calculateAngle(O, A, B);
   }
   else
   {
       /* Se B estiver a direita da reta OA, então precisamos do complemento */
        return (360 - calculateAngle(O, A, B));
   } 
}

List* giftWrapping(List* points)
{
    cout << "giftwrapping started";
    List *convexHull = createList();
    List *auxiliar_leitura = createList();
    /*
    * First: find the leftmost point of the list
    * We start using the second item of the list, and the we run trough the entire list to find if has another point more to the left than this.
    */
    cout << points->next;
    //auxiliar_leitura = points->next;

    double leftmost_point_x_axis = (auxiliar_leitura->ponto->x);
    cout << leftmost_point_x_axis;
    Point* leftmost_point = auxiliar_leitura->ponto;
    cout << leftmost_point;
    while(auxiliar_leitura != points)
    {
        if(auxiliar_leitura->ponto->x < leftmost_point_x_axis)
        {
            leftmost_point_x_axis = auxiliar_leitura->ponto->x;
            leftmost_point = auxiliar_leitura->ponto;
        }
        auxiliar_leitura = auxiliar_leitura->next;
    }
    #ifdef DEBUG
        cout << "Leftmost point found: " << leftmost_point->x << ", " << leftmost_point->y <<"\n" ;
    #endif
    return points;    
}


// /*
//     /*
//     * Create a List to insert the Points for the Convex Hull
//     */
//     List* convexHull = createList();

//     /* 
//     * Find the furthest point to the right, by choosing the
//     * point with the higher x coordinate.
//     */

//     // First we start with the head of the list being the point that we want
//     double highest_x = set->ponto->x;
//     List* aux = set;

//     // The we loop till we see all the points, and saving what are these value in highest_x variable, and the point itself in aux
//     for(int i = 0; i < n_points; i++)
//     {
//         // If we find any point with a higher x coordiante, change the point we have  
//         if(aux->ponto->x > highest_x)
//         {
//             highest_x = aux->ponto->x;
//             aux = aux->next;
//         }
//     }

//     // At the end, we sabe this point in rightest_point variable.  
//     Point rightest_point = aux->ponto;

//     // This point is also one point of our Convex Hull, so we save him in the set
//     convexHull = insertList(convexHull, rightest_point);

//     /*
//     * Loop through all the points to find the point that has the lowest oriented angle between itself and the rightest_point
//     * This loop occours of every point of the Convex Hull, or in others words, until the last edge connects back to the rightest_point
//     */
    
//     while( aux->ponto->x != rightest_point.x && aux->ponto->y != rightest_point.y )
//     {
//         Point new_point;
//         double lowest_angle = 0;
//         for(int i = 0; i < n_points; i++)
//         {
//             /* TODO 
//             * calculate Oriented Angle between aux and all the others points
//             * save the point with the lowest oriented angle
//             */ 
//             if(value < lowest_angle)
//             {
//                 lowest_angle = value;
//                 new_point = that point;
//             }
//         }

//         convexHull = insertList(convexHull, aux);
//         aux = new_point;
//     }


    // aux = set[0];
    // int i = 0;
    // while( (lowest_point.x != aux.x) && (lowest_point.y != aux.y) )
    // {
    //     while(i != n_points)
    //     {
    //         // if(i != j) ???
    //         // orientedAngle(?, ?, ?);
    //     }
    // }


    // Point rightest;

    // // Do for all the points, find the lowest angle possible
    // double lowest_angle = 360;
    // double actual_angle;
    // for(int i = 0; i < n_points; i++)
    // {
    //     actual_angle = orientedAngle();
    //     if(actual_angle < lowest_angle)
    //     {
    //         // Substitute the lowest angle found
    //     }
    // }
    