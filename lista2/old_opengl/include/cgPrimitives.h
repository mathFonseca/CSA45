/**
 * @file cgPrimitives.h
 * @brief Basic geometric primitives.
 * @author Ricardo Dutra da Silva
 */


#ifndef _CGPRIMITIVES_H_
#define _CGPRIMITIVES_H_


#include <cgTypes.h>
#include <math.h>


/* Defines. */
#define CG_ORIENTATION_LEFT       1
#define CG_ORIENTATION_RIGHT     -1
#define CG_ORIENTATION_COLLINEAR  0


/* Types. */


/* Functions. */


/// Triangle area.
/**
 * This function computes the area of the triangle given by three points p1, p2 and p3.
 * @param p1 First point of the triangle.
 * @param p2 Second point of the triangle.
 * @param p3 Third point of the triangle.
 * @return The area of the triangle.
 * 
 * @sa cgTriangleSignedArea cgTriangleSignedArea2
 */
double cgTriangleArea(cgPoint p1, cgPoint p2, cgPoint p3);

/// Signed triangle area.
/**
 * This function computes the signed area of the triangle given by three points p1, p2 and p3.
 * @param p1 First point of the triangle.
 * @param p2 Second point of the triangle.
 * @param p3 Third point of the triangle.
 * @return The signed area of the triangle.
 * 
 * @sa cgTriangleArea cgTriangleSignedArea2
 */
double cgTriangleSignedArea(cgPoint p1, cgPoint p2, cgPoint p3);

/// Two times signed triangle area.
/**
 * This function computes the double of the area of the triangle given by three points p1, p2 and p3. The function is used to compute the orientation of three points.
 * @param p1 First point of the triangle.
 * @param p2 Second point of the triangle.
 * @param p3 Third point of the triangle.
 * @return Twice the signed area of the triangle.
 * 
 * @sa cgTriangleArea cgTriangleSignedArea cgOrientation
 */
double cgTriangleSignedArea2(cgPoint p1, cgPoint p2, cgPoint p3);

/// Orientation of three points.
/**
 * This function computes the orientation of three points using the signed area ot the triangle defined by the three points.
 * @param p1 First point of the triangle.
 * @param p2 Second point of the triangle.
 * @param p3 Third point of the triangle.
 * @return CG_ORIENTATION_LEFT if points form a left turn, CG_ORIENTATION_RIGHT if points form a right turn, CG_ORIENTATION_COLLINEAR if points are collinear.
 * 
 * @sa cgTriangleSignedArea2
 */
int cgOrientation(cgPoint p1, cgPoint p2, cgPoint p3);



#endif /* _CGPRIMITIVES_H_ */
