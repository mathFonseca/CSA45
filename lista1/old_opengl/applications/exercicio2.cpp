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

/* Globals */
int winwidth, winheight;
point_2d p1, p2, p3;

void Init(){
    
    /* Select clearing color. */
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Reshape(int w, int h){

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, 100.0, 0.0, 100.0);
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

void Display(void){
    
    /* Clear buffers. */
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f (1.0, 0.0, 0.0);
        glVertex2d(p1.x+50, p1.y+50);
        glVertex2d(p2.x+50, p2.y+50);
        glVertex2d(p3.x+50, p3.y+50);  
    glEnd();
   
    glFlush();
}

int main(int argc, char** argv)
{
    /* Calcula info exercicio 1*/
    printf("Definindo pontos...\n");
    double area1, area2;

    p1 = point(5, 5);
    p2 = point(0, 0);
    p3 = point(10, 0);
    
    area1 = area_triangulo_unsigned(p2, p1, p3);
    area2 = area_triangulo_signed(p2, p1, p3);    
    
    printf("Area Triangulo Unsigned: %.2f.\nArea Triangulo Signed:  %.2f.\n", 
    area1, area2);
    
    /* Call glut init functions. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(512, 512); 
    glutCreateWindow("Window");
    Init();

    /* Call glut drawing functions. */
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}
