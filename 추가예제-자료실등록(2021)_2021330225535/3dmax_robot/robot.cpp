
/* Robot program (Chapter 8). Cylinder for base, scaled cube for arms */
/* Shows use of instance transformation to define parts (symbols) */
/* The cylinder is a quadric object from the GLU library */
/* The cube is also obtained from GLU */

#include <glut.h>
#include <stdlib.h>

#define GOLD 1
#define BRONZE 2
#define COPPER 3
#define PEWTER 4
#define BRASS 5

#define WHITE	6
#define RED 7
#define YELLOW 8

/* Let's start using #defines so we can better
interpret the constants (and change them) */

#define BASE_HEIGHT 2.0
#define LOWER_ARM_HEIGHT 3.12

typedef float point[3];

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 0;
GLUquadricObj  *p; /* pointer to quadric object */
int material=0;
int light=0;

/* Define the three parts */
/* Note use of push/pop to return modelview matrix
to its state before functions were entered and use
rotation, translation, and scaling to create instances
of symbols (cube and cylinder */

void display_base();
void display_lower_arm();
void display_upper_arm();
void load_texture();
void read_base();
void read_upper_arm();
void read_lower_arm();

void base()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   display_base();
   glPopMatrix();
}

void lower_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   display_lower_arm();
   glPopMatrix();
}

void upper_arm()
{
   glPushMatrix();
   glScalef(1.0, 1.5, 1.0);
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   display_upper_arm();
   glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0, 1.0, 1.0);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    base();
    glTranslatef(0.0, BASE_HEIGHT, 0.0);
    glRotatef(theta[1], 0.0, 0.0, 1.0);
    lower_arm();
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    upper_arm();
    glFlush();
    glutSwapBuffers();
}

void
initLightAndMaterial(void)
{
	GLfloat goldSpecular [] = {0.628281, 0.555802, 0.366065, 1.0};
	GLfloat goldDiffuse [] = {0.75164, 0.60648, 0.22648, 1.0};
	GLfloat goldAmbient [] = {0.24725, 0.1995, 0.0745, 1.0};
	GLfloat goldShininess [] = {51.2};

	GLfloat bronzeSpecular [] = {0.2125, 0.1275, 0.054, 1.0};
	GLfloat bronzeDiffuse [] = {0.714, 0.4284, 0.18144, 1.0};
	GLfloat bronzeAmbient [] = {0.3935, 0.2719, 0.16167, 1.0};
	GLfloat bronzeShininess [] = {25.6};

	GLfloat chromeSpecular [] = {0.25, 0.25, 0.25, 1.0};
	GLfloat chromeDiffuse [] = {0.4, 0.4, 0.4, 1.0};
	GLfloat chromeAmbient [] = {0.7746, 0.7746, 0.7746, 1.0};
	GLfloat chromeShininess [] = {76.8};
 
	GLfloat copperSpecular [] = {0.1913, 0.0735, 0.0225, 1.0};
	GLfloat copperDiffuse [] = {0.7038, 0.2705, 0.0828, 1.0};
	GLfloat copperAmbient [] = {0.2568, 0.1376, 0.0860, 1.0};
	GLfloat copperShininess [] = {12.8};

	GLfloat pewterSpecular [] = {0.1059, 0.0588, 0.1137, 1.0};
	GLfloat pewterDiffuse [] = {0.4275, 0.4706, 0.5412, 1.0};
	GLfloat pewterAmbient [] = {0.3333, 0.3333, 0.5216, 1.0};
	GLfloat pewterShininess [] = {9.85};

	GLfloat whiteSpecular [] =  {0.1, 0.1, 0.1, 1.0};
	GLfloat whiteDiffuse [] =  {0.8, 0.8, 0.8, 1.0};
	GLfloat whiteAmbient [] =  {0.2, 0.2, 0.2, 1.0};
	GLfloat whiteShininess [] = {20.0};

	GLfloat white_ambient[] =  {0.0, 0.0, 0.0, 1.0};
	GLfloat white_diffuse[] =  {1.0, 1.0, 1.0, 1.0};
	GLfloat white_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat white_position[] =  {0.0, 0.0, 20.0, 0.0};

	GLfloat red_ambient[] =  {0.5, 0.5, 0.5, 1.0};
	GLfloat red_diffuse[] =  {1.0, 0.0, 0.0, 1.0};
	GLfloat red_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat red_position[] =  {0.0, 0.0, 20.0, 0.0};

	GLfloat yellow_ambient[] =  {0.5, 0.5, 0.5, 1.0};
	GLfloat yellow_diffuse[] =  {1.0, 1.0, 0.0, 1.0};
	GLfloat yellow_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat yellow_position[] =  {0.0, 0.0, 20.0, 0.0};

	GLfloat ambient[] =  {0.5, 0.0, 0.0, 1.0};
	GLfloat diffuse[] =  {1.0, 1.0, 1.0, 1.0};
	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat position[] =  {90.0, 90.0, 150.0, 0.0};

	GLfloat lmodel_ambient[] = {0.3, 0.3, 0.3, 1.0};


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	if (light == WHITE) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, white_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, white_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, white_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, white_position);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
	}
	else if (light == RED) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, red_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, red_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, red_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, red_position);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
	}
	else if (light == YELLOW) {
		glLightfv(GL_LIGHT0, GL_AMBIENT, yellow_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, yellow_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, yellow_position);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 50);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80);
	}

	if (material == GOLD) {
		glMaterialfv(GL_FRONT, GL_SHININESS, goldShininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
	}
	else if (material == BRONZE) {
		glMaterialfv(GL_FRONT, GL_SHININESS, bronzeShininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmbient);
	}
	else if (material == COPPER) {
		glMaterialfv(GL_FRONT, GL_SHININESS, copperShininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmbient);
	}
	else if (material == PEWTER) {
		glMaterialfv(GL_FRONT, GL_SHININESS, pewterShininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pewterSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pewterDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, pewterAmbient);
	}
	else if (material == WHITE) {
		glMaterialfv(GL_FRONT, GL_SHININESS, whiteShininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
	}

}



void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        theta[axis] += 5.0;
        if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    }
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
    {
        theta[axis] -= 5.0;
        if( theta[axis] < 360.0 ) theta[axis] += 360.0;
    }
    display();
}

void delay(int t)
{
	int i;

	for (i = 0; i < t * 50000000; i++);
}

void animation_example()
{
	for (theta[0] = 0; theta[0] < 60; theta[0] += 5 ) {
		delay(1);
		display();
	}

	for (theta[1] = 0; theta[1] < 60; theta[1] += 5 ) {
		delay(1);
		display();
	}

	for (theta[2] = 0; theta[2] < 60; theta[2] += 5 ) {
		delay(1);
		display();
	}

	for (; theta[0] < 120; theta[0] += 5 ) {
		delay(1);
		display();
	}

	for (; theta[2] > 0; theta[2] -= 5 ) {
		delay(1);
		display();
	}

	for (; theta[1] > 0; theta[1] -= 5 ) {
		delay(1);
		display();
	}
}

void menu(int id)
{
   if(id == 1 ) axis=0;
   if(id == 2) axis=1;
   if(id == 3 ) axis=2;
   if (id == 4) animation_example();
   if (id == 5) {
	   theta[0] = 0;
	   theta[1] = 0;
	   theta[2] = 0;
	   display();
   }
   if (id == 6) {
	   load_texture();
	   glutPostRedisplay();
   }
   if (id == 7) {
	   glDisable(GL_TEXTURE_2D);
	   glutPostRedisplay();
   }
   if(id ==8 ) exit(0);
}


void right_menu(int id)
{

}

void mat_menu(int id)
{

    if(id == 2 ) material=GOLD;
    else if(id == 3) material=BRONZE;
	else if(id == 4) material=COPPER;
	else if(id == 5) material=PEWTER;
	else if(id == 1) material=WHITE;


   initLightAndMaterial();
   glutPostRedisplay();
}

void light_menu(int id)
{

   if(id == 1 ) light=WHITE;
   else if(id == 2) light=RED;
   else if(id == 3) light=YELLOW;

   initLightAndMaterial();
   glutPostRedisplay();
}

void 
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-4.5, 4.5, -0.5, 8.5, -10.0, 10.0);
}

void myinit()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glColor3f(1.0, 0.0, 0.0);

   p=gluNewQuadric(); /* allocate quadric object */
   gluQuadricDrawStyle(p, GLU_FILL); /* render it as wireframe */


   initLightAndMaterial();

	glEnable(GL_DEPTH_TEST);
   
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}

void
main(int argc, char **argv)
{
	int mat_menu_id, light_menu_id;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("base", 1);
    glutAddMenuEntry("lower arm", 2);
    glutAddMenuEntry("upper arm", 3);

	glutAddMenuEntry("Animation Example", 4);
	glutAddMenuEntry("원위치", 5);
	glutAddMenuEntry("텍스쳐맵핑 사용", 6);
	glutAddMenuEntry("텍스쳐맵핑 사용 안함", 7);
    glutAddMenuEntry("quit", 8);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	light_menu_id = glutCreateMenu(light_menu);
	glutAddMenuEntry("백색광", 1);
    glutAddMenuEntry("적색광", 2);
	glutAddMenuEntry("노랑색광", 3);

	mat_menu_id = glutCreateMenu(mat_menu);
	glutAddMenuEntry("White", 1);
	glutAddMenuEntry("Gold", 2);
    glutAddMenuEntry("Bronze", 3);
	glutAddMenuEntry("Copper", 4);
	glutAddMenuEntry("Pewter", 5);


	glutCreateMenu(right_menu);
	glutAddSubMenu("조명", light_menu_id);
	glutAddSubMenu("재질", mat_menu_id);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	read_base();
	read_upper_arm();
	read_lower_arm();

	

    glutMainLoop();
}
