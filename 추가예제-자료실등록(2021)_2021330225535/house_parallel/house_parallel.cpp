
/* Viewing a house with various modeling view and projection */


#include <stdlib.h>
#include <glut.h>
#include <stdio.h>

void house(void)
{
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 54.0);
        glVertex3f(0.0, 10.0, 54.0);
        glVertex3f(8.0, 16.0, 54.0);
        glVertex3f(16.0, 10.0, 54.0);
        glVertex3f(16.0, 0.0, 54.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 30.0);
        glVertex3f(0.0, 10.0, 30.0);
        glVertex3f(8.0, 16.0, 30.0);
        glVertex3f(16.0, 10.0, 30.0);
        glVertex3f(16.0, 0.0, 30.0);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(16.0, 0.0, 54.0);
        glVertex3f(16.0, 0.0, 30.0);
        glVertex3f(16.0, 10.0, 54.0);
        glVertex3f(16.0, 10.0, 30.0);
        glVertex3f(8.0, 16.0, 30.0);
        glVertex3f(8.0, 16.0, 54.0);
        glVertex3f(0.0, 10.0, 54.0);
        glVertex3f(0.0, 10.0, 30.0);
        glVertex3f(0.0, 0.0, 30.0);
        glVertex3f(0.0, 0.0, 54.0);
    glEnd();
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {8.0, 8.0, 70.0}; /* initial viewer location */
static GLdouble vrp[]= {8.0, 8.0, 54.0}; /* initial viewer location */

void display(void)
{

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Update viewer position in modelview matrix */

	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], vrp[0], vrp[1], vrp[2], 0.0, 1.0, 0.0);

/* rotate cube */

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

    house();
    printf_s("x = %f y = %f z = %f\n", viewer[0],viewer[1],viewer[2]);
    printf_s("u = %f v = %f n = %f\n", vrp[0], vrp[1], vrp[2]);
    glFlush();
	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON & state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON & state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON & state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	display();
}

void keys(unsigned char key, int x, int y)
{

/* Use x, X, y, Y, z, and Z keys to move viewer */

   if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   if(key == 'u') vrp[0]-= 1.0;
   if(key == 'U') vrp[0]+= 1.0;
   if(key == 'v') vrp[1]-= 1.0;
   if(key == 'V') vrp[1]+= 1.0;
   if(key == 'n') vrp[2]-= 1.0;
   if(key == 'N') vrp[2]+= 1.0;
   display();
}

void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);

/* Use a perspective view */

 glMatrixMode(GL_PROJECTION); 
 glLoadIdentity();
 glOrtho(-20.0, 20.0, -20.0, 20.0, -100.0, 100.0);

 glMatrixMode(GL_MODELVIEW);
}

void
main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
 glutCreateWindow("colorcube");
 glutReshapeFunc(myReshape);
 glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glEnable(GL_DEPTH_TEST);
 glutMainLoop();
}
