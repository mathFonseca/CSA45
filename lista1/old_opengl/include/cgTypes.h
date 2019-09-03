/**
 * @file cgTypes.h
 * @brief Basic geometric types and related functions.
 * @author Ricardo Dutra da Silva
 */


#ifndef _CGTYPES_H_
#define _CGTYPES_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/* Defines. */

//#define X 0
//#define Y 1
//#define Z 2
//

/* Types. */

/// cgPoint
/** The struct represents a 3D point with coordinates of type double. 
 */
typedef struct cg_point_3d
{
    	/// Array of coordinates.
    	/** The coordinates of a point are stored using as array of three positions. The positions indexed by 0, 1 and 2 are related to x, y and z coordinates. */
	double coordinates[3];

} cgPoint;

/// cgListNode
/** The struct represents a node in a list. 
 */
typedef struct cg_list_node
{
	/// Data.
    	/** Pointer to the data type. */
	void *data;
	/// Previous node.
    	/** Previous node in the list. */
    	struct cg_list_node *prev;
	/// Next node.
    	/** Next node in the list. */
    	struct cg_list_node *next;

} cgListNode;

/// cgList
/** The struct represents a sequence of data. The data are stored using a circular doubly connected list. 
 */
typedef struct cg_list
{
	/// Number of elements.
    	/** Number of elements in the list. */
	int nelem;
	/// Head of the list.
    	/** Pointer to first point in the list. */
    	struct cg_list_node *head;

} cgList;

/// cgPolygon
/** The struct represents a polygon defined by a sequence of points. The sequence of points should be given in counterclockwise orientation. 
 */
typedef struct cg_polygon
{
    	/// List of vertices.
    	/** The vertices are points stored in a list. */
    	cgList vertices;

} cgPolygon;


/* Functions. */


/// Set point coordinates.
/**
 * This function sets the coordinates values of a point. 
 * @param p The point.
 * @param x The x coordinate value.
 * @param y The y coordinate value.
 * @param z The z coordinate value.
 */
void cgPointSet(cgPoint *p, double x, double y, double z);

/// Get point x coordinate.
/**
 * This function returns the x coordinate of a point. 
 * @param p The point.
 * @return The x coordinate.
 */
double cgPointGetX(cgPoint p);

/// Get point y coordinate.
/**
 * This function returns the y coordinate of a point. 
 * @param p The point.
 * @return The y coordinate.
 */
double cgPointGetY(cgPoint p);

/// Get point z coordinate.
/**
 * This function returns the z coordinate of a point. 
 * @param p The point.
 * @return The z coordinate.
 */
double cgPointGetZ(cgPoint p);

/// Set point coordinates (random).
/**
 * This function sets the coordinates values of a point to random values in the range [0,1]. The random seed must be initialized in the main funtion (srand(time(NULL)))
 * @param p The point.
 */
void cgPointSetRand(cgPoint *p);

/// Print point.
/**
 * This function prints a point. 
 * @param p The point.
 */
void cgPointPrint(cgPoint p);

/// Init list.
/**
 * This function initializes a list. This function should always be called before using a list. 
 * @param list The list.
 */
void cgListInit(cgList *list);

/// Insert.
/**
 * This function inserts a data at the end of a point list. 
 * @param list The list.
 * @param p The data.
 */
void cgListInsert(cgList *list, void *p);

/// Init polygon.
/**
 * This function initializes a polygon. This function should always be called before using a polygon. 
 * @param poly The polygon.
 */
void cgPolygonInit(cgPolygon *poly);

/// Append.
/**
 * This function inserts a point at the end of a list. 
 * @param list The list.
 * @param p The data.
 */
void cgListAppend(cgList *list, void *p);

/// Insert point.
/**
 * This function inserts a point in a polygon. The point is inserted in the last * position of the sequence of vertices. 
 * @param poly The polygon.
 * @param p The point.
 */
void cgPolygonAppend(cgPolygon *poly, cgPoint *p);

/// Print list.
/**
 * This function prints a list. 
 * @param list The list.
 * @param printfunc Reference to a printing function.
 */
void cgListPrint(cgList list, void (*printfunc)(void *));

/// Print polygon.
/**
 * This function prints a polygon. 
 * @param poly The polygon.
 */
void cgPolygonPrint(cgPolygon poly);

/// Print polygon point.
/**
 * This function prints a polygon point. 
 * @param p The point.
 */
void cgPolygonPrintFunc(void *p);

#endif /* _CGTYPES_H_ */
