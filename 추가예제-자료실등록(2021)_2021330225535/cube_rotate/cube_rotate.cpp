#include <glut.h>

GLfloat theta = 0.0;

void spinCube(int value)
{

	/* Idle callback, spin cube 2 degrees about selected axis */
	theta += 2.0;
	if( theta > 360.0 ) theta -= 360.0;
	
	/* display(); */
	glutPostRedisplay();
	glutTimerFunc(100, spinCube, 0);
}

void MyDisplay( ){					
    glClear(GL_COLOR_BUFFER_BIT);	
    glViewport(0, 0, 300, 300);	
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);				
    glLoadIdentity( );				
	
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(5.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 5.0, 0.0);
	glEnd();

    glTranslatef(0.6, 0.0, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, 0.0, 0.0);				
    glTranslatef(0.6, 0.0, 0.0);					
    glutSolidCube(0.3);						
    glFlush( ); 				
}				

int main(int argc, char** argv) {
    glutInit(&argc,argv); 				
    glutInitDisplayMode(GLUT_RGBA); 		
    glutInitWindowSize(300, 300);    			
    glutInitWindowPosition(0, 0); 	
    glutCreateWindow("OpenGL Sample Drawing"); 
    glClearColor (1.0, 1.0, 1.0, 1.0);		
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity( );    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  		
    glutDisplayFunc(MyDisplay); 
	glutTimerFunc(100, spinCube, 0);	
    glutMainLoop( );					
    return 0;		
}

