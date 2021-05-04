
/* Rotating cube with viewer movement from Chapter 5 */
/* Cube definition and display similar to rotating--cube program */

/* We use the Lookat function in the display callback to point
the viewer, whose position can be altered by the x,X,y,Y,z, and Z keys.
The perspective view is set in the reshape callback */

/* #include <GL/gl.h> */
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <string.h>


GLfloat vertices[100000][3];
GLint	faces[100000][3];
GLfloat normals[100000][3];
GLfloat face_normals[100000][3];
GLfloat tex_coords[100000][2];

int total_vertices = 0;
int total_faces = 0;


GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {10.0, 10.0, 10.0, 1.0};

GLfloat chalkSpecular[] = {0.0, 0.0, 0.0, 1.0};
GLfloat chalkDiffuse[] = {0.75164, 0.0, 0.0, 1.0};
GLfloat chalkAmbient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat chalkShininess[] = {0.0};

GLfloat shineSpecular [] = {0.628281, 0.555802, 0.366065, 1.0};
GLfloat shineDiffuse [] = {0.0, 0.0, 0.0, 1.0};
GLfloat shineAmbient [] = {0.0, 0.0, 0.0, 1.0};
GLfloat shineShininess [] = {50.2};

unsigned char *cloth_image;
int cloth_width, cloth_height, bitcount;
unsigned char *skin_image;
int skin_width, skin_height;

unsigned char *eyelash_image;
int eyelash_width, eyelash_height;

unsigned char *leye_image;
int leye_width, leye_height;

unsigned char *reye_image;
int reye_width, reye_height;

unsigned char *hair_image;
int hair_width, hair_height;
#define MacroNormalizeWeights(Length,Ax,Ay,Az,Aw)\
			((Length=(1.0/(Ax+Ay+Az+Aw))),\
			(Ax *= Length),\
			(Ay *= Length),\
			(Az *= Length),\
			(Aw *= Length))

//...............................................................................
#define MacroMagnitude(Length,Ax,Ay,Az)\
			(Length=(float)(sqrt(Ax*Ax+Ay*Ay+Az*Az)))
//...............................................................................
#define MacroDot(Length,Ax,Ay,Az,Bx,By,Bz)\
			(Length = (Ax*Bx+Ay*By+Az*Bz)) 

//...............................................................................
#define MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz)\
			((Rx = Ay*Bz-Az*By),\
			( Ry = Az*Bx-Ax*Bz),\
			( Rz = Ax*By-Ay*Bx))

#define MacroNormalize(Length,Ax,Ay,Az)\
			((Length=(1.0/(sqrt(Ax*Ax+Ay*Ay+Az*Az)))),\
			(Ax *= Length),\
			(Ay *= Length),\
			(Az *= Length))

void compute_normal()
{
	int V0, V1, V2;
	int v, f;

	GLfloat Length, Ax, Ay, Az, Bx, By, Bz, Rx, Ry, Rz;

	long num_normals = 0;	
	
	for(v=0; v < total_vertices; v++)	{
		num_normals = 0;	
		normals[v][0] = 0.0f;
		normals[v][1] = 0.0f;
		normals[v][2] = 0.0f;
		for(f=0; f < total_faces; f++) {
			V0 = faces[f][0]; 
			V1 = faces[f][1];
			V2 = faces[f][2];

			//// V0 ////

			if(v == V0 || v == V1 || v == V2) {
				Ax = vertices[V2][0] - vertices[V1][0];
				Ay = vertices[V2][1] - vertices[V1][1];
				Az = vertices[V2][2] - vertices[V1][2];

				Bx = vertices[V0][0] - vertices[V1][0];
				By = vertices[V0][1] - vertices[V1][1];
				Bz = vertices[V0][2] - vertices[V1][2];

				MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
				MacroNormalize(Length,Rx,Ry,Rz);

				normals[v][0] += Rx;
				normals[v][1] += Ry;
				normals[v][2] += Rz;
				num_normals++;
			}
		}

		normals[v][0] /= (float)num_normals;
		normals[v][1] /= (float)num_normals;
		normals[v][2] /= (float)num_normals;
	}


	for(f=0; f < total_faces; f++) {
		V0 = faces[f][0]; 
		V1 = faces[f][1];
		V2 = faces[f][2];

		Ax = vertices[V2][0] - vertices[V1][0];
		Ay = vertices[V2][1] - vertices[V1][1];
		Az = vertices[V2][2] - vertices[V1][2];

		Bx = vertices[V0][0] - vertices[V1][0];
		By = vertices[V0][1] - vertices[V1][1];
		Bz = vertices[V0][2] - vertices[V1][2];

		MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
		MacroNormalize(Length,Rx,Ry,Rz);

		face_normals[f][0] = Rx;
		face_normals[f][1] = Ry;
		face_normals[f][2] = Rz;
	}
}

				
void myinit()
{
    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess={100.0};
    GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[]={100.0, 100.0, 100.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glColor3f (1.0, 1.0, 1.0);
    glEnable(GL_NORMALIZE); /* automatic normaization of normals */
    glEnable(GL_CULL_FACE); /* eliminate backfacing polygons */
    glCullFace(GL_BACK); 

}

				
void axes(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(10, 0.0, 0.0);
	glEnd();
    glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(0.0, 10.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
	    glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 25.0, 10.0}; /* initial viewer location */
static GLdouble at[]= {0.0, 25.0, 0.0}; /* initial viewer location */

void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Update viewer position in modelview matrix */

	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2], at[0], at[1], at[2], 0.0, 1.0, 0.0);

/* rotate cube */

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	


	for (i = 0; i < total_faces; i++) {

/*
		if (i == 0) 
			glTexImage2D(GL_TEXTURE_2D, 0, 3, leye_width, 
				leye_height, 0, GL_RGB, GL_UNSIGNED_BYTE, leye_image);
		else if (i == 80) 
			glTexImage2D(GL_TEXTURE_2D, 0, 3, reye_width, 
				reye_height, 0, GL_RGB, GL_UNSIGNED_BYTE, reye_image);
		else if (i == 160) 
			glTexImage2D(GL_TEXTURE_2D, 0, 3, eyelash_width, 
				eyelash_height, 0, GL_RGB, GL_UNSIGNED_BYTE, eyelash_image);
		else if (i == 220) 
			glTexImage2D(GL_TEXTURE_2D, 0, 3, skin_width, 
				skin_height, 0, GL_RGB, GL_UNSIGNED_BYTE, skin_image);
*/
		glBegin(GL_TRIANGLES);
//			glTexCoord2fv(tex_coords[faces[i][0]]);
			glNormal3fv(normals[faces[i][0]]);
			glVertex3fv(vertices[faces[i][0]]);

//			glTexCoord2fv(tex_coords[faces[i][0]]);
			glNormal3fv(normals[faces[i][1]]);
			glVertex3fv(vertices[faces[i][1]]);

//			glTexCoord2fv(tex_coords[faces[i][0]]);
			glNormal3fv(normals[faces[i][2]]);
			glVertex3fv(vertices[faces[i][2]]);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

void readBmpFile(char *fname, unsigned char **image, int *width, int *height, int *bitcount);

void load_texture()
{
	readBmpFile("skin.bmp", &skin_image, &skin_width, &skin_height, &bitcount);
	readBmpFile("leye.bmp", &leye_image, &leye_width, &leye_height, &bitcount);
	readBmpFile("reye.bmp", &reye_image, &reye_width, &reye_height, &bitcount);
	readBmpFile("eyelash.bmp", &eyelash_image, &eyelash_width, &eyelash_height, &bitcount);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

 //   glEnable(GL_TEXTURE_2D);


}

void read_a_model(char *filename)
{

	char buf[1024];
	char kw1[32], kw2[32], kw3[32];
	FILE *fp;
	int n_vertices, n_faces;
	int n;
	float X, Y, Z;
	int A, B, C;
	char *ptr;
	int base;
	int Frames, Frame, num_meshes, num_normals, num_faces;
	int i, flags, MaterialID, num_vertices, j, na, nb, nc, smoothingroup;
	float tu, tv, index;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Can't open %s\n", filename);
		return;
	}
	
	// Check Title
	if(fscanf(fp, " // MilkShape 3D ASCII ") == EOF)
		goto Label_LoadTXT_ERROR;

	// Read in frames, and frame
	if(fscanf(fp, " Frames: %d Frame: %d ",&Frames,&Frame) != 2)
		goto Label_LoadTXT_ERROR;

	// Read in num_meshes
	if(fscanf(fp, " Meshes: %d ", &num_meshes) != 1)
		goto Label_LoadTXT_ERROR;

	//use main menu functions, so set pObject as current.
	//pCurrentlySelectedObject = pObject;

	// Read in all the meshes
	for(i=0;i<num_meshes;i++) 
	{
		//Read mesh name, flags, material id
		if(fscanf(fp, " \"%[^\"]\" %d %d ",buf,&flags,&MaterialID) != 3)
			goto Label_LoadTXT_ERROR;


		if(fscanf(fp, " %d ", &num_vertices) != 1)
			goto Label_LoadTXT_ERROR;

		base = total_vertices;

		for(j=0;j < num_vertices;j++)
		{
			if(fscanf(fp, " %d %f %f %f %f %f %d ",
					  &flags,
					  &X,
					  &Y,
					  &Z,
					  &tu,
					  &tv,
					  &index) != 7)
			{
				goto Label_LoadTXT_ERROR;
			}

			vertices[total_vertices][0] = X;
			vertices[total_vertices][1] = Y;
			vertices[total_vertices][2] = Z;
			tex_coords[total_vertices][0] = tu;
			tex_coords[total_vertices][1] = tv;
			total_vertices++;
		}

		if(fscanf(fp," %d ",&num_normals)!=1)
			goto Label_LoadTXT_ERROR;

		for(j=0;j<num_normals;j++)
		{
			if(fscanf(fp," %f %f %f ",&X,&Y,&Z) != 3)
			{
				goto Label_LoadTXT_ERROR;
			}
		}

		if(fscanf(fp, " %d ", &num_faces) != 1)
			goto Label_LoadTXT_ERROR;



		for(j=0;j<num_faces;j++)
		{
			if(fscanf(fp, " %d %d %d %d %d %d %d %d ",
					  &flags,
					  &A,
					  &B,
					  &C,
					  &na,
					  &nb,
					  &nc,
					  &smoothingroup) != 8)
			{
				goto Label_LoadTXT_ERROR;
			}

			faces[total_faces][0] = A+base;
			faces[total_faces][1] = B+base;
			faces[total_faces][2] = C+base;
			total_faces++;
		}
	}

	printf("Total vertices = %d\n", total_vertices);
	printf("Total faces = %d\n", total_faces);

	compute_normal();
	load_texture();

	//Clean Exit
	fclose(fp);
	return ;

	//Error Exit
	Label_LoadTXT_ERROR:;
	fclose(fp);

	return;
}


void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
	display();
}

void keys(unsigned char key, int x, int y)
{

/* Use x, X, y, Y, z, and Z keys to move viewer */

   if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   if(key == 'q') at[0]-= 1.0;
   if(key == 'Q') at[0]+= 1.0;
   if(key == 'w') at[1]-= 1.0;
   if(key == 'W') at[1]+= 1.0;
   if(key == 'e') at[2]-= 1.0;
   if(key == 'E') at[2]+= 1.0;

   display();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);

	/* Use a perspective view */

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	//if(w<=h) glFrustum(-1.0, 1.0, -1.0 * (GLfloat) h/ (GLfloat) w, 
    //   1.0* (GLfloat) h / (GLfloat) w, 2.0, 200.0);
	//else glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 
    //   2.0* (GLfloat) w / (GLfloat) h, 2.0, 200.0);

	/* Or we can use gluPerspective */

	gluPerspective(90.0, w/h, 2.0, 2000.0); 

	glMatrixMode(GL_MODELVIEW);
}

void right_menu(int id)
{
	if (id == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, chalkSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chalkDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, chalkAmbient);
		glMaterialfv(GL_FRONT, GL_SHININESS, chalkShininess);
	}
	else if (id == 2) {
			
		glMaterialfv(GL_FRONT, GL_SPECULAR, shineSpecular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shineDiffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, shineAmbient);
		glMaterialfv(GL_FRONT, GL_SHININESS, shineShininess);
	}
	else if (id == 3) exit(0);
	display();

}

void
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);

	myinit();

	glutCreateMenu(right_menu);
    glutAddMenuEntry("Diffuse light",1);
    glutAddMenuEntry("Specular Light",2);
	glutAddMenuEntry("quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	read_a_model("face5.txt");

	glutMainLoop();
}
