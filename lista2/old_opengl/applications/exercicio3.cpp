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
bool intersecPropria(point_2d ponto_1, point_2d ponto_2, point_2d ponto_3, point_2d ponto_4);

/* Defines. */
#define MAXNPTS 1000

/* Globals */
int winwidth, winheight;
int npts = 0;
int n = 0;
int drawing_polygon = 1;
point2d polygon[MAXNPTS];
point2d pontos[4];

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
                if(drawing_polygon > 0)
                {
                    if (npts < MAXNPTS)
                    {

                            polygon[npts].x = x;
                            polygon[npts].y = 512.0-y;
                            printf("Reading point (%f,%f).\n", 
                            polygon[npts].x, polygon[npts].y);
                            printf("npts: %d\n", npts);
                            npts++;
                    }
                } 
                else 
                {
                    if(npts < 4)
                    {
                        pontos[npts].x = x;
                        pontos[npts].y = 512.0 - y;
                        printf("Reading point (%f,%f).\n", 
                            pontos[npts].x, pontos[npts].y);
                        npts++;
                    }
                    else
                        npts = 0;
                    
                }   
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                n = npts;
                npts = 0;
                drawing_polygon = drawing_polygon * (-1);
            }
            break;
        default:
            break;
    }
}

void DrawPoints()
{
    int i;
    glColor3f (0.0, 0.0, 0.0);
    glPointSize((GLdouble) 2);
    // Quando clicar em 4 botões, aplica as funções e desenha conforme resultado.
    if(drawing_polygon > 0 )
    {
        glBegin(GL_LINE_STRIP);
        for(i = 0; i < npts; i++)
        {
            glVertex2d(polygon[i].x, polygon[i].y);
        }
        glEnd();
    }
    else
    {
        glBegin(GL_LINES);
            glVertex2d(polygon[n].x, polygon[n].y);
            glVertex2d(polygon[0].x, polygon[0].y);
        glEnd();
    }

    


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
