#include <glut.h>

GLfloat Delta = 0.f;
float Value = -0.01f;
float bx = 0;
float by = -0.75f;
float xdiff = 0.02f;
float ydiff = 0.02f;

void OnKeyboardPressed(const unsigned char KeyPressed, int X, int Y)
{
	switch (KeyPressed)
	{
		case 'a':
			Value = -0.01f;
			break;
		case 's':
			Value = 0.01f;
			break;
		case 'q':
			exit(0);
	}
}

void OnDrawCall()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Bottom bar
	glBegin(GL_POLYGON);
	glColor3f(0, 0.5f, 0.8f);
	glVertex3f(-0.2f + Delta, -0.9f, 0.f);
	glVertex3f(0.2f + Delta, -0.9f, 0.f);
	glVertex3f(0.2f + Delta, -0.8f, 0.f);
	glVertex3f(-0.2f + Delta, -0.8f, 0.f);
	glEnd();

	// Projectile
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(bx - 0.05f, by - 0.05f, 0.f);
	glVertex3f(bx + 0.05f, by - 0.05f, 0.f);
	glVertex3f(bx + 0.05f, by + 0.05f, 0.f);
	glVertex3f(bx - 0.05f, by + 0.05f, 0.f);
	glEnd();

	glutSwapBuffers();
}

void OnTick(const int value)
{
	Delta += Value;

	bx = bx + xdiff;
	by = by + ydiff;

	if (bx > 1)
	{
		xdiff = -0.02f;
	}
	if (bx < -1)
	{
		xdiff = 0.02f;
	}
	if (by > 1)
	{
		ydiff = -0.02f;
	}
	if (by < -0.8f)
	{
		ydiff = 0.02f;
	}
	if (by < -0.75f && (bx < -0.2f + Delta || bx > 0.2f + Delta))
	{
		xdiff = 0;
		ydiff = 0;
	}


	glutPostRedisplay();
	glutTimerFunc(40, OnTick, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("20173262 √÷¿Á¿±");
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutTimerFunc(40, OnTick, 1);
	glutKeyboardFunc(OnKeyboardPressed);
	glutDisplayFunc(OnDrawCall);
	glutMainLoop();
	return 0;
}
