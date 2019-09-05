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


/* Types. */
typedef struct point_2d
{
    double x;
    double y;

} point2d;

/* Defines. */
#define MAXNPTS 1000

/* Globals */
int winwidth, winheight;
int npts = 0;
bool func = false;
point2d reta1[MAXNPTS];
point2d reta2[MAXNPTS];

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
                    if(npts == 0)
                    {
                        reta1[0].x = x;
                        reta1[0].y = 512.0-y;
                        npts++;
                        func = false;
                    }
                    else if(npts == 1)
                    {
                        reta1[1].x = x;
                        reta1[1].y = 512.0-y;
                        npts++;
                    }
                    else if(npts == 2)
                    {
                        reta2[0].x = x;
                        reta2[0].y = 512.0-y;
                        npts++;
                    }
                    else
                    {
                        reta2[1].x = x;
                        reta2[1].y = 512.0 - y;
                        npts = 0; // Reseta npts.
                        func = true;
                    }
                    
		           // points[npts].x = x;
                    // points[npts].y = 512.0-y;
		            printf("Reading point (%f,%f).\n", points[npts].x, points[npts].y);
                    // npts++;
                }

                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                npts = 0;
                glutPostRedisplay();
                // reinicia as retas
            }
            break;
        default:
            break;
    }
}

void DrawPoints()
{
    int i;
    bool intersecPropria;
/*
bool intersecPropria(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3, point_2d ponto_4);
bool between(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3);
bool intersec(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3, point_2d ponto_4);
*/
    glColor3f (0.0, 0.0, 0.0);
    glPointSize((GLdouble) 2);
    // Quando clicar em 4 botões, aplica as funções e desenha conforme resultado.
    if(func == true)
    {
        if(intersecPropria(reta1[0], reta1[1], reta2[0], reta2[1]))
            glColor3f(1.0, 0.0, 0.0);
        else if(intersec(reta1[0], reta1[1], reta2[0], reta2[1]))
            glColor3f(0.0, 0.0, 1.0);
    }
    glBegin(GL_LINES);
    // Desenha reta 1
        glVertex2d(reta1[0].x, reta1[0].y);    
        glVertex2d(reta1[i].x, reta1[i].y);
    // Desenha reta 2
        glVertex2d(reta2[0].x, reta2[0].y);    
        glVertex2d(reta2[i].x, reta2[i].y);
    
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
