#include "stdafx.h"
#include <windows.h>
#include <glut.h>
#include <math.h>

GLfloat window_width;
GLfloat window_height;

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

}

void RenderScene(void)
{
	GLfloat x, y, z, angle;
	GLfloat r = 1.0f;
	GLfloat rstep = 0.5f;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f); //(angle)
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	z = 0.0f;

	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
		// 3.14/0.1 개의 포인트를 뿌린다 총 3바퀴 
	{
		x = r*sin(angle);
		y = r*cos(angle);
		glVertex3f(x, y, z);
		r += rstep;
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("SpringVertex");

	// glutCreateWindow("Simple");
	// OS가 판단하기에 화면에 그려야 할 때 그림
	// glutPostRedisplay(); OS에게 강제로 화면에 그리라고 말함(RenderScene)
	glutReshapeFunc(ChangeSize); // 윈도우 사이즈 리사이즈 할 때 호출
	glutDisplayFunc(RenderScene); // 그려야될떄만 호출
	SetupRC();
	glutMainLoop();
}*/

// glutSpecialFunc 키보드 처리를 위한 콜백

// xRot각도만큼, x축을 기준으로 회전
// glRotatef(xRot, 1.0f, 0.0f, 0.0f);