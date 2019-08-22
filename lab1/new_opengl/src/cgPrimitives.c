/**
 * @file cgPrimitives.c
 * @brief Implementation of basic geometric primitives.
 * @author Ricardo Dutra da Silva
 */


#include <cgPrimitives.h>


double cgTriangleArea(cgPoint p1, cgPoint p2, cgPoint p3)
{
	double x1 = cgPointGetX(p1);
	double y1 = cgPointGetY(p1);
	double x2 = cgPointGetX(p2);
	double y2 = cgPointGetY(p2);
	double x3 = cgPointGetX(p3);
	double y3 = cgPointGetY(p3);

	return fabs(((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2.0);		
}

double cgTriangleSignedArea(cgPoint p1, cgPoint p2, cgPoint p3)
{
	double x1 = cgPointGetX(p1);
	double y1 = cgPointGetY(p1);
	double x2 = cgPointGetX(p2);
	double y2 = cgPointGetY(p2);
	double x3 = cgPointGetX(p3);
	double y3 = cgPointGetY(p3);

	return (((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2.0);		
}

double cgTriangleSignedArea2(cgPoint p1, cgPoint p2, cgPoint p3)
{
	double x1 = cgPointGetX(p1);
	double y1 = cgPointGetY(p1);
	double x2 = cgPointGetX(p2);
	double y2 = cgPointGetY(p2);
	double x3 = cgPointGetX(p3);
	double y3 = cgPointGetY(p3);

	return ((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));		
}

int cgOrientation(cgPoint p1, cgPoint p2, cgPoint p3)
{
	double area = cgTriangleSignedArea2(p1, p2, p3);

	if (area > 0.0)
		return CG_ORIENTATION_LEFT;
	
	if (area < 0.0)
		return CG_ORIENTATION_RIGHT;
	
	return CG_ORIENTATION_COLLINEAR;
}
