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

void Init(){
    
    /* Select clearing color. */
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Reshape(int w, int h){

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, 50.0, 0.0, 50.0);
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

    glBegin(GL_LINE_STRIP);
    glEnd();
   
    glFlush();
}

int main(int argc, char** argv)
{
    /* Call glut init functions. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(100, 100); 
    glutCreateWindow("Window");
    Init();

    /* Call glut drawing functions. */
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);

    glutMainLoop();
    return 0;
}
