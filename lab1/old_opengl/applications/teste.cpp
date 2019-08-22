#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Types. */
typedef struct point_2d
{
    double x;
    double y;

} point2d;

int left(point_2d point_1, point2d point_2, point2d point_3)
{
    int area;
    int A_x = point_3.x - point_1.x;
    int A_y = point_3.y - point_1.y;
    int B_x = point_2.x - point_1.x;
    int B_y = point_2.y - point_1.y;
    area = ((A_x * B_y) - (B_x * A_y));
    area = area/2;
    return area;
}

int main()
{
    point2d ponto_1, ponto_2, ponto_3;

    ponto_1.x = 0;
    ponto_1.y = 0;

    ponto_2.x = 3;
    ponto_2.y = 0;

    ponto_3.x = 0;
    ponto_3.y = 4;

    int area;

    area = left(ponto_1, ponto_2, ponto_3);

    printf("Area: %d\n", area);

    return 0;
}
