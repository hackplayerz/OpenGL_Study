#include <stdlib.h>
#include <glut.h>

GLfloat goldSpecular [] = {0.6283, 0.5558, 0.3661, 1.0};
GLfloat goldDiffuse [] = {0.7516, 0.6065, 0.2265, 1.0};
GLfloat goldAmbient [] = {0.2473, 0.1995, 0.0745, 1.0};
GLfloat goldShininess [] = {51.2};

GLfloat bronzeSpecular [] = {0.2125, 0.1275, 0.054, 0.5};
GLfloat bronzeDiffuse [] = {0.714, 0.4284, 0.18144, 0.5};
GLfloat bronzeAmbient [] = {0.3935, 0.2719, 0.16167, 0.5};
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

GLfloat brassSpecular [] = {0.3294, 0.2235, 0.0275, 1.0};
GLfloat brassDiffuse [] = {0.7804, 0.5686, 0.1137, 1.0};
GLfloat brassAmbient [] = {0.9922, 0.9412, 0.8079, 1.0};
GLfloat brassShininess [] = {27.89};


void display(void) {
  glClearColor(0.1, 0.2, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
  glMaterialfv(GL_FRONT, GL_SHININESS, goldShininess);
  
  glutSolidTeapot(0.575);

  glutSwapBuffers();
}    

void init (void)  {
 GLfloat position [] = {0.0, 0.0, 1.0, 0.0};
 
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
}

void reshape(GLsizei w, GLsizei h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -10, 10); /* rovnobezne promitani */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(250, 250);
  glutCreateWindow("Material");
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
}
















