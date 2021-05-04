#include <glaux.h>
#include <glut.h>
#include <glu.h>			
#include <stdio.h>
GLfloat xrot=0.9f, yrot=0.8f, zrot=1.0f;
unsigned int MyTextureObject[1];
AUX_RGBImageRec *pTextureImage[1]; //텍스쳐 저장 공간을 가리키는 포인터    

void MyReshape(int w, int h){						
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

GLUquadricObj *t, *h;


void MyDisplay( ){								
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

	glutSolidSphere(1.0, 20, 20);

//	glutSolidTeapot(1.0);
//	glutSolidCone(1.0, 3.0, 10, 10);
//	glutSolidTorus(0.6, 1.0, 10, 10);

//	h=gluNewQuadric();
//  gluQuadricDrawStyle(h, GLU_FILL);
//  t=gluNewQuadric();
//  gluQuadricDrawStyle(t, GLU_FILL);
//  gluCylinder(t, 1.0, 1.0, 2.0,10,10);
//  gluSphere(h,1.0,10,10);

    glutSwapBuffers();
}

void MyTimer(int Value){							
	glRotatef(xrot,1.0f,0.0f,0.0f);	glRotatef(yrot,0.0f,1.0f,0.0f);	glRotatef(zrot,0.0f,0.0f,1.0f);
	glutPostRedisplay( );
	glutTimerFunc(50, MyTimer, 1);
}

AUX_RGBImageRec * LoadBMP(char *szFilename){				
    FILE * pFile = NULL;
    if(!szFilename){
        return NULL;
    }
    fopen_s(&pFile, szFilename,"r");
    if(pFile){
        fclose(pFile);
        return auxDIBImageLoad(szFilename);	     //파일로부터 메모리로 	
    }
    return NULL;
}

int LoadGLTextures(char * szFilePath){       //파일을 로드하고 텍스쳐로 변환	
    int Status = FALSE;


    glClearColor(0.0, 0.0, 0.0, 0.5);
    memset(pTextureImage, 0, sizeof(void *)*1);        //포인터를 널로 		
	 					//비트맵을 로드하고 오류확인
    if (pTextureImage[0]=LoadBMP(szFilePath)){				
        Status=TRUE;				//상태 플랙을 True로
        glGenTextures(1, &MyTextureObject[0]);	//텍스쳐 생성
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
                    0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		float s_plane[4] = { 1, 0, 0, 0 }, t_plane[4] = { 0, 0, 1, 0 };

		glTexGenfv(GL_S, GL_OBJECT_PLANE, s_plane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, t_plane);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

        glEnable(GL_TEXTURE_2D);
    }
    return Status;
}

void main(int argc, char * argv[ ]){						
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("OpenGL Sample Program");
        glutDisplayFunc(MyDisplay);
        glutReshapeFunc(MyReshape);
        glutTimerFunc(500,MyTimer,1);
        if(LoadGLTextures("texture.bmp")){
            glEnable(GL_TEXTURE_2D);
            glShadeModel(GL_SMOOTH);
            glClearDepth(1.0);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
            glutMainLoop( );
        }  
}

