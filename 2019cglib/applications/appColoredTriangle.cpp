/**
 * @file appColorTriangle.cpp
 * @brief Drawing a colored triangle.
 * @author Ricardo Dutra da Silva
 */

#include <cg.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "shader.h"


/* Globals */
GLuint VAO, VBO, CBO;


/* Functions. */
void Init(void);
void Display(void);
void Keyboard(unsigned char, int, int);


void Keyboard(unsigned char key, int x, int y)
{
	/* Closing a window using the keyboard. */
	switch (key)
	{
		/* Escape key.*/
		case 27: 
			exit(0);
		/* q key. */
		case 'q':
		case 'Q':
			exit(0);
	}
}


void Init()
{
	/* Create vertex array object (VAO). */
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* Some vertices for a triangle. */
	GLfloat vertices[] = {
    		-0.8f, -0.8f, 0.0f, 1.0f,
     		 0.0f,  0.8f, 0.0f, 1.0f,
     		 0.8f, -0.8f, 0.0f, 1.0f
  	};

	/* Some color for a triangle. */
  	GLfloat colors[] = {
    		1.0f, 0.0f, 0.0f, 1.0f,
    		0.0f, 1.0f, 0.0f, 1.0f,
    		0.0f, 0.0f, 1.0f, 1.0f
	};

	/* Create vertex buffer object (VBO). */
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Copy data to VBO. */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	/* Create color buffer object (CBO). */
	glGenBuffers(1, &CBO);
  	glBindBuffer(GL_ARRAY_BUFFER, CBO);
  	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	/* Load and compile shaders. */
	GLuint program = LoadShaders("simple2.vert", "simple2.frag");
	glUseProgram(program);
}


void Display(void)
{

	/* Clear buffers for drawing. */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* Draw. */ 
	//glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	/* Force to display. */
	glFlush();
}


int main(int argc, char** argv)
{
	/* Init GLUT and GL. */
	glutInit(&argc, argv);

	/* Init display mode. */
	glutInitDisplayMode(GLUT_RGBA);

	/* Window size. */
	glutInitWindowSize(512, 512);

	/* OpenGL Context. */
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	/* Create window. */
	glutCreateWindow(argv[0]);

	/* Init GLEW. */
	if (glewInit())
       	{
		fprintf(stderr, "Unable to initialize GLEW ... exiting.");
		exit(EXIT_FAILURE);
	}
	
	/* Init GL drawing. */
	Init();

	/* Bind callback functions. */
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);

	/* Give control to GLUT.*/
	glutMainLoop();
}
