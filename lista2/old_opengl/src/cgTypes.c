/**
 * @file cgTypes.c
 * @brief Implementation of basic functions for manipulation of types.
 * @author Ricardo Dutra da Silva
 */


#include <cgTypes.h>


void cgPointSet(cgPoint *p, double x, double y, double z)
{
	p->coordinates[0] = x;		
	p->coordinates[1] = y;		
	p->coordinates[2] = z;		
}

double cgPointGetX(cgPoint p)
{
	return p.coordinates[0];		
}

double cgPointGetY(cgPoint p)
{
	return p.coordinates[1];		
}

double cgPointGetZ(cgPoint p)
{
	return p.coordinates[2];		
}

void cgPointSetRand(cgPoint *p)
{
	p->coordinates[0] = ((double)rand()/(double)RAND_MAX);		
	p->coordinates[1] = ((double)rand()/(double)RAND_MAX);		
	p->coordinates[2] = ((double)rand()/(double)RAND_MAX);		
}

void cgPointPrint(cgPoint p)
{
	printf("(%f,%f,%f)\n", cgPointGetX(p), cgPointGetY(p), cgPointGetZ(p));
}

void cgListInit(cgList *list)
{
	list->nelem = 0;
	list->head = NULL;
}

void cgListAppend(cgList *list, void *p)
{
	cgListNode *n = (cgListNode *) malloc(sizeof(cgListNode));
	n->data = p;

	if (list->head != NULL)
	{
		n->prev = list->head->prev->next;	
		n->next = list->head;	
		list->head->prev->next = n;	
		list->head->prev = n;	
		list->nelem++;
	}
	else
	{
		n->prev = n;
		n->next = n;
		list->nelem++;
		list->head = n;
	}
}

void cgPolygonInit(cgPolygon *poly)
{
	cgListInit(&(poly->vertices));
}

void cgPolygonAppend(cgPolygon *poly, cgPoint *p)
{
	cgListAppend(&(poly->vertices), (void *) p);
}

void cgPolygonPrint(
	cgPolygon poly
)
{
	cgListPrint(poly.vertices, &cgPolygonPrintFunc);
}

void cgPolygonPrintFunc(
	void *p
)
{
	cgPoint *pnt = (cgPoint *) p;
	cgPointPrint(*pnt);
}

void cgListPrint(
	cgList list,
        void (*printfunc)(void *)
)
{
	cgListNode *head = list.head;
	cgListNode *n = head;

	do
	{
		(*printfunc)(n->data);
		n = n->next;
	}
	while (n != head);
}
