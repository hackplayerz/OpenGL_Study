#include <glut.h>

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 800;

void DrawDisplay_Callback();

int main(int argc , char* argv[])
{
	// Initialize glut library.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("그래픽스 실습-2");
	glClearColor(.3f, .3f, .3f, 1.f);
	glMatrixMode(GL_PROJECTION); // 투상 좌표계 선언.
	glLoadIdentity(); // 좌표계 초기화.
	glOrtho(0, WindowWidth, 0, WindowHeight, -1, 1); // 직교투영의 범위를 지정.
	
	glutDisplayFunc(DrawDisplay_Callback);
	glutMainLoop();
	
	return 0;
}



/**
 * @brief 그래픽 윈도우에 그려질 콜백 메서드.
 */
void DrawDisplay_Callback()
{
	// Clear buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, WindowWidth, WindowHeight);
	glColor3f(1.f, 1.f, 1.f);

#pragma region Draw zone
	/** Draw points. */
	glColor3f(0, 1.f, 0);
	glPointSize(3.f);
	glBegin(GL_POINTS);
	glVertex3f(100, 500, 0);
	glVertex3f(200, 500, 0);
	glVertex3f(100, 400, 0);
	glVertex3f(200, 400, 0);
	glEnd();

	/** Draw line. */
	glLineWidth(5.f);
	glColor3f(0, 1.f, 0);
	glBegin(GL_LINES);
	glVertex3f(100, 100, 0);
	glVertex3f(700, 100, 0);
	glEnd();

	/** Draw unfilled square. */
	glColor3f(1.f, 1.f, 0);
	glLineWidth(5.f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(300, 300, 0);
	glVertex3f(700, 300, 0);
	glVertex3f(700, 700, 0);
	glVertex3f(300, 700, 0);
	glEnd();

	/** Draw square polygon. */
	glColor3f(1.f, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(400, 400, 0);
	glVertex3f(600, 400, 0);
	glVertex3f(600, 600, 0);
	glVertex3f(400, 600, 0);
	glEnd();


	// End of Draw zone
#pragma endregion 
	glFlush();
}