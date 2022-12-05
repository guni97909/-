#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "sgi.h"

#define	WIRE 0		
#define	SHADE 1		
#define	TEX 2		

#define	POINT 0		
#define	LINEAR 1		

#define	NOMIP 1		
#define	MIPNEAREST 2		
#define	MIPLINEAR 3		

#define	CLAMP 0		
#define	REPEAT 1	

#define	DECAL 1		
#define	REPLACE 2		
#define	MODULATE 3		
#define	BLEND 4		

#define PI  3.14159265359
#define	fRadius 10			/* 회전 각도 */

GLfloat mKa[4] = { 0.2f, 0.2f, 0.2f, 0.0f }; /* Object : Ambient */
GLfloat mKd[4] = { 0.6f, 0.6f, 0.6f, 0.0f }; /* Object : Diffuse */
GLfloat mKs[4] = { 0.2f, 0.2f, 0.2f, 0.0f }; /* Object : Specular */
GLfloat mKe[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; /* Object : Emission */
GLfloat shininess[1] = { 50 }; /* Object : Shininess */

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  /* Red diffuse light. */
GLfloat light_position[] = { 1.0, 0.0, 0.0, 0.0 };  /* Infinite light location. */
GLfloat	light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; /* specular light */
GLfloat	light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };  /* ambient light */


typedef struct {
	float x;
	float y;
	float z;
} Point;

typedef struct {
	unsigned long ip[3];
} Face;

int pnum;
int fnum;
Point *mpoint;
Face *mface;

GLfloat angle1 = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat light_angle1 = 0;   /* in degrees */
GLfloat light_angle2 = 0;   /* in degrees */

int status=2;           // WIRE or SHADE  or TEXTURE
int cull=0;             // CULLING toggle 
char *fname="cube.dat";

void MakeSORModel();
void MakeSweepModel();

Point Pos, Dir;
double rads=0.0;
int IsLoad=0;
int BirdEye=0;
int IsFull=0;
int IsSit = 0;

unsigned char * image = NULL;
int iwidth, iheight, idepth;
float scalefactor = 1.0;
int moving;
int trans;
int beginx, beginy;
int light_moving;
int scaling = 0;

GLuint textureId[7];

GLfloat xloc = 0, yloc = 0, zloc = 0;
int w, h;
int filter = 0;
int mode = 1;
int tscale = 1;
int modulate = 1;
int mip = 0;

void InitWalk(void)
{
	Pos.x=-100;
	Pos.y=25;
	Pos.z=0;
}

void InitTexture(void)
{
	glGenTextures(1, &textureId[0]);
	glBindTexture(GL_TEXTURE_2D, textureId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image =read_bmp("sample1.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenTextures(1, &textureId[1]);
	glBindTexture(GL_TEXTURE_2D, textureId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image =read_bmp("sample2.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);    
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId[2]);
	glBindTexture(GL_TEXTURE_2D, textureId[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image =read_bmp("floor1.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId[3]);
	glBindTexture(GL_TEXTURE_2D, textureId[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = read_bmp("wallB.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId[4]);
	glBindTexture(GL_TEXTURE_2D, textureId[4]);
	if (modulate == DECAL) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	else if (modulate == REPLACE) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	else if (modulate == MODULATE) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	}
	glShadeModel(GL_SMOOTH);

	image = read_bmp("star.bmp", &iwidth, &iheight, &idepth);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, iwidth, iheight, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId[5]);
	glBindTexture(GL_TEXTURE_2D, textureId[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = read_bmp("cat.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &textureId[6]);
	glBindTexture(GL_TEXTURE_2D, textureId[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = read_bmp("Entrance.bmp", &iwidth, &iheight, &idepth);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth, iheight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void DrawWire(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
	glEnable (GL_LIGHT2);
	glEnable (GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(1);
	glCallList(2);
	glCallList(3);
	glCallList(4);
	glCallList(5);
	glutSwapBuffers();
}

void DrawShade(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_TEXTURE_2D);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
	glEnable (GL_LIGHT2);
	glEnable (GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(1);
	glCallList(2);
	glCallList(3);
	glCallList(4);
	glCallList(5);
	glutSwapBuffers();
}

void DrawTexture(void)   
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
	glEnable (GL_LIGHT2);
	glEnable (GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
//	glDisable(GL_COLOR_MATERIAL);

	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(1);
	glCallList(2);
	glCallList(3);
	glCallList(4);
	glCallList(5);
	glutSwapBuffers();
}


Point cnormal(Point a, Point b, Point c) //수정 X
{
    Point p, q, r;
    double val;
    p.x = a.x-b.x; p.y = a.y-b.y; p.z = a.z-b.z;
    q.x = c.x-b.x; q.y = c.y-b.y; q.z = c.z-b.z;

    r.x = p.y*q.z - p.z*q.y;
    r.y = p.z*q.x - p.x*q.z;
    r.z = p.x*q.y - p.y*q.x;

    val = sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
    r.x = r.x / val;
    r.y = r.y / val;
    r.z = r.z / val;
    return r;
}

void MakeGL_MyModel(void)
{
	int i;
	Point norm;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mKa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mKd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mKe);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if (glIsList(2)) glDeleteLists(2, 2);
	glNewList(2, GL_COMPILE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureId[2]);

	glTranslatef(170.0, 10.0, -180.0);
	//	glTranslatef(0.0, 10.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	for (i = 0; i < fnum; i++) {
		norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]],
			mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
			mpoint[mface[i].ip[0]].z);
		if (i % 2 == 0) glTexCoord2f(0.0, 1.0);
		else glTexCoord2f(1.0, 1.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
			mpoint[mface[i].ip[1]].z);
		if (i % 2 == 0) glTexCoord2f(1.0, 1.0);
		else glTexCoord2f(1.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
			mpoint[mface[i].ip[2]].z);
		glEnd();
	}

	glPopMatrix();
	glEndList();
}

void MakeGL_MyModelSOR(void)
{
	int i;
	Point norm;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mKa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mKd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mKe);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if (glIsList(3)) glDeleteLists(3, 3);
	glNewList(3, GL_COMPILE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureId[2]);

	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslatef(185.0, 10.0, 180.0);
	//	glTranslatef(0.0, 10.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	for (i = 0; i < fnum; i++) {
		norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]],
			mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
			mpoint[mface[i].ip[0]].z);
		if (i % 2 == 0) glTexCoord2f(0.0, 1.0);
		else glTexCoord2f(1.0, 1.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
			mpoint[mface[i].ip[1]].z);
		if (i % 2 == 0) glTexCoord2f(1.0, 1.0);
		else glTexCoord2f(1.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
			mpoint[mface[i].ip[2]].z);
		glEnd();
	}
	glPopMatrix();

	glEndList();
}



void MakeGL_MyModelSweep(void)
{
	int i;
	Point norm;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mKa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mKd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mKe);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if (glIsList(4)) glDeleteLists(4, 4);
	glNewList(4, GL_COMPILE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureId[2]);

	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslatef(100.0, 50.0, 160.0);
	//	glTranslatef(0.0, 10.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	for (i = 0; i < fnum; i++) {
		norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]],
			mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
			mpoint[mface[i].ip[0]].z);
		if (i % 2 == 0) glTexCoord2f(0.0, 1.0);
		else glTexCoord2f(1.0, 1.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
			mpoint[mface[i].ip[1]].z);
		if (i % 2 == 0) glTexCoord2f(1.0, 1.0);
		else glTexCoord2f(1.0, 0.0);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
			mpoint[mface[i].ip[2]].z);
		glEnd();
	}
	glPopMatrix();

	glEndList();
}

void MakeGL_GLUTModel(void) 
{
	int i;
	Point norm;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mKa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mKd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mKe);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glShadeModel(GL_SMOOTH);

	if (glIsList(2)) glDeleteLists(2, 2);
	glNewList(2, GL_COMPILE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureId[2]);

	glTranslatef(80.0, 10.0, 0.0);
	//glutSolidTeapot(10.0);
	glutSolidSphere(10.0, 50, 50);

	/*	glScalef(0.1,0.1,0.1);
		for (i = 0; i < fnum; i++) {
			norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]],
				mpoint[mface[i].ip[0]]);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 1.0f, 1.0f);

			glNormal3f(norm.x, norm.y, norm.z);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
				mpoint[mface[i].ip[0]].z);
			if (i%2==0) glTexCoord2f(0.0, 1.0);
			else glTexCoord2f(1.0, 1.0);
			glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
				mpoint[mface[i].ip[1]].z);
			if (i % 2 == 0) glTexCoord2f(1.0, 1.0);
			else glTexCoord2f(1.0, 0.0);
			glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
				mpoint[mface[i].ip[2]].z);
			glEnd();
		}
	*/
	glPopMatrix();
	glEndList();
}


void MakeGL_SimpleModel(void)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mKa);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mKd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mKs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mKe);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	if (glIsList(1)) glDeleteLists(1,1);
	glNewList(1, GL_COMPILE);
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, textureId[0]);
	//오른쪽

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glNormal3d(0,0,-1);
		glTexCoord2d(0,0);
   		glVertex3d(-200,0,200);  
		glTexCoord2d(0,1);
		glVertex3d(-200,100,200);
		glTexCoord2d(1,1);
		glVertex3d(200,100,200);
		glTexCoord2d(1,0);
		glVertex3d(200,0,200);
	glEnd();

	//왼쪽
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glNormal3d(0,0,1);
		glTexCoord2d(0,0);
   		glVertex3d(200,0,-200);  
		glTexCoord2d(0,1);
		glVertex3d(200,100,-200);
		glTexCoord2d(1,1);
		glVertex3d(-200,100,-200);
		glTexCoord2d(1,0);
		glVertex3d(-200,0,-200);
	glEnd();
	//뒤
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 0, -200);
	glTexCoord2d(0, 1);
	glVertex3d(-200, 100, -200);
	glTexCoord2d(1, 1);
	glVertex3d(-200, 100, 200);
	glTexCoord2d(1, 0);
	glVertex3d(-200, 0, 200);
	glEnd();

	//앞
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		glNormal3d(1,0,0);
		glTexCoord2d(0,0);
   		glVertex3d(200,0,200);  
		glTexCoord2d(0,1);
		glVertex3d(200,100,200);
		glTexCoord2d(1,1);
		glVertex3d(200,100,-200);
		glTexCoord2d(1,0);
		glVertex3d(200,0,-200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId[1]);

	glShadeModel(GL_SMOOTH);

	if (glIsList(1)) glDeleteLists(1, 1);
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	
	//1
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(200, 0, -110);
	glTexCoord2d(0, 1);
	glVertex3d(200, 100, -110);
	glTexCoord2d(1, 1);
	glVertex3d(-50, 100, -110);
	glTexCoord2d(1, 0);
	glVertex3d(-50, 0, -110);
	glEnd();

	//2
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-50, 0, -80);
	glTexCoord2d(0, 1);
	glVertex3d(-50, 100, -80);
	glTexCoord2d(1, 1);
	glVertex3d(-50, 100, -150);
	glTexCoord2d(1, 0);
	glVertex3d(-50, 0, -150);
	glEnd();

	//2.5
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-50, 70, -200);
	glTexCoord2d(0, 1);
	glVertex3d(-50, 100, -200);
	glTexCoord2d(1, 1);
	glVertex3d(-50, 100, -110);
	glTexCoord2d(1, 0);
	glVertex3d(-50, 70, -110);
	glEnd();
	
	//3
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 0, -130);
	glTexCoord2d(0, 1);
	glVertex3d(-200, 100, -130);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, -130);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, -130);
	glEnd();

	//4
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-110, 0, -130);
	glTexCoord2d(0, 1);
	glVertex3d(-110, 100, -130);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, -100);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, -100);
	glEnd();

	//5
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 0, -100);
	glTexCoord2d(0, 1);
	glVertex3d(-200, 100, -100);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, -100);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, -100);
	glEnd();

	//6
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(200, 0, -30);
	glTexCoord2d(0, 1);
	glVertex3d(200, 100, -30);
	glTexCoord2d(1, 1);
	glVertex3d(-50, 100, -30);
	glTexCoord2d(1, 0);
	glVertex3d(-50, 0, -30);
	glEnd();

	//7
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-110, 0, -70);
	glTexCoord2d(0, 1);
	glVertex3d(-110, 100, -70);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, 0);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, 0);
	glEnd();

	//8
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 0, -10);
	glTexCoord2d(0, 1);
	glVertex3d(-200, 100, -10);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, -10);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, -10);
	glEnd();

	//9
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 0, 0);
	glTexCoord2d(0, 1);
	glVertex3d(-200, 100, 0);
	glTexCoord2d(1, 1);
	glVertex3d(-110, 100, 0);
	glTexCoord2d(1, 0);
	glVertex3d(-110, 0, 0);
	glEnd();

	//10
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-60, 0, 200);
	glTexCoord2d(0, 1);
	glVertex3d(-60, 100, 200);
	glTexCoord2d(1, 1);
	glVertex3d(-60, 100, 30);
	glTexCoord2d(1, 0);
	glVertex3d(-60, 0, 30);
	glEnd();

	//11
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-170, 0, 30);
	glTexCoord2d(0, 1);
	glVertex3d(-170, 100, 30);
	glTexCoord2d(1, 1);
	glVertex3d(-10, 100, 30);
	glTexCoord2d(1, 0);
	glVertex3d(-10, 0, 30);
	glEnd();

	//12
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(160, 0, 200);
	glTexCoord2d(0, 1);
	glVertex3d(160, 100, 200);
	glTexCoord2d(1, 1);
	glVertex3d(160, 100, 100);
	glTexCoord2d(1, 0);
	glVertex3d(160, 0, 100);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId[3]);
	//밑면
	glBegin(GL_POLYGON);
	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(200, 0, 200);
	glTexCoord2d(0, 2);
	glVertex3d(200, 0, -200);
	glTexCoord2d(2, 2);
	glVertex3d(-200, 0, -200);
	glTexCoord2d(2, 0);
	glVertex3d(-200, 0, 200);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId[4]);
	if (mode == CLAMP) {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else {
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (mip == NOMIP) {
		if (filter == POINT) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else if (mip == MIPNEAREST) {
		if (filter == POINT) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else {
		if (filter == POINT) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	if (modulate == DECAL) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}
	else if (modulate == REPLACE) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}
	else if (modulate == MODULATE) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	}
	glShadeModel(GL_SMOOTH);

	if (glIsList(1)) glDeleteLists(1, 1);
	glNewList(1, GL_COMPILE);
	glPushMatrix();

	image = read_bmp("star.bmp", &iwidth, &iheight, &idepth);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, iwidth, iheight, GL_RGB,
		GL_UNSIGNED_BYTE, image);


	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 1, 0);
	glTexCoord2d(0, 0);
	glVertex3d(50, 1, 170);
	glTexCoord2d(1 * tscale, 0);
	glVertex3d(50, 1, 70);
	glTexCoord2d(0, 1 * tscale);
	glVertex3d(-50, 1, 170);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 1, 0);
	glTexCoord2d(1 * tscale, 0);
	glVertex3d(50, 1, 70);
	glTexCoord2d(1 * tscale, 1 * tscale);
	glVertex3d(-50, 1, 70);
	glTexCoord2d(0, 1 * tscale);
	glVertex3d(-50, 1, 170);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId[5]);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(50, 20, -29);
	glTexCoord2d(0, 1);
	glVertex3d(50, 50, -29);
	glTexCoord2d(1, 1);
	glVertex3d(80, 50, -29);
	glTexCoord2d(1, 0);
	glVertex3d(80, 20, -29);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureId[6]);
	glBegin(GL_POLYGON);
	glNormal3d(-1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3d(-200, 1, -200);
	glTexCoord2d(0, 1);
	glVertex3d(-130, 1, -200);
	glTexCoord2d(1, 1);
	glVertex3d(-130, 1, -130);
	glTexCoord2d(1, 0);
	glVertex3d(-200, 1, -130);
	glEnd();

	glPopMatrix();
	glEndList();

}

void GLSetupView(void) {
	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };   // Ambient of the entire scene
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat	light0_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Ambient light 
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  // White diffuse light 
	GLfloat	light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Specular light 
	GLfloat light0_position[] = { 1.0, 1.0, 1.0, 0.0 };  // Infinite light location 

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glEnable(GL_LIGHT0);

	GLfloat	light1_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Ambient light 
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  // White diffuse light 
	GLfloat	light1_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Specular light 
	GLfloat light1_position[] = { -1.0, 1.0, 0.0, 1.0 };  // Point light location 

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5); // 감쇠현상  (Constant: ca)
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);      // 감쇠현상  (Linear: la)
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);   // 감쇠현상  (Quadric: qa)
	glEnable(GL_LIGHT1);

	GLfloat light2_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_position[] = { -2.0, 2.0, 1.0, 1.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);     // 광원 주변광 (Intensity: I0)
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);       // 광원 난반사  (Intensity: I0)
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular); // 광원 정반사  (Intensity: I0)
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);   // 광원 위치      (Position: p)

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5); // 감쇠현상  (Constant: ca)
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);      // 감쇠현상  (Linear: la)
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);   // 감쇠현상  (Quadric: qa)

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction); // 집중광원 방향 (Direction: d)
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);                     // 집중광원 (Falloff: sd)
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);                        // 집중광원 (Cutoff : sc)

	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);
  /* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

  /* Setup the view */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  
	gluPerspective(  40.0, // field of view in degree 
		1.0, // aspect ratio 
		1.0, // Z near 
		2000.0); // Z far 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Dir.x=Pos.x+(fRadius*cos(rads));
	Dir.y = Pos.y;
	Dir.z=Pos.z-(fRadius*sin(rads));

	if (BirdEye==0)  {
		gluLookAt(	Pos.x, Pos.y, Pos.z,
			Dir.x, Dir.y, Dir.z, 
			0.0f,		1.0f,		0.0f);
	}
	else {
		gluLookAt(	Pos.x, Pos.y+1000, Pos.z,
			Dir.x, Dir.y, Dir.z, 
			0.0f,		1.0f,		0.0f);
	}
}



void ReadModel()  
{
	FILE *f1;
	char s[81];

	int i;

	if ((f1 = fopen(fname, "rt"))== NULL) {
		printf("No file\n");
		exit(0);
	}
	fscanf(f1,"%s",s);     printf( "%s", s ); //문자열 "vertex"를 읽는다.
	fscanf(f1,"%s",s);     printf( "%s", s ); //문자열 "="를 읽는다.
	fscanf(f1,"%d",&pnum);     printf( "%d\n", pnum); //VERTEX의 개수를 읽어온다.

    mpoint = (Point*)malloc(sizeof(Point)*pnum);

	for (i=0; i<pnum; i++){
		fscanf(f1,"%f",&mpoint[i].x);   //VERTEX X좌표를 읽는다
		fscanf(f1,"%f",&mpoint[i].y);   //VERTEX Y좌표를 읽는다
		fscanf(f1,"%f",&mpoint[i].z);   //VERTEX Z좌표를 읽는다
	    printf( "%f %f %f\n", mpoint[i].x, mpoint[i].y,mpoint[i].z);
	}

	fscanf(f1,"%s",s);     printf( "%s", s ); //FACE를 읽는다.
	fscanf(f1,"%s",s);     printf( "%s", s ); //문자열 "="를 읽는다.
	fscanf(f1,"%d",&fnum);     printf( "%d\n", fnum);

	mface = (Face*)malloc(sizeof(Face)*fnum);
	for (i=0; i<fnum; i++){
		fscanf(f1,"%d",&mface[i].ip[0]); //1번째 점의 인덱스를 읽는다.
		fscanf(f1,"%d",&mface[i].ip[1]); //2번째 점의 인덱스를 읽는다.
		fscanf(f1,"%d",&mface[i].ip[2]); //3번째 점의 인덱스를 읽는다.
	    printf("%d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}
	fclose(f1);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			trans = 1;
		}
		else {
			moving = 1;
		}
		beginx = x;
		beginy = y;

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
		trans = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		scaling = 1;
		beginx = x;
		beginy = y;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		scaling = 0;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		scaling = 0;
		light_moving = 1;
		beginx = x;
		beginx = y;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		light_moving = 0;
	}
}

void motion(int x, int y)
{
	if (scaling) {
		scalefactor = scalefactor * (1.0 + (beginx - x) * 0.0001);
		glutPostRedisplay();
	}
	if (trans) {
		xloc = xloc + (x - beginx);
		beginx = x;

		yloc = yloc + (beginy - y);
		beginy = y;
		glutPostRedisplay();
	}
	if (moving) {
		angle1 = angle1 + (x - beginx);
		beginx = x;

		angle2 = angle2 + (y - beginy);
		beginy = y;
		glutPostRedisplay();
	}
	if (light_moving) {
		light_angle1 = light_angle1 + (x - beginx);
		beginx = x;

		light_angle2 = light_angle2 + (y - beginy);
		beginy = y;
		glutPostRedisplay();
	}
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLSetupView();
	if (IsLoad==0) {	
		
		ReadModel();
		MakeGL_MyModel();

		
		IsLoad = 1;
	}
	MakeSORModel();
	glutPostRedisplay();
	MakeGL_MyModelSOR();

	MakeSweepModel();
	glutPostRedisplay();
	MakeGL_MyModelSweep();

	MakeGL_SimpleModel();
	if (status==WIRE) DrawWire(); //선구조형상
	else if (status==SHADE) DrawShade(); //쉐이딩
	else DrawTexture();
}

void keyboard(unsigned char key, int x, int y)
{
	printf("key %d\n",key);
	switch (key)
	{
		case 'w':
			status=WIRE;
		    glutPostRedisplay();
			break;
		case 's':
			status=SHADE;
		    glutPostRedisplay();
			break;
		case 't':
			status=TEX;
		    glutPostRedisplay();
			break;
		case 'c':
			if (cull) cull=0;
			else cull=1;
		    glutPostRedisplay();
			break;
		case 'z':
			if (!IsSit) {
				Pos.y = Pos.y / 2;
				Dir.y = Pos.y;
				IsSit = 1;
				glutPostRedisplay();
				
			}
			else {
				Pos.y = Pos.y * 2;
				Dir.y = Pos.y;
				glutPostRedisplay();
				IsSit = 0;
				
			}
			break;
		case 32: //space
			for (int i = 0; i < 20; i++) {
				display();
				Pos.y = Pos.y + 0.1;
				display();
			}
			for (int i = 0; i < 5; i++) {
				display();
				Pos.y = Pos.y - 0.4;
				display();
			}
			break;
		case 'f':
			if (!IsFull) {
				glutFullScreen();
				printf("FullScreen\n");
				IsFull=1;
			}
			else {
				glutPositionWindow(100,100);
				glutReshapeWindow(400,400);
				printf("Window\n");
				IsFull=0;
			}
			break;
		case '1':
			fname="cube.dat";
			ReadModel();
			IsLoad=0;
		    glutPostRedisplay();
			break;
		case '2':
			fname="sphere.dat";	
			ReadModel();
			IsLoad=0;
		    glutPostRedisplay();
			break;
		case '3':
			fname="teapot.dat";
			ReadModel();
			IsLoad=0;
		    glutPostRedisplay();
			break;
		case '4':
			MakeGL_GLUTModel();
			glutPostRedisplay();
			break;
		case '5':
			fname = "chair.dat";
			ReadModel();
			IsLoad = 0; 
			glutPostRedisplay();
			break;
		case 'v':
			if (!BirdEye) BirdEye=1;
			else BirdEye=0;
		    glutPostRedisplay();
			break;
		case 'p':
			if (filter) {
				filter = POINT;
				printf("Point Samping\n");
			}
			else {
				filter = LINEAR;
				printf("Linear Samping\n");
			}
			glutPostRedisplay();
			break;
		case 'r':
			if (mode) {
				mode = CLAMP;
				printf("Texture Clamp\n");
			}
			else {
				mode = REPEAT;
				printf("Texture Repeat\n");
			}
			glutPostRedisplay();
			break;
		case 27:
			exit( EXIT_SUCCESS);
			break;
		case 'h':
			printf("Space :jump\n");
			printf("h ==> Mouse/Key Button Usage\n");
			printf("Left Button : Objet Rotation\n");
			printf("Ctrl + Left Button : Object Translation\n");
			printf("Middle Button : Object Scaling\n");
			printf("Right Button : Light Rotation\n");
			printf("w ==> Wireframe \n");
			printf("s ==> Shading \n");
			printf("t ==> Texture Mapping \n");
			printf("c ==> Culling On/Off\n");
			printf("+ ==> Texture Scale Up\n");
			printf("- ==> Texture Scale Down\n");
			printf("p ==> Point/Linear Samping\n");
			printf("r ==> Texture Clamp/Repeat\n");
			printf("y ==> Texture Mapping: Decal\n");
			printf("u ==> Texture Mapping: Replace\n");
			printf("i ==> Texture Mapping: Modulate\n");
			printf("o ==> Texture Mapping: Blend\n");
			printf(", ==> No Mipmapping\n");
			printf(". ==> Mipmapping: Nearest\n");
			printf("/ ==> Mipmapping: Linear\n");
			glutPostRedisplay();
			break;
		case '+':
			tscale++;
			printf("Texture Scale Up\n");
			glutPostRedisplay();
			break;
		case '-':
			if (tscale < 1) tscale = 1;
			else tscale--;
			printf("Texture Scale Down\n");
			glutPostRedisplay();
			break;
		case ',':
			mip = NOMIP;
			printf("No Mipmapping\n");
			glutPostRedisplay();
			break;
		case '.':
			mip = MIPNEAREST;
			printf("Mipmapping: Nearest\n");
			glutPostRedisplay();
			break;
		case '/':
			mip = MIPLINEAR;
			printf("Mipmapping: Linear\n");
			glutPostRedisplay();
			break;
		case 'y':
			modulate = DECAL;
			printf("Texture Mapping: Decal\n");
			glutPostRedisplay();
			break;
		case 'u':
			modulate = REPLACE;
			printf("Texture Mapping: Replace\n");
			glutPostRedisplay();
			break;
		case 'i':
			modulate = MODULATE;
			printf("Texture Mapping: Modulate\n");
			glutPostRedisplay();
			break;
		case 'o':
			modulate = BLEND;
			printf("Texture Mapping: Blend\n");
			glutPostRedisplay();
			break;
	}
}

void MoveViewer(GLdouble dStep)  
{
	GLdouble xDelta,zDelta;
	xDelta = dStep*cos(rads);
	zDelta = -dStep*sin(rads);
	Pos.x += (float)xDelta;
	Pos.z += (float)zDelta;   
}

void MoveStep(GLdouble dStep)  
{
	GLdouble xDelta,zDelta;
	double frads;
	frads=PI*0.5-rads;
	xDelta = dStep*cos(frads);
	zDelta = dStep*sin(frads);
	Pos.x += (float)xDelta;
	Pos.z += (float)zDelta;
}

int Collision()  //바꿔야함
{
	printf("Pos %f %f %f\n",Pos.x, Pos.y, Pos.z);
	if (Pos.x> 200.0 || Pos.x <-200.0) return 1;
	if (Pos.z> 200.0 || Pos.z <-200.0) return 1;
	if (Pos.x> -50.0 && Pos.x <200.0 && Pos.z > -111.0 && Pos.z < -109.0) return 1; //1
	if (Pos.x> -50.0 && Pos.z > -150 && Pos.z < -80.0) return 1; //2
	if (Pos.x > -200.0 && Pos.x <-110.0 && Pos.z > -131.0 && Pos.z < -129.0) return 1; //3
	if (Pos.x < -110.0 && Pos.z > -130 && Pos.z < -100.0) return 1; //4
	if (Pos.x > -200.0 && Pos.x <-110.0 && Pos.z > -101.0 && Pos.z < -99.0) return 1; //5
	if (Pos.x > -50.0 && Pos.x <200.0 && Pos.z > -31.0 && Pos.z < -29.0) return 1; //6
	if (Pos.x > -111.0 && Pos.x <-109.0 && Pos.z > -70 && Pos.z < -0.0) return 1; //7
	if (Pos.x > -200.0 && Pos.x <-110.0 && Pos.z > -11.0 && Pos.z < -9.0) return 1; //8
	if (Pos.x > -200.0 && Pos.x <-110.0 && Pos.z > -1.0 && Pos.z < 1.0) return 1; //9
	if (Pos.x > -61.0 && Pos.x <-59.0 && Pos.z > 30 && Pos.z < 200.0) return 1; //10
	if (Pos.x > -170.0 && Pos.x <-10.0 && Pos.z > 29.0 && Pos.z < 31.0) return 1; //11
	if (Pos.x > 159.0 && Pos.x < 161.0 && Pos.z > 100 && Pos.z < 200.0) return 1; //12
	return 0;
}

void special(int key, int x, int y) 
{

	switch (key)
	{
		case GLUT_KEY_LEFT : 
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) 
			{
				printf("CTRL \n");
				MoveStep(-2.0);
				if (Collision()) MoveStep(2.5);
			}
			else 
			{
				rads += PI/60.0f; 
				if(rads > (2.0*PI))		
					rads = 0.0;
				printf("Left directional key. \n\n");
			}
			break;


		case GLUT_KEY_RIGHT :
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) 
			{
				printf("CTRL \n");
				MoveStep(2.0);
				if(Collision()) MoveStep(-2.5);
			}
			else 
			{
				printf("Right directional key. \n");
				rads -= PI/60.0; 
				if(rads < 0.0)
					rads = (2.0*PI);	
			}
			break;

		case GLUT_KEY_UP :
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) 
			{
				printf("CTRL \n");
				MoveViewer(4.0);					
				if(Collision()) MoveViewer(-6.0);					
				break;
			}
			else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
			{
				printf("SHIFT \n");
				MoveViewer(1.0);
				if (Collision()) MoveViewer(-1.5);
				break;
			}
			else 
			{
				printf("Up directional key. \n");
				MoveViewer(2.0);					
				if(Collision()) MoveViewer(-2.5);					
				break;
			}
			
		case GLUT_KEY_DOWN :
			if (glutGetModifiers()==GLUT_ACTIVE_CTRL) 
			{
				printf("CTRL \n");
				MoveViewer(-4.0);					
				if(Collision()) MoveViewer(6.0);					
				break;
			}
			else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
			{
				printf("SHIFT \n");
				MoveViewer(-1.0);
				if (Collision()) MoveViewer(1.5);
				break;
			}
			else 
			{
				printf("Down directional key. \n");
				MoveViewer(-2.0);					
				if(Collision()) MoveViewer(2.5);					
				break;
			}
		default :
			printf("Function key. \n");
			break;
	}
	display();
}


void MakeSweepModel() {

	int i;
	int IncAngle = 10;

	pnum = (360 / IncAngle) * 2;
	mpoint = (Point*)malloc(sizeof(Point) * pnum);

	mpoint[0].x = 100;   mpoint[0].y = -100;   mpoint[0].z = 100;
	mpoint[1].x = -100;  mpoint[1].y = 100;  mpoint[1].z = -100;


	for (i = 0; i < pnum - 2; i++) {
		mpoint[i + 2].x = cos(IncAngle * PI / 180) * mpoint[i].x - sin(IncAngle * PI / 180) * mpoint[i].z + 5;
		mpoint[i + 2].y = mpoint[i].y + 10;
		mpoint[i + 2].z = sin(IncAngle * PI / 180) * mpoint[i].x + cos(IncAngle * PI / 180) * mpoint[i].z - 10;
	}

	fnum = 2 * 360 / IncAngle;
	mface = (Face*)malloc(sizeof(Face) * fnum);

	for (i = 0; i < pnum; i += 2) {		// 계산된 점들로 면 구성
		mface[i].ip[0] = i % pnum;
		mface[i].ip[1] = (i + 3) % pnum;
		mface[i].ip[2] = (i + 1) % pnum;

		mface[i + 1].ip[0] = i % pnum;
		mface[i + 1].ip[1] = (i + 1) % pnum;
		mface[i + 1].ip[2] = (i + 3) % pnum;
	}
}

void MakeSORModel()
{
	int i;
	int IncAngle = 10;

	pnum = (360 / IncAngle) * 10;
	mpoint = (Point*)malloc(sizeof(Point) * pnum);

	mpoint[0].x = 100;  mpoint[0].y = -150;  mpoint[0].z = 60;
	mpoint[1].x = 100;  mpoint[1].y = -130;  mpoint[1].z = 60;
	mpoint[2].x = 5;   mpoint[2].y = -5;  mpoint[2].z = 5;
	mpoint[3].x = 5;   mpoint[3].y = 5;  mpoint[3].z = 5;
	mpoint[4].x = 100;   mpoint[4].y = 130;  mpoint[4].z = 60;
	mpoint[5].x = 100;   mpoint[5].y = 150;   mpoint[5].z = 60;

	for (i = 0; i < pnum - 6; i++) {
		mpoint[i + 6].x = cos(IncAngle * PI / 180) * mpoint[i].x - sin(IncAngle * PI / 180) * mpoint[i].z;
		mpoint[i + 6].y = mpoint[i].y;
		mpoint[i + 6].z = sin(IncAngle * PI / 180) * mpoint[i].x + cos(IncAngle * PI / 180) * mpoint[i].z;
	}

	fnum = 10 * 360 / IncAngle;
	mface = (Face*)malloc(sizeof(Face) * fnum);
	int j = 0;

	for (i = 0; i < pnum; i += 10) {

		mface[i].ip[0] = j % pnum;  //면적 0
		mface[i].ip[1] = (j + 1) % pnum;
		mface[i].ip[2] = (j + 6) % pnum;

		mface[i + 1].ip[0] = (j + 1) % pnum;  //면적 1
		mface[i + 1].ip[1] = (j + 7) % pnum;
		mface[i + 1].ip[2] = (j + 6) % pnum;

		mface[i + 2].ip[0] = (j + 1) % pnum;
		mface[i + 2].ip[1] = (j + 2) % pnum;
		mface[i + 2].ip[2] = (j + 7) % pnum;

		mface[i + 3].ip[0] = (j + 2) % pnum;
		mface[i + 3].ip[1] = (j + 8) % pnum;
		mface[i + 3].ip[2] = (j + 7) % pnum;

		mface[i + 4].ip[0] = (j + 2) % pnum;
		mface[i + 4].ip[1] = (j + 3) % pnum;
		mface[i + 4].ip[2] = (j + 8) % pnum;

		mface[i + 5].ip[0] = (j + 9) % pnum;
		mface[i + 5].ip[1] = (j + 3) % pnum;
		mface[i + 5].ip[2] = (j + 8) % pnum;

		mface[i + 6].ip[0] = (j + 3) % pnum;
		mface[i + 6].ip[1] = (j + 4) % pnum;
		mface[i + 6].ip[2] = (j + 9) % pnum;

		mface[i + 7].ip[0] = (j + 4) % pnum;
		mface[i + 7].ip[1] = (j + 10) % pnum;
		mface[i + 7].ip[2] = (j + 9) % pnum;

		mface[i + 8].ip[0] = (j + 4) % pnum;
		mface[i + 8].ip[1] = (j + 5) % pnum;
		mface[i + 8].ip[2] = (j + 10) % pnum;

		mface[i + 9].ip[0] = (j + 5) % pnum;
		mface[i + 9].ip[1] = (j + 11) % pnum;
		mface[i + 9].ip[2] = (j + 10) % pnum;
		j = j + 6;
	}

}

void Myhelp()
{
	printf("Help : Mouse/Key Button Usage\n");
	printf("Left Button : Objet Rotation\n");
	printf("Ctrl + Left Button : Object Translation\n");
	printf("Right Button : Light Rotation\n");
	printf("Directional Key : Objet Rotation\n");
	printf("Ctrl + Directional Key : Object Translation\n");
	printf("Shift + Directional Key : Object Scaling\n");
	printf("w ==> Wireframe \n");
	printf("s ==> Shading \n");
	printf("t ==> Texture Mapping \n");
	printf("c ==> Culling On/Off\n");
	printf("+ ==> Texture Scale Up\n");
	printf("- ==> Texture Scale Down\n");
	printf("p ==> Point/Linear Samping\n");
	printf("r ==> Texture Clamp/Repeat\n");
	printf("1 ==> Texture Mapping: Decal\n");
	printf("2 ==> Texture Mapping: Replace\n");
	printf("3 ==> Texture Mapping: Modulate\n");
	printf("4 ==> Texture Mapping: Blend\n");
	printf(", ==> No Mipmapping\n");
	printf(". ==> Mipmapping: Nearest\n");
	printf("/ ==> Mipmapping: Linear\n");
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Simple Modeling");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	InitWalk();
	InitTexture();
	GLSetupView();
	Myhelp();
	glutMainLoop();
	return 0;            /* ANSI C requires main to return int. */
}

