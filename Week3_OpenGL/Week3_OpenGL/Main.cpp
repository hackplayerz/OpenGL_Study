#include <glut.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);

	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_POLYGON);

	glVertex3f(-.5f, -.5f, 0);
	glVertex3f(.5f, -.5f, 0);
	glVertex3f(.5f, .5f, 0);
	glVertex3f(-.5f, .5f, 0);
	
	glEnd();
	glFlush();
}

int main(int argc , char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("그래픽스 실습-2");
	glClearColor(0.3f, 0.3f, 0.3f, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1, 1, -1, 1, -1, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	
	return 0;
}
