
/* Rotating cube with viewer movement from Chapter 5 */
/* Cube definition and display similar to rotating--cube program */

/* We use the Lookat function in the display callback to point
the viewer, whose position can be altered by the x,X,y,Y,z, and Z keys.
The perspective view is set in the reshape callback */

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <string.h>


GLfloat base_vertices[100000][3];
GLint	base_faces[100000][3];
GLfloat base_normals[100000][3];
GLfloat base_face_normals[100000][3];

GLfloat upper_arm_vertices[100000][3];
GLint	upper_arm_faces[100000][3];
GLfloat upper_arm_normals[100000][3];
GLfloat upper_arm_face_normals[100000][3];

GLfloat lower_arm_vertices[100000][3];
GLint	lower_arm_faces[100000][3];
GLfloat lower_arm_normals[100000][3];
GLfloat lower_arm_face_normals[100000][3];


int base_total_vertices = 0;
int base_total_faces = 0;

int upper_arm_total_vertices = 0;
int upper_arm_total_faces = 0;

int lower_arm_total_vertices = 0;
int lower_arm_total_faces = 0;

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

unsigned char *texture_image;
int texture_width, texture_height, bitcount;

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

void compute_upper_arm_normal()
{
	int V0, V1, V2;
	int v, f;

	GLfloat Length, Ax, Ay, Az, Bx, By, Bz, Rx, Ry, Rz;

	long num_normals = 0;	
	
	for(v=0; v < upper_arm_total_vertices; v++)	{
		num_normals = 0;	
		upper_arm_normals[v][0] = 0.0f;
		upper_arm_normals[v][1] = 0.0f;
		upper_arm_normals[v][2] = 0.0f;
		for(f=0; f < upper_arm_total_faces; f++) {
			V0 = upper_arm_faces[f][0]; 
			V1 = upper_arm_faces[f][1];
			V2 = upper_arm_faces[f][2];

			//// V0 ////

			if(v == V0 || v == V1) {
				Ax = upper_arm_vertices[V2][0] - upper_arm_vertices[V1][0];
				Ay = upper_arm_vertices[V2][1] - upper_arm_vertices[V1][1];
				Az = upper_arm_vertices[V2][2] - upper_arm_vertices[V1][2];

				Bx = upper_arm_vertices[V0][0] - upper_arm_vertices[V1][0];
				By = upper_arm_vertices[V0][1] - upper_arm_vertices[V1][1];
				Bz = upper_arm_vertices[V0][2] - upper_arm_vertices[V1][2];

				MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
				MacroNormalize(Length,Rx,Ry,Rz);

				upper_arm_normals[v][0] += Rx;
				upper_arm_normals[v][1] += Ry;
				upper_arm_normals[v][2] += Rz;
				num_normals++;
			}
		}

		upper_arm_normals[v][0] /= (float)num_normals;
		upper_arm_normals[v][1] /= (float)num_normals;
		upper_arm_normals[v][2] /= (float)num_normals;
	}


	for(f=0; f < upper_arm_total_faces; f++) {
		V0 = upper_arm_faces[f][0]; 
		V1 = upper_arm_faces[f][1];
		V2 = upper_arm_faces[f][2];

		Ax = upper_arm_vertices[V2][0] - upper_arm_vertices[V1][0];
		Ay = upper_arm_vertices[V2][1] - upper_arm_vertices[V1][1];
		Az = upper_arm_vertices[V2][2] - upper_arm_vertices[V1][2];

		Bx = upper_arm_vertices[V0][0] - upper_arm_vertices[V1][0];
		By = upper_arm_vertices[V0][1] - upper_arm_vertices[V1][1];
		Bz = upper_arm_vertices[V0][2] - upper_arm_vertices[V1][2];

		MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
		MacroNormalize(Length,Rx,Ry,Rz);

		upper_arm_face_normals[f][0] = Rx;
		upper_arm_face_normals[f][1] = Ry;
		upper_arm_face_normals[f][2] = Rz;
	}
}

void compute_base_normal()
{
	int V0, V1, V2;
	int v, f;

	GLfloat Length, Ax, Ay, Az, Bx, By, Bz, Rx, Ry, Rz;

	long num_normals = 0;	
	
	for(v=0; v < base_total_vertices; v++)	{
		num_normals = 0;	
		base_normals[v][0] = 0.0f;
		base_normals[v][1] = 0.0f;
		base_normals[v][2] = 0.0f;
		for(f=0; f < base_total_faces; f++) {
			V0 = base_faces[f][0]; 
			V1 = base_faces[f][1];
			V2 = base_faces[f][2];

			//// V0 ////

			if(v == V0 || v == V1) {
				Ax = base_vertices[V2][0] - base_vertices[V1][0];
				Ay = base_vertices[V2][1] - base_vertices[V1][1];
				Az = base_vertices[V2][2] - base_vertices[V1][2];

				Bx = base_vertices[V0][0] - base_vertices[V1][0];
				By = base_vertices[V0][1] - base_vertices[V1][1];
				Bz = base_vertices[V0][2] - base_vertices[V1][2];

				MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
				MacroNormalize(Length,Rx,Ry,Rz);

				base_normals[v][0] += Rx;
				base_normals[v][1] += Ry;
				base_normals[v][2] += Rz;
				num_normals++;
			}
		}

		base_normals[v][0] /= (float)num_normals;
		base_normals[v][1] /= (float)num_normals;
		base_normals[v][2] /= (float)num_normals;
	}


	for(f=0; f < base_total_faces; f++) {
		V0 = base_faces[f][0]; 
		V1 = base_faces[f][1];
		V2 = base_faces[f][2];

		Ax = base_vertices[V2][0] - base_vertices[V1][0];
		Ay = base_vertices[V2][1] - base_vertices[V1][1];
		Az = base_vertices[V2][2] - base_vertices[V1][2];

		Bx = base_vertices[V0][0] - base_vertices[V1][0];
		By = base_vertices[V0][1] - base_vertices[V1][1];
		Bz = base_vertices[V0][2] - base_vertices[V1][2];

		MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
		MacroNormalize(Length,Rx,Ry,Rz);

		base_face_normals[f][0] = Rx;
		base_face_normals[f][1] = Ry;
		base_face_normals[f][2] = Rz;
	}
}

void compute_lower_arm_normal()
{
	int V0, V1, V2;
	int v, f;

	GLfloat Length, Ax, Ay, Az, Bx, By, Bz, Rx, Ry, Rz;

	long num_normals = 0;	
	
	for(v=0; v < lower_arm_total_vertices; v++)	{
		num_normals = 0;	
		lower_arm_normals[v][0] = 0.0f;
		lower_arm_normals[v][1] = 0.0f;
		lower_arm_normals[v][2] = 0.0f;
		for(f=0; f < lower_arm_total_faces; f++) {
			V0 = lower_arm_faces[f][0]; 
			V1 = lower_arm_faces[f][1];
			V2 = lower_arm_faces[f][2];

			//// V0 ////

			if(v == V0 || v == V1) {
				Ax = lower_arm_vertices[V2][0] - lower_arm_vertices[V1][0];
				Ay = lower_arm_vertices[V2][1] - lower_arm_vertices[V1][1];
				Az = lower_arm_vertices[V2][2] - lower_arm_vertices[V1][2];

				Bx = lower_arm_vertices[V0][0] - lower_arm_vertices[V1][0];
				By = lower_arm_vertices[V0][1] - lower_arm_vertices[V1][1];
				Bz = lower_arm_vertices[V0][2] - lower_arm_vertices[V1][2];

				MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
				MacroNormalize(Length,Rx,Ry,Rz);

				lower_arm_normals[v][0] += Rx;
				lower_arm_normals[v][1] += Ry;
				lower_arm_normals[v][2] += Rz;
				num_normals++;
			}
		}

		lower_arm_normals[v][0] /= (float)num_normals;
		lower_arm_normals[v][1] /= (float)num_normals;
		lower_arm_normals[v][2] /= (float)num_normals;
	}


	for(f=0; f < lower_arm_total_faces; f++) {
		V0 = lower_arm_faces[f][0]; 
		V1 = lower_arm_faces[f][1];
		V2 = lower_arm_faces[f][2];

		Ax = lower_arm_vertices[V2][0] - lower_arm_vertices[V1][0];
		Ay = lower_arm_vertices[V2][1] - lower_arm_vertices[V1][1];
		Az = lower_arm_vertices[V2][2] - lower_arm_vertices[V1][2];

		Bx = lower_arm_vertices[V0][0] - lower_arm_vertices[V1][0];
		By = lower_arm_vertices[V0][1] - lower_arm_vertices[V1][1];
		Bz = lower_arm_vertices[V0][2] - lower_arm_vertices[V1][2];

		MacroCross(Rx,Ry,Rz,Ax,Ay,Az,Bx,By,Bz);
		MacroNormalize(Length,Rx,Ry,Rz);

		lower_arm_face_normals[f][0] = Rx;
		lower_arm_face_normals[f][1] = Ry;
		lower_arm_face_normals[f][2] = Rz;
	}
}
	
void display_base(void)
{
	int i;

	glBegin(GL_TRIANGLES);
		for (i = 0; i < base_total_faces; i++) {
			glTexCoord2f(0.0, 0.0);
			glNormal3fv(base_normals[base_faces[i][0]]);
			glVertex3fv(base_vertices[base_faces[i][0]]);
			glTexCoord2f(1.0, 0.0);
			glNormal3fv(base_normals[base_faces[i][1]]);
			glVertex3fv(base_vertices[base_faces[i][1]]);
			glTexCoord2f(0.0, 1.0);
			glNormal3fv(base_normals[base_faces[i][2]]);
			glVertex3fv(base_vertices[base_faces[i][2]]);
		
		}
	glEnd();
}

void display_upper_arm(void)
{
	int i;

	glBegin(GL_TRIANGLES);
		for (i = 0; i < upper_arm_total_faces; i++) {
			glTexCoord2f(0.0, 0.0);
			glNormal3fv(upper_arm_normals[upper_arm_faces[i][0]]);
			glVertex3fv(upper_arm_vertices[upper_arm_faces[i][0]]);
			glTexCoord2f(1.0, 0.0);
			glNormal3fv(upper_arm_normals[upper_arm_faces[i][1]]);
			glVertex3fv(upper_arm_vertices[upper_arm_faces[i][1]]);
			glTexCoord2f(0.0, 1.0);
			glNormal3fv(upper_arm_normals[upper_arm_faces[i][2]]);
			glVertex3fv(upper_arm_vertices[upper_arm_faces[i][2]]);
		
		}
	glEnd();
}

void display_lower_arm(void)
{
	int i;

	glBegin(GL_TRIANGLES);
		for (i = 0; i < lower_arm_total_faces; i++) {
			glTexCoord2f(0.0, 0.0);
			glNormal3fv(lower_arm_normals[lower_arm_faces[i][0]]);
			glVertex3fv(lower_arm_vertices[lower_arm_faces[i][0]]);
			glTexCoord2f(1.0, 0.0);
			glNormal3fv(lower_arm_normals[lower_arm_faces[i][1]]);
			glVertex3fv(lower_arm_vertices[lower_arm_faces[i][1]]);
			glTexCoord2f(0.0, 1.0);
			glNormal3fv(lower_arm_normals[lower_arm_faces[i][2]]);
			glVertex3fv(lower_arm_vertices[lower_arm_faces[i][2]]);
		
		}
	glEnd();
}

void readBmpFile(char *fname, unsigned char **image, int *width, int *height, int *bitcount);

void load_texture()
{

	readBmpFile("texture.bmp", &texture_image, &texture_width, &texture_height, &bitcount);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_width, 
        texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glEnable(GL_TEXTURE_2D);
}

void read_base()
{

	char filename[256]="base.asc";
	char buf[1024];
	char kw1[32], kw2[32], kw3[32];
	FILE *fp;
	int n_vertices, n_faces;
	int n;
	float X, Y, Z;
	int A, B, C;
	char *ptr;
	int base;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Can't open %s\n", filename);
		return;
	}
	
	while (fgets(buf, 1024, fp) != NULL) {
		sscanf(buf, "%s %s", kw1, kw2);
		//printf("%s %s\n", kw1, kw2);
		if (strcmp(kw1, "Named") == 0) {
			// Begin a new object
			sscanf(buf, "%s %s %s", kw1, kw2, kw3);
			printf("%s %s %s\n", kw1, kw2, kw3);
		}
		else if (strcmp(kw1, "Tri-mesh,") == 0) {
			sscanf(buf, "%s %s %d %s %d", kw1, kw2, &n_vertices, kw3, &n_faces);
			printf("%s %s = %d %s = %d", kw1, kw2, n_vertices, kw3, n_faces);
		}
		else if (strcmp(kw1, "Vertex") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &X);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Y);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Z);

			//printf("Vertex %d : %f %f %f\n", n, X, Y, Z);
			base_vertices[base_total_vertices][0] = X;
			base_vertices[base_total_vertices][1] = Y;
			base_vertices[base_total_vertices][2] = Z;
			base_total_vertices++;
		}
		// Face list:
		// Face 0: A:0 B:1 C:2 AB:1 BC:1 CA:1
		// Smoothing: 2
		else if (strcmp(kw1, "Vertex") == 0 && (strcmp(kw2, "List:") == 0 || strcmp(kw2, "list:") == 0)) {
			base = base_total_vertices;
			printf("Vertex list:\n");
		}
		else if (strcmp(kw1, "Face") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &A);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &B);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &C);

			base_faces[base_total_faces][0] = A+base;
			base_faces[base_total_faces][1] = B+base;
			base_faces[base_total_faces][2] = C+base;
			base_total_faces++;
		}
	}
	printf("Total vertices = %d\n", base_total_vertices);
	printf("Total faces = %d\n", base_total_faces);

	compute_base_normal();
}

void read_upper_arm()
{

	char filename[256]="upper_arm.asc";
	char buf[1024];
	char kw1[32], kw2[32], kw3[32];
	FILE *fp;
	int n_vertices, n_faces;
	int n;
	float X, Y, Z;
	int A, B, C;
	char *ptr;
	int base;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Can't open %s\n", filename);
		return;
	}
	
	while (fgets(buf, 1024, fp) != NULL) {
		sscanf(buf, "%s %s", kw1, kw2);
		//printf("%s %s\n", kw1, kw2);
		if (strcmp(kw1, "Named") == 0) {
			// Begin a new object
			sscanf(buf, "%s %s %s", kw1, kw2, kw3);
			printf("%s %s %s\n", kw1, kw2, kw3);
		}
		else if (strcmp(kw1, "Tri-mesh,") == 0) {
			sscanf(buf, "%s %s %d %s %d", kw1, kw2, &n_vertices, kw3, &n_faces);
			printf("%s %s = %d %s = %d", kw1, kw2, n_vertices, kw3, n_faces);
		}
		else if (strcmp(kw1, "Vertex") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &X);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Y);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Z);

			//printf("Vertex %d : %f %f %f\n", n, X, Y, Z);
			upper_arm_vertices[upper_arm_total_vertices][0] = X;
			upper_arm_vertices[upper_arm_total_vertices][1] = Y;
			upper_arm_vertices[upper_arm_total_vertices][2] = Z;
			upper_arm_total_vertices++;
		}
		// Face list:
		// Face 0: A:0 B:1 C:2 AB:1 BC:1 CA:1
		// Smoothing: 2
		else if (strcmp(kw1, "Vertex") == 0 && (strcmp(kw2, "List:") == 0 || strcmp(kw2, "list:") == 0)) {
			base = upper_arm_total_vertices;
			printf("Vertex list:\n");
		}
		else if (strcmp(kw1, "Face") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &A);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &B);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &C);

			upper_arm_faces[upper_arm_total_faces][0] = A+base;
			upper_arm_faces[upper_arm_total_faces][1] = B+base;
			upper_arm_faces[upper_arm_total_faces][2] = C+base;
			upper_arm_total_faces++;
		}
	}
	printf("Total vertices = %d\n", upper_arm_total_vertices);
	printf("Total faces = %d\n", upper_arm_total_faces);

	compute_upper_arm_normal();
}

void read_lower_arm()
{

	char filename[256]="lower_arm.asc";
	char buf[1024];
	char kw1[32], kw2[32], kw3[32];
	FILE *fp;
	int n_vertices, n_faces;
	int n;
	float X, Y, Z;
	int A, B, C;
	char *ptr;
	int lower_arm;

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Can't open %s\n", filename);
		return;
	}
	
	while (fgets(buf, 1024, fp) != NULL) {
		sscanf(buf, "%s %s", kw1, kw2);
		//printf("%s %s\n", kw1, kw2);
		if (strcmp(kw1, "Named") == 0) {
			// Begin a new object
			sscanf(buf, "%s %s %s", kw1, kw2, kw3);
			printf("%s %s %s\n", kw1, kw2, kw3);
		}
		else if (strcmp(kw1, "Tri-mesh,") == 0) {
			sscanf(buf, "%s %s %d %s %d", kw1, kw2, &n_vertices, kw3, &n_faces);
			printf("%s %s = %d %s = %d", kw1, kw2, n_vertices, kw3, n_faces);
		}
		else if (strcmp(kw1, "Vertex") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &X);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Y);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%f", &Z);

			//printf("Vertex %d : %f %f %f\n", n, X, Y, Z);
			lower_arm_vertices[lower_arm_total_vertices][0] = X;
			lower_arm_vertices[lower_arm_total_vertices][1] = Y;
			lower_arm_vertices[lower_arm_total_vertices][2] = Z;
			lower_arm_total_vertices++;
		}
		// Face list:
		// Face 0: A:0 B:1 C:2 AB:1 BC:1 CA:1
		// Smoothing: 2
		else if (strcmp(kw1, "Vertex") == 0 && (strcmp(kw2, "List:") == 0 || strcmp(kw2, "list:") == 0)) {
			lower_arm = lower_arm_total_vertices;
			printf("Vertex list:\n");
		}
		else if (strcmp(kw1, "Face") == 0 && kw2[0] >= '0' && kw2[0] <= '9') {
			sscanf(buf, "%s %d", kw1, &n);
			ptr = strchr(buf, ':');
			ptr++;
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &A);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &B);
			ptr = strchr(ptr, ':');
			ptr++;
			sscanf(ptr, "%d", &C);

			lower_arm_faces[lower_arm_total_faces][0] = A+lower_arm;
			lower_arm_faces[lower_arm_total_faces][1] = B+lower_arm;
			lower_arm_faces[lower_arm_total_faces][2] = C+lower_arm;
			lower_arm_total_faces++;
		}
	}
	printf("Total vertices = %d\n", lower_arm_total_vertices);
	printf("Total faces = %d\n", lower_arm_total_faces);

	compute_lower_arm_normal();
}

