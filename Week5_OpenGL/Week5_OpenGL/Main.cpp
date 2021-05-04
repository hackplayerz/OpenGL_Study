#include <glut.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(.5f, .5f, .5f);
	glBegin(GL_POLYGON);

	glVertex3f(-.5f, -.5f, 0.f);
	glVertex3f(.5f, -.5f, 0.f);
	glVertex3f(.5f, .5f, 0.f);
	glVertex3f(-.5f, .5f, 0.f);
	
	
	glEnd();
	glFlush();
}

void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat widFactor = static_cast<GLfloat>(NewWidth) / static_cast<GLfloat>(NewHeight);

	
}