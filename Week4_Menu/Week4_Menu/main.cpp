#include<glut.h>

enum class MenuItems
{
    Sphere = 1,
    Torus,
    Teapot,
    Cone,
    Exit,

    NONE
};

MenuItems MenuState = MenuItems::Sphere;

void MyMainMenu(int entryID)
{
    MenuState = static_cast<MenuItems>(entryID);
    glutPostRedisplay();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5f, 0.0f, 0.5f);
    switch (MenuState)
    {
    case MenuItems::Sphere:
        glutWireSphere(0.2, 15, 15);
        break;
    case MenuItems::Torus: 
        glutWireTorus(0.1, 0.3, 40, 20);
        break;
    case MenuItems::Teapot:
        glutWireTeapot(.5);
        break;
    case MenuItems::Cone:
        glutWireCone(.2, .5, 12, 12);
        break;
    case MenuItems::Exit: case MenuItems::NONE:
        exit(0);
    }
    glFlush();
}


int main(int argc, char* argv[])
{
    // Initialize graphics windows.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // 메뉴 콜백 함수 설정
    // 메뉴 항목 정의
    glutAddMenuEntry("Draw Sphere", static_cast<int>(MenuItems::Sphere)); 
    glutAddMenuEntry("Draw Torus", static_cast<int>(MenuItems::Torus));
    glutAddMenuEntry("Draw Teapot", static_cast<int>(MenuItems::Teapot));
    glutAddMenuEntry("Draw Cone", static_cast<int>(MenuItems::Cone));
    glutAddMenuEntry("Exit", static_cast<int>(MenuItems::Exit));
    glutAttachMenu(GLUT_RIGHT_BUTTON);     // 메뉴를 마우스 오른쪽 버튼에 연결
    glutSetMenu(MyMainMenuID);


    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
