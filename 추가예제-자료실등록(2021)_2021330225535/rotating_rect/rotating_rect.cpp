/*
 *  rotating_rect.c
 *  This program demonstrates double buffering for 
 *  flicker-free animation.  The left and middle mouse
 *  buttons start and stop the spinning motion of the square.
 */

#include <stdio.h>
#include <glut.h>
#include <math.h>

static GLfloat theta = 0.0;
GLfloat thetar;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		thetar = (theta * (2 * 3.14159)) / 360.0;
		glVertex2f(cos(thetar), sin(thetar));
		glVertex2f(-sin(thetar), cos(thetar));
		glVertex2f(-cos(thetar), -sin(thetar));
		glVertex2f(sin(thetar), -cos(thetar));
	glEnd();
	glFlush();
}

void myinit (void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f (1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
}

void MyTimer(int value)
{
	theta += 2;
	if (theta >= 360.0) theta -= 360.0;
	
	glutTimerFunc(10, MyTimer, 1);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Rotating Rectangle");
    myinit();
	glutDisplayFunc(display); 
    glutTimerFunc(10, MyTimer, 1);
	glutMainLoop();
}

