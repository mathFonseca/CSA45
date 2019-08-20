/**
 * @file appWindow.cpp
 * @brief Opening a window.
 * @author Ricardo Dutra da Silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <cg.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


/* Functions. */
void Display(void);


void Display(void)
{
	/* Clear buffers. */
	/*forca o glut a limpar a tela*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*aqui voce desenha as coisas de fato*/
	/* Force drawing. */
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
	
	/* Bind callback functions. */
	glutDisplayFunc(Display);


	/* Give control to GLUT.*/
	glutMainLoop();
}
