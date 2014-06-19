#include "stdafx.h"
#include <windows.h>
#include <glut.h>

GLfloat window_width;
GLfloat window_height;

class Rectangle {
private:
	GLfloat x;
	GLfloat y;
	GLfloat x_inner;
	GLfloat y_inner;
	GLsizei rsize;
	GLsizei rsize_inner;
	GLfloat xstep;
	GLfloat ystep;
	GLfloat padding;
	
public:
	Rectangle()
	{

	}

	Rectangle(GLfloat x, GLfloat y, GLfloat xstep, GLfloat ystep)
	{
		this->x = x;
		this->y = y;
		this->x_inner = this->x + padding;
		this->y_inner = this->y + padding;
		this->xstep = xstep;
		this->ystep = ystep;

		this->rsize = 50.0f;
		this->rsize_inner = 30.0f;
		this->padding = (this->rsize - this->rsize_inner) / 2;
	}

	void draw()
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glRectf(this->x, this->y, this->x + rsize, this->y + rsize);
		glColor3f(1.0f, 1.0f, 0.0f);
		glRectf(this->x_inner + this->padding, this->y_inner + this->padding, this->x_inner + this->rsize - this->padding, this->y_inner + this->rsize - this->padding);
	}

	void setStepValue() 
	{
		if (isXColided()) this->xstep = -this->xstep;
		if (isYColided()) this->ystep = -this->ystep;
	}

	void move()
	{
		this->x = this->xstep;
		this->y = this->ystep;
		this->x_inner = this->xstep;
		this->y_inner = this->ystep;
	}

	bool isXColided()
	{
		return this->x > window_width - this->rsize || this->x < -window_width;
	}

	bool isYColided()
	{
		return this->x > window_width - this->rsize || this->x < -window_width;
	}
};


GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat x1_inner = 0.0f;
GLfloat y1_inner = 0.0f;

GLfloat x2 = -50.0f;
GLfloat y2 = -50.0f;
GLfloat x2_inner = -50.0f;
GLfloat y2_inner = -50.0f;

GLsizei rsize = 50.0f;
GLsizei rsize_inner = 30.0f;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat padding = (rsize - rsize_inner) / 2;



void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	

	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x1 + rsize, y1 + rsize);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x1_inner + padding, y1_inner + padding, x1_inner + rsize - padding, y1_inner + rsize - padding);

	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(x2, y2, x2 + rsize, y2 + rsize);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x2_inner + padding, y2_inner + padding, x2_inner + rsize - padding, y2_inner + rsize - padding);

	glutSwapBuffers();
}

void TimerFunction(int value)
{
	if (x1 > window_width - rsize
		|| x1 < -window_width)
		xstep = -xstep;

	if (y1>window_height - rsize
		|| y1< -window_height)
		ystep = -ystep;

	x1 += xstep;
	x1_inner += xstep;
	y1 += ystep;
	y1_inner += ystep;

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}


void SetupRC(void) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
	}
	else
	{
		window_width = 100.0f*w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("BounceRectangle");
	// glutCreateWindow("Simple");
	// OS가 판단하기에 화면에 그려야 할 때 그림
	// glutPostRedisplay(); OS에게 강제로 화면에 그리라고 말함(RenderScene)
	glutReshapeFunc(ChangeSize); // 윈도우 사이즈 리사이즈 할 때 호출
	glutDisplayFunc(RenderScene); // 그려야될떄만 호출
	glutTimerFunc(2000, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}

// glutSpecialFunc 키보드 처리를 위한 콜백

// xRot각도만큼, x축을 기준으로 회전
// glRotatef(xRot, 1.0f, 0.0f, 0.0f);