
#include <glaux.h>	
#include <glut.h>
#include <glu.h>
#include <stdio.h>

GLfloat xrot=0.9f, yrot=0.8f, zrot=1.0f;
unsigned int MyTextureObject[2];
AUX_RGBImageRec *pTextureImage[2]; //텍스쳐 저장 공간을 가리키는 포인터    

void MyReshape(int w, int h){						
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void MyDisplay( ){								
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP); 
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP); 
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

    glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glutSolidTeapot(1.0);


	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

    glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]);
	glTranslatef(-2.0, 0.0, 0.0);
    glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	//앞면
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	//뒷면
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	//윗면
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	//아랫면
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	//우측면
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	//좌측면
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
	glPopMatrix();

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

int LoadGLTextures(char * szFilePath1, char * szFilePath2){       //파일을 로드하고 텍스쳐로 변환	
    int Status = FALSE;
    glClearColor(0.0, 0.0, 0.0, 0.5);
    memset(pTextureImage, 0, sizeof(void *)*1);        //포인터를 널로 		
	 					//비트맵을 로드하고 오류확인
    if ((pTextureImage[0]=LoadBMP(szFilePath1)) && 
		(pTextureImage[1]=LoadBMP(szFilePath2))){			
        Status=TRUE;				//상태 플랙을 True로
        glGenTextures(2, &MyTextureObject[0]);	//텍스쳐 생성
        glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX, pTextureImage[0]->sizeY,
                    0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


        glBindTexture(GL_TEXTURE_2D, MyTextureObject[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[1]->sizeX, pTextureImage[1]->sizeY,
                    0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[1]->data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }
    return Status;
}

void main(int argc, char * argv[ ]){						
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("OpenGL Sample Program");
        glutDisplayFunc(MyDisplay);
        glutReshapeFunc(MyReshape);
        glutTimerFunc(500,MyTimer,1);
        if(LoadGLTextures("env.bmp", "apple.bmp")){
            glEnable(GL_TEXTURE_2D);
            glShadeModel(GL_SMOOTH);
            glClearDepth(1.0);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
            glutMainLoop( );
        }
}

