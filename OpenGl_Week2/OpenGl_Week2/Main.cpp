#include <glut.h>

void MyDisplay()
{
	// Clear buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// Gl begin it is pair with glEnd()
	glBegin(GL_POLYGON);

	// Draw vertices, it will be square.
	glVertex3f(-0.5, -0.5, 0);
	glVertex3f(0.5, -0.5, 0);	
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(-0.5, 0.5, 0);

	glEnd();
	// Force execution of GL commands in finite time.
	glFlush();	
}

int main(int argc , char* argv[])
{
	// Initialize graphics library.
	glutInit(&argc, argv);

	// Create graphic window.
	glutCreateWindow("OpenGL Drawing Example");
	// Start display MyDisplay func.
	glutDisplayFunc(MyDisplay);
	// Idle callback.
	glutMainLoop();
	return 0;
}
