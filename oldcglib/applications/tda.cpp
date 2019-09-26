//------------------------------------------------------------------------------
// Biblioteca criada para comportar diversas estruturas de dados
// Autor: Matheus Fonseca Alexandre de Oliveira


#include "tda.h"
#include <iostream>
#define FUNCTIONS_DEBUG
#define ERRORS
using namespace std;

Point* createPoint(double x, double y)
{
    Point* novo_ponto = (Point*)malloc(sizeof(Point));
    novo_ponto->x = x;
    novo_ponto->y = y;
    return novo_ponto;
}

points_List* createList()
{
   return NULL;
}

points_List* append(Point* received_point, points_List* list)
{
    if(received_point == NULL)
    {
        #ifdef ERRORS
            cout << "Queue Append Error: Point not defined.\n";
        #endif
    }
    else
    {
        /*
        * First case: list is null.
        */
       if(list == NULL)
       {
           list = (points_List*)malloc(sizeof(points_List));
           list->point = createPoint(received_point->x, received_point->y);
           list->next_node = list;
           list->prev_node = list;
           #ifdef  FUNCTIONS_DEBUG
                cout << "* * Node Created: \n";
                cout << "Header: " << list << "\n";
                cout << "Point: " << list->point->x << "," << list->point->y << "\n";
                cout << "Next: " << list->next_node << "\n";
                cout << "Prev: " << list->prev_node << "\n";
           #endif
           return list;
       }
       /*
       * Second case: list already have a point
       */ 
       else
       {
           points_List* new_node = (points_List*)malloc(sizeof(points_List));
           new_node->next_node = NULL;
           new_node->prev_node = NULL;

           new_node->point = createPoint(received_point->x, received_point->y);
           new_node->next_node = list;
           list->prev_node->next_node = new_node;
           new_node->prev_node = list->prev_node;
           list->prev_node = new_node;
           #ifdef  FUNCTIONS_DEBUG
                cout << "* * Node Created: \n";
                cout << "Header: " << new_node << "\n";
                cout << "Point: " << new_node->point->x << "," << new_node->point->y << "\n";                
                cout << "Next: " << new_node->next_node << "\n";
                cout << "Prev: " << new_node->prev_node << "\n";
                cout << "Next Prev: " << new_node->next_node->prev_node << "\n";
                cout << "Prev Next: " << new_node->prev_node->next_node << "\n";
           #endif
           return list;
       } 
    }
}

void printList(points_List* list)
{
    /* TODO */
}

void freeList(points_List* list)
{
    /* TODO  */
}

points_List* remove(Point* received_point, points_List* list)
{
    if(received_point ==  NULL)
    {
        #ifdef ERRORS
            cout << "Queue Remove Error: Point not defined.\n";
        #endif
    }
    else if(list ==  NULL)
    {
        #ifdef ERRORS
            cout << "Queue Remove Error: List not defined.\n";
        #endif
    }
    else
    {
        /*
        * First Case: Point to be removed is the head
        */
       if(list->point == received_point)
        {
            points_List* new_header = list->next_node;
            list->prev_node->next_node = list->next_node;
            list->next_node->prev_node = list->prev_node;
            free(list);
            return new_header;
        }
        /* 
        * Second Case: Point to be removed need to be search to fount out
        */
        else
        {
            points_List* lista_auxiliar = list->next_node;
            while(lista_auxiliar != list)
            {
                if(lista_auxiliar->point == received_point)
                {
                    /* todo */
                }

                lista_auxiliar = lista_auxiliar->next_node;

                /*
                * Error Case: Point doesn't exist in this List
                */ 
                if(lista_auxiliar == list)
                {
                    #ifdef ERRORS
                      cout << "Queue Remove Error: Point not exist in this scope.\n";
                    #endif
                    return NULL;
                }
            }
        }
    }
}