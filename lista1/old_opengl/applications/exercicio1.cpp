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
point_2d u, v;
point_2d u_v_soma;
point_2d u_v_vector;

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
    	glColor3f (0.0, 0.0, 0.0);
        glVertex2d(p1.x+25, p1.y+25);
        glVertex2d(p2.x+25, p2.y+25);
        glVertex2d(p3.x+25, p3.y+25);
    glEnd();
   
    glFlush();
}

int main(int argc, char** argv)
{
    /* Calcula info exercicio 1*/
    printf("Definindo pontos...\n");

    p1 = point(5, 5);
    p2 = point(0, 0);
    p3 = point(10, 0);
    
    
    printf("Ponto 1: %.2f x %.2f y\n", p1.x, p1.y);
    printf("Ponto 2: %.2f x %.2f y\n", p2.x, p2.y);
    printf("Ponto 3: %.2f x %.2f y\n", p3.x, p3.y);

    
    printf("Definindo vetores...\n");
    u = vector(p1, p2);
    v = vector(p3, p2);

    printf("Definindo demais valores...\n");
    double u_v_mult, u_mol, v_mol;
    u_v_mult = produto_interno(u,v);
    u_mol = produto_interno(u,u);
    v_mol = produto_interno(v,v);    
    
    
    printf("Definindo vetores...\n");
    u_v_soma = soma_vetores(u,v);
    u_v_vector = produto_vetorial(u,v);

    printf("Soma de u e v: %.2f x, %.2f y\n", u_v_soma.x, u_v_soma.y);
    printf("Produto Vetorial de u e v: %.2f z\n", u_v_vector.x);

    printf("Produto Interno u*v: %.2f\n", u_v_mult);
    printf("Produto Interno u*u: %.2f\n", u_mol);
    printf("Produto Interno v*v: %.2f\n", v_mol);
    
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
