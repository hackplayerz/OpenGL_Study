/* Rotating cube with color interpolation */

/* Demonstration of use of homogeneous coordinate 
transformations and simple data structure for representing
cube from Chapter 4 */

/*Both normals and colors are assigned to the vertices */
/*Cube is centered at origin so (unnormalized) normals
are the same as the vertex values */

#include <stdlib.h>
#include <glut.h>
#include <stdio.h>


	GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
	{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

	GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
	{1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
	{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

void polygon(int a, int b, int c , int d)
{

/* draw a polygon via list of vertices */

 	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{

/* map vertices to faces */

	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLfloat theta2[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 10.0}; /* initial viewer location */

void display(void)
{
/* display callback, clear frame buffer and z buffer,
   rotate cube and draw, swap buffers */


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3fv(colors[1]);

	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(5.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 5.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 5.0);
	glEnd();

	glPushMatrix();
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	colorcube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, 5.0, 5.0);
	glRotatef(theta2[0]/5.0, 1.0, 0.0, 0.0);
	glRotatef(theta2[1]/5.0, 0.0, 1.0, 0.0);
	glRotatef(theta2[2]/5.0, 0.0, 0.0, 1.0);
	glScalef(1.0, 2.0, 1.0);
	colorcube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, -5.0, -5.0);
	glRotatef(theta2[0]*2.0, 1.0, 0.0, 0.0);
	glRotatef(theta2[1]*2.0, 0.0, 1.0, 0.0);
	glRotatef(theta2[2]*2.0, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.5, 0.7);
	colorcube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0, 5.0, 5.0);
	glRotatef(theta2[0]/2.0, 1.0, 0.0, 0.0);
	glRotatef(theta2[1]/2.0, 0.0, 1.0, 0.0);
	glRotatef(theta2[2]/2.0, 0.0, 0.0, 1.0);
	glScalef(1.0, 1.5, 1.5);
	colorcube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0, -5.0, -5.0);
	glRotatef(theta2[0], 1.0, 0.0, 0.0);
	glRotatef(theta2[1], 0.0, 1.0, 0.0);
	glRotatef(theta2[2], 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0, 2.0);
	colorcube();
	glPopMatrix();

    glFlush();
	glutSwapBuffers();
}

void spinCube()
{

/* Idle callback, spin cube 2 degrees about selected axis */


	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	theta2[axis] += 4.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	display();
}

void mouse(int btn, int state, int x, int y)
{

/* mouse callback, selects an axis about which to rotate */

	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
}


void keyboard(unsigned char key, int x, int y)
{
   if(key == 'X') viewer[0]-= 1.0;
   if(key == 'x') viewer[0]+= 1.0;
   if(key == 'Y') viewer[1]-= 1.0;
   if(key == 'y') viewer[1]+= 1.0;
   if(key == 'Z') viewer[2]-= 1.0;
   if(key == 'z') viewer[2]+= 1.0;
   if (key == 'd') glutIdleFunc(spinCube);
   if (key == 's') glutIdleFunc(NULL);

   printf("%f %f %f\n", viewer[0], viewer[1], viewer[2]);
   display();
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-12.0, 12.0, -12.0 * (GLfloat) h / (GLfloat) w,
            12.0 * (GLfloat) h / (GLfloat) w, -100.0, 100.0);
    else
        glOrtho(-12.0 * (GLfloat) w / (GLfloat) h,
            12.0 * (GLfloat) w / (GLfloat) h, -12.0, 12.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void
main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glutMainLoop();
}
