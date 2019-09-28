
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

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

#define PRINT_POINTS
#define PRINT_FUNCTIONS_MESSAGES0

double randomNumber(int scale);
List* generatePoints(int number_of_points);
List* createList(void);
void freeList(List *lista);
List* insertList(List* lista, Point* elem);
void printPoints(List* points);
List* jarvisMarching(List* lista_de_pontos);
int listSize(List* list);
double orientedAngle(Point* Origem, Point* FirstPoint, Point* Second_Point);
double dotProduct(Point* u, Point* v);
bool leftOn(Point* A, Point* B, Point* C);
int main()
{
    int number_of_points;
    cout << "Digite o número de pontos: \n";
    cin >> number_of_points;

    srand(time(NULL));
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "Random seed created.\n";
    #endif
    List* lista_de_pontos = createList();
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "List created.\n";
    #endif
    lista_de_pontos = generatePoints(number_of_points);
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "Points created.\n";
    #endif
    #ifdef PRINT_POINTS
        printPoints(lista_de_pontos);
    #endif
    List* convexHull = createList();
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "Convex Hull list created.\n";
    #endif

    //    convexHull = jarvisMarching(lista_de_pontos);    
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "Jarvis March returned sucessfuly.\n";
    #endif
    if(convexHull != NULL)
    {
        printPoints(convexHull);
    }
    


    freeList(lista_de_pontos);
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "List memory desallocated correctly.\n";
    #endif
    freeList(convexHull);
    #ifdef PRINT_FUNCTIONS_MESSAGES
        cout << "Convex Hull list desallocated correctly.\n";
    #endif
    return 0;
}

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

double randomNumber(int scale)
{
    return rand() % scale;
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

void printPoints(List* points)
{
    List* auxiliar = points;
    int i = 0;
    while(auxiliar != NULL)
    {
       cout << "Ponto " << i << ": " << auxiliar->ponto->x << ", " << auxiliar->ponto->y << "\n";
       auxiliar = auxiliar->next;
       i++;
    }    
}

int listSize(List* list)
{
    int size_of_list = 0;
    List* auxiliar = list;
    while(auxiliar != NULL)
    {
        auxiliar = auxiliar->next;
        size_of_list++;
    }
    return size_of_list;
}

List* jarvisMarching(List* lista_de_pontos)
{
    int size_of_list = listSize(lista_de_pontos);
    if(size_of_list < 3)
    {
        #ifdef ERRORS
            cout << "Not enough points to perform Convex Hull.\n";
        #endif
        return NULL;
    }
    else
    {
        List* convexHull = createList();
        /*
        * First Step: found the leftmost point
        */
        Point* leftmost_point = lista_de_pontos->ponto;
        List* lista_auxiliar = lista_de_pontos;
        List* leftmost_point_node = lista_de_pontos;
        for(int i = 0; i < size_of_list; i++)
        {
            if(lista_auxiliar->ponto->x < leftmost_point->x)
            {
                leftmost_point = lista_auxiliar->ponto;
                leftmost_point_node = lista_auxiliar;
            }
            lista_auxiliar = lista_auxiliar->next;
        }  

        /*
        * Second step: move though all the points, starting by the leftmost point found
        * We stop when we get at this point again.
        */ 

        Point* ponto_auxiliar = leftmost_point;
        List* loop_list = lista_de_pontos;
        double minimum_angle = 0;
        double auxiliar_angle = 0;
        do
        {
            loop_list = lista_de_pontos;
            // Faz um loop com todos os pontos
            for(int i = 0; i < size_of_list; i++)
            {
                // Verifica se não é o ponto que estamos agora.
                if(loop_list->ponto != ponto_auxiliar)
                {
                    // Calcultar angulo orientado
                }
                loop_list = loop_list->next;
            }
            leftmost_point_node = ponto_auxiliar;
            convexHull = insertList(convexHull, ponto_auxiliar);
            // remover? setar alguma flag para não verificar esse ponto de novo

        } while (ponto_auxiliar != leftmost_point);
        

        List* response = createList();
        response = insertList(response, leftmost_point);
        return response;       
    }    
}

double orientedAngle(Point* Origem, Point* FirstPoint, Point* Second_Point)
{
    Point* vector_u, *vector_v;
    vector_u->x = FirstPoint->x - Origem->x;
    vector_u->y = FirstPoint->y - Origem->y;

    vector_v->x = Second_Point->x -Origem->x;
    vector_v->y = Second_Point->y -Origem->y;

    double OF = dotProduct(vector_u, vector_u);
    double OS = dotProduct(vector_v, vector_v);
    double FS = dotProduct(vector_u, vector_v);

    double theta = (double)acos(FS/(OF*OS));

    if(leftOn(Origem, FirstPoint, Second_Point))
    {
        return theta;
    }
    else
    {
        return (double) 360 - theta;
    }
    
}

double dotProduct(Point* u, Point* v)
{
    double result;
    result = u->x * v->x;
    result += u->y * v->y;
    return result;
}

bool leftOn(Point* A, Point* B, Point* C)
{
    double area;
    area = ((B->x - A->x) * (C->y - A->y)) - ((C->x - A->x) * (B->y - A->y) );
    area = area/2;
    return (area >= 0) ? true : false;    
}