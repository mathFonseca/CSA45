#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <GL/glut.h>
#include "geo.h"

/* Functions. */
void Init(void);
void Reshape(int w, int h);
void Display(void);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void DrawPoints(void);
void DrawLines();

/* Defines. */
#define MAXNPTS 1000

/* Globals */
int winwidth, winheight;
int npts = 0;
int flag = 0;
point2d points[MAXNPTS];

void Init(){
    
    /* Select clearing color. */
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Reshape(int w, int h){

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, 512.0, 0.0, 512.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   winwidth  = w;
   winheight = h;
}

void Keyboard(unsigned char key, int x, int y){

    switch (key){
        case 27:
            exit(0);
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}

void Mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (npts < MAXNPTS)
                {
		            points[npts].x = x;
                    points[npts].y = 512.0-y;
		            printf("Reading point (%f,%f).\n", points[npts].x, points[npts].y);
                    printf("Points: %d\n", npts);
                    npts++;
                }

                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                npts = 0;
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

void DrawPoints()
{
    int i;
    double u_area, s_area;
    glColor3f (0.0, 0.0, 0.0);
    glPointSize((GLdouble) 2);
    // Printa os pontos
    glBegin(GL_POINTS);
    for (i = 0; i < npts; i++)
        glVertex2d(points[i].x, points[i].y);
    glEnd();
    // Printa as retas
    glBegin(GL_LINES);
    for (i = 0; i < npts; i+=3)
    {
        if(i != npts - 1)
        {
            glVertex2d(points[i].x, points[i].y);
            glVertex2d(points[i+1].x, points[i+1].y);            
        }
    }
    glEnd();
    // Printa os triangulos
    glBegin(GL_TRIANGLES);
    for (i = 0; i < npts; i+=3)
    {
        // Quantidade de repetições é a quantidade de triangulos
        if( i != npts - 2)
        {        
            point_2d A, B, C;

            A = c_Point(points[i].x, points[i].y);
            B = c_Point(points[i+1].x, points[i].y);
            C = c_Point(points[i+2].x, points[i+2].y);

            u_area = u_areaTriangle(A, B, C);
            s_area = s_areaTriangle(A, B, C);

            printf("Area (un): %.2f\n", u_area);
            printf("Area (s): %.2f\n", s_area);

            if(left(A, B, C))
                glColor3f(1.0, 1.0, 0.0);
            else
                glColor3f(0.0, 0.0, 1.0); 

            glVertex2d(points[i].x, points[i].y);
            glVertex2d(points[i+1].x, points[i+1].y);
            glVertex2d(points[i+2].x, points[i+2].y);
        }
    }
    glEnd();
}

void Display(void){
    
    /* Clear buffers. */
    glClear(GL_COLOR_BUFFER_BIT);
   
    /* Draw. */
    DrawPoints();

    glFlush();
}

int main(int argc, char** argv){

    /* Call glut init functions. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(512, 512); 
    glutCreateWindow("Test");
    Init();

    /* Call glut drawing functions. */
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}
