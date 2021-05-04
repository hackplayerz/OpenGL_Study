#include <glut.h>
#include <gl.h>
#include <glu.h>
#include <math.h>

void InitLight( ){
	GLfloat mat_diffuse[ ] = {0.5, 0.4, 0.3, 1.0};
	GLfloat mat_specular[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[ ] = {0.5, 0.4, 0.3, 1.0};
	GLfloat mat_shininess[ ] = {15.0};
	GLfloat light_specular[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_diffuse[ ] = {0.8, 0.8, 0.8, 1.0};
	GLfloat light_ambient[ ] = {0.3, 0.3, 0.3, 1.0};
	GLfloat light_position[ ] = {-3, 6, 3.0, 0.0};
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

float atx = 5.0, aty = 5.0, atz = 5.0, diff = -0.1;

void MyDisplay( )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	gluLookAt(atx, aty, atz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutSolidTeapot(0.5);
	glFlush();
	glutSwapBuffers();
}

void MyIdle()
{

	
	for (int i = 0; i < 10000000; i++);

    atx += diff;
	aty += diff;
	atz += diff;
	
	if (atx > 5.0) diff = -0.1;
	if (atx < 1.0) diff = 0.1;

	glutPostRedisplay();

}

void MyReshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity( );
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing"); 
	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight( );
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutIdleFunc(MyIdle);
	glutMainLoop( );
	return 0;

}
