#include "Render.h"
#include "Projectile.h"
#include "BottomBar.h"

void TimerFunc(const int value)
{
	
}
void DisplayFunc()
{
	
}

void OnKeyboardPressed(const unsigned char KeyPressed, int X, int Y)
{
	
}

int main(int argc , char* argv[])
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
	glutTimerFunc(40, TimerFunc, 1);
	glutKeyboardFunc(OnKeyboardPressed);
	glutDisplayFunc(DisplayFunc);
	glutMainLoop();
	
	glutMainLoop();	
	return 0;
}
