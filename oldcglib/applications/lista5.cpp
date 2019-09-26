
#include <iostream>
#include <ctime>
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


double randomNumber(int scale);
List* generatePoints(int number_of_points);
List* createList(void);
void freeList(List *lista);
List* insertList(List* lista, Point* elem);
void printPoints(List* points);

int main()
{
    int number_of_points;
    cout << "Digite o número de pontos: \n";
    cin >> number_of_points;
    srand(time(NULL));
    List* lista_de_pontos = createList();
    lista_de_pontos = generatePoints(number_of_points);
    printPoints(lista_de_pontos);
    freeList(lista_de_pontos);
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
    List* auxiliar = points->next;
    int i = 0;
    while(auxiliar != NULL)
    {
        cout << "Ponto " << i << ": " <<auxiliar->ponto->x << ", " << auxiliar->ponto->y << "\n";
        auxiliar = auxiliar->next;
        i++;
    }    
}