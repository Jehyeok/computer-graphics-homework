#include "stdafx.h"
#include <glut.h>
#include <windows.h>
#include <math.h>

GLfloat window_width;
GLfloat window_height;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f*h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 100.0, -100.0);
	}
	else
	{
		window_width = 100.0f*w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 100.0, -100.0);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Enable smooth shading    
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// First
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);
	glEnd();

	// Second
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);
	glEnd();

	// Third
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glEnd();

	// Fourth
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-30.0f, -30.0f, 30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);
	glEnd();

	// Fifth
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)255);
	glVertex3f(-30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(30.0f, 30.0f, 30.0f);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glEnd();

	// Sixth
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(30.0f, 30.0f, -30.0f);

	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)0);
	glVertex3f(-30.0f, -30.0f, -30.0f);

	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(-30.0f, 30.0f, -30.0f);
	glEnd();

	// Flush drawing commands
	glPopMatrix();
	glutSwapBuffers();
}

void ContorolKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	glutPostRedisplay();
}

int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Atom");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(ContorolKey);
	SetupRC();
	glutMainLoop();
}