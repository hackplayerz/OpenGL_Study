#include <glut.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	// 로컬회전->로컬이동
	glRotatef(45.0, 0, 0, 1);
	glTranslatef(0.6, 0, 0);
	glScalef(1, 2, 1);

	
	glutSolidCube(0.3f);
	glFlush();
}

int main(int argc , char* argv[])
{
	// Initialize graphics windows.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
