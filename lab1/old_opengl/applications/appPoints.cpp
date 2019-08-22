#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <GL/glut.h>

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
point2d points[MAXNPTS];
int color_count = 0;

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
                    npts++;
                }
		/* Forca o redesenho */
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
	float red = 0.0;
	float blue = 0.0;
	float green = 0.0;
    // glColor3f (0.0, 0.0, 0.0);
    glPointSize((GLdouble) 2);
   /* GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES */
    glBegin(GL_TRIANGLES);
    for (i = 0; i < npts; i++)
    {
	glColor3f(red,blue,green);
        glVertex2d(points[i].x, points[i].y);
  	if (color_count >= 3){
		color_count = 0;
	red += 0.5;
	blue += 0.5;
	green += 0.5;
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

    color_count = 0;
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
