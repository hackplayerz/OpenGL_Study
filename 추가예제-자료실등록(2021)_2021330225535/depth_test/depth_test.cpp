
/* Rotating cube with viewer movement from Chapter 5 */
/* Cube definition and display similar to rotating--cube program */

/* We use the Lookat function in the display callback to point
the viewer, whose position can be altered by the x,X,y,Y,z, and Z keys.
The perspective view is set in the reshape callback */

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>


	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
	{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
	{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

void axes(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(10, 0.0, 0.0);
	glEnd();
    glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(0.0, 10.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void polygon(int a, int b, int c , int d)
{

	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glNormal3fv(normals[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glNormal3fv(normals[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glNormal3fv(normals[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glNormal3fv(normals[d]);
		glVertex3fv(vertices[d]);
	glEnd();


}				

void colorcube()
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
    axes();
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Update viewer position in modelview matrix */

	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* rotate cube */

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	colorcube();

	printf("x = %f y = %f z = %f \n", viewer[0],viewer[1],viewer[2]);

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
   display();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	/* Use a perspective view */

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	if(w<=h) glFrustum(-1.0, 1.0, -1.0 * (GLfloat) h/ (GLfloat) w, 
       1.0* (GLfloat) h / (GLfloat) w, 2.0, 200.0);
	else glFrustum(-1.0, 1.0, -1.0 * (GLfloat) w/ (GLfloat) h, 
       1.0* (GLfloat) w / (GLfloat) h, 2.0, 200.0);

	/* Or we can use gluPerspective */

	//  gluPerspective(45.0, w/h, -10.0, 10.0); */

 glMatrixMode(GL_MODELVIEW);
}

void right_menu(int id)
{
	if (id == 1) glEnable(GL_DEPTH_TEST);
	else if (id == 2) glDisable(GL_DEPTH_TEST);
	else if (id == 3) exit(0);
	display();
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

	glutCreateMenu(right_menu);
    glutAddMenuEntry("hidden surface removal",1);
    glutAddMenuEntry("without hidden surface removal",2);
	glutAddMenuEntry("quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
