#include <glut.h>

enum class HeadMenuItems
{
	DrawSphere,
	DrawTorus,
	ChangeSize,
	ChangeColor,
	Exit,

	None
};

enum class SizeMenuItems
{
	Big,
	Small,

	None
};

enum class ColorMenuItems
{
	Red,
	Green,
	Blue,

	None
};

HeadMenuItems HeadMenuState = HeadMenuItems::DrawSphere;
ColorMenuItems ColorMenuState = ColorMenuItems::Red;
SizeMenuItems SizeMenuState = SizeMenuItems::Big;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (ColorMenuState)
	{
		case ColorMenuItems::Red: case ColorMenuItems::None:
			glColor3f(1, 0, 0);
			break;
		case ColorMenuItems::Green:
			glColor3f(0, 1, 0);
			break;
		case ColorMenuItems::Blue:
			glColor3f(0, 0, 1);
			break;
	}

	switch (HeadMenuState)
	{
		case HeadMenuItems::DrawSphere:
			if (SizeMenuState == SizeMenuItems::Big)
			{
				glutWireSphere(0.4, 15, 15);		//큰 원구
			}
			else if (SizeMenuState == SizeMenuItems::Small)
			{
				glutWireSphere(0.2, 15, 15);	  //작은 원구
			}
			break;
		case HeadMenuItems::DrawTorus:
			if (SizeMenuState == SizeMenuItems::Big)
			{
				glutWireTorus(0.2, 0.5, 40, 20);  //큰 원환체
			}
			else if (SizeMenuState == SizeMenuItems::Small)
			{
				glutWireTorus(0.1, 0.3, 40, 20);	//작은 원환체
			}
			break;
		case HeadMenuItems::Exit:    case HeadMenuItems::None:
			exit(0);
	}

	glFlush();
}

void MyMainMenu(const int entryID)
{
	HeadMenuState = static_cast<HeadMenuItems>(entryID);

	glutPostRedisplay();
}

void MySizeMenu(const int entryID)
{
	SizeMenuState = static_cast<SizeMenuItems>(entryID);
	glutPostRedisplay();
}

void MyColorMenu(const int entryID)
{
	ColorMenuState = static_cast<ColorMenuItems>(entryID);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// 색상메뉴 설정.
	GLint MyColorMenuID = glutCreateMenu(MyColorMenu);
	glutAddMenuEntry("Red", static_cast<int>(ColorMenuItems::Red));
	glutAddMenuEntry("Green", static_cast<int>(ColorMenuItems::Green));
	glutAddMenuEntry("Blue", static_cast<int>(ColorMenuItems::Blue));

	// 크기 메뉴 설정.
	GLint MySizeMenuID = glutCreateMenu(MySizeMenu);
	glutAddMenuEntry("Small One", static_cast<int>(SizeMenuItems::Small));
	glutAddMenuEntry("Big One", static_cast<int>(SizeMenuItems::Big));

	// 메인 매뉴 설정.
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Draw Sphere", static_cast<int>(HeadMenuItems::DrawSphere));
	glutAddMenuEntry("Draw Torus", static_cast<int>(HeadMenuItems::DrawTorus));
	glutAddSubMenu("Change Size", MySizeMenuID);
	glutAddSubMenu("Change Color", MyColorMenuID);
	glutAddMenuEntry("Exit", static_cast<int>(HeadMenuItems::Exit));

	glutAttachMenu(GLUT_RIGHT_BUTTON); // 오른쪽 마우스 버튼에 메뉴 열리는 이벤트 바인딩.
	glutDisplayFunc(MyDisplay);
	glutMainLoop();

	return 0;
}