/**
 * @file appPoints.cpp
 * @brief Inserting points.
 * @author Ricardo Dutra da Silva
 */


#include <cg.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shader.h"


/* Defines. */
#define MAX_NUM_POINTS 1024
#define WINDOW_SIZE 512	


/* Globals */
GLuint VAO, VBO;
int npoints = 0;
cgPoint vertices[MAX_NUM_POINTS];
GLint wh, ww;


void Init(void);
void Reshape(int, int);
void Display(void);
void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);

void Reshape(int w, int h)
{
	ww = w;
	wh = h;
	glViewport(0, 0, w, h);
}


void Keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
		case 27:
			exit(0);
		case 'q':
		case 'Q':
			exit(0);
	}
}

void Mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				printf("MOUSE CLICK (%d, %d)\n", x, y);
				float xc = (2.0*(x/(float)ww))-1.0;
				float yc = (2.0*((wh-y)/(float)wh))-1.0;
				printf("MOUSE CLICK (%f, %f)\n", xc, yc);
				cgPointSet(&vertices[npoints], xc, yc, 0.0);
				cgPointPrint(vertices[npoints]);
				npoints++;


				glBindBuffer(GL_ARRAY_BUFFER, VBO);
    				glBufferSubData(GL_ARRAY_BUFFER, 0, npoints*sizeof(cgPoint), vertices);

				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}



void Init()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_NUM_POINTS*sizeof(cgPoint), (void *)0, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferSubData(GL_ARRAY_BUFFER, 0, npoints*sizeof(cgPoint), vertices);

	GLuint program = LoadShaders("simple.vert", "simple.frag");
	glUseProgram(program);
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, npoints);

	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);

	if (glewInit())
       	{
		fprintf(stderr, "Unable to initialize GLEW ... exiting.");
		exit(EXIT_FAILURE);
	}
	
	Init();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutDisplayFunc(Display);

	glutMainLoop();
}
