#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define	WIRE 0		
#define	SHADE 1	
#define	PI 3.141592

GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat	light_specular[] = {1.0, 1.0, 1.0, 1.0}; /* specular light */
GLfloat	light_ambient[] = {0.3, 0.3, 0.3, 1.0};  /* ambient light */

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

GLfloat anglex = -150;   /* in degrees */
GLfloat angley = -150;   /* in degrees */
GLfloat light_angle = -150;   /* in degrees */

GLfloat xloc = 0, yloc = 0, zloc = 0;
GLfloat viewX = 400, viewY = 400, viewZ = 400;
int moving; 
int beginx, beginy;
int light_moving;
float scalefactor = 1.0;
int scaling = 0;         
int status=0;           // WIRE or SHADE
int cull=0;             // CULLING toggle 
char *fname="cube.dat";
float zoom = 40.0;

void MakeSORModel();
void MakeSweepModel();
void point_change(double pointx, double pointy, double pointz);

void DrawWire(void)
{
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(1);
	glutSwapBuffers();
}

void DrawShade(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(1);
	glutSwapBuffers();
}

Point cnormal(Point a, Point b, Point c)
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

void MakeGL_Model(void)
{
	int i;
	Point norm;
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glRotatef(light_angle, 0.0, 1.0, 0.0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	if (glIsList(1)) glDeleteLists(1,1);			
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glTranslatef(xloc, yloc, zloc);
	glRotatef(anglex, 0.0, 1.0, 0.0);
	glRotatef(angley, 1.0, 0.0, 0.0);
    glScalef(scalefactor, scalefactor, scalefactor);
	for (i = 0; i < fnum; i++) {
		norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]], 
			mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
			mpoint[mface[i].ip[0]].z);
		glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
			mpoint[mface[i].ip[1]].z);
		glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
			mpoint[mface[i].ip[2]].z);
		glEnd();
	}
	glPopMatrix();
	glEndList();
}

void GLSetupRC(void) 
{
  /* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);           // 난반사 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);      // 정반사 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_ambient);       // 주변광 설정
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);       // 조명의 위치 설정
	glEnable(GL_LIGHT0);                          // 설정한 LIGHT0를 사용 가능 
	glEnable(GL_LIGHTING);                     // 설정한 조명들을 켬    glDisable(…): 조명들을 끔

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);       // 깊이 테스트 켬

  /* Setup the view */
  glMatrixMode(GL_PROJECTION);      // 프로젝션 설정
  glLoadIdentity();                                   // 프로젝션 행렬 초기화  단위 행렬로 대치 
  
  gluPerspective(  zoom, // field of view in degree 
  1.0, // aspect ratio 
  1.0, // Z near 
  2000.0); // Z far 
  glMatrixMode(GL_MODELVIEW);         // 시각좌표계 UVN 설정 
  glLoadIdentity();
  gluLookAt(viewX, viewY, viewZ,  // eye is at (0,0,5) 
    0.0, 0.0, 0.0,      // center is at (0,0,0) 
    0.0, 1.0, 0.);      // up is in positive Y direction 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MakeGL_Model();                        // 물체 모델링
	if (status == WIRE) DrawWire();   // 물체 렌더링 (선구조형상)
	else DrawShade();                       // 물체 렌더링 (쉐이딩)
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
	fscanf(f1,"%s",s);     printf( "%s", s );
	fscanf(f1,"%s",s);     printf( "%s", s );
	fscanf(f1,"%d",&pnum);     printf( "%d\n", pnum);

    mpoint = (Point*)malloc(sizeof(Point)*pnum);

	for (i=0; i<pnum; i++){
		fscanf(f1,"%f",&mpoint[i].x);
		fscanf(f1,"%f",&mpoint[i].y);
		fscanf(f1,"%f",&mpoint[i].z);
	    printf( "%f %f %f\n", mpoint[i].x, mpoint[i].y,mpoint[i].z);
	}

	fscanf(f1,"%s",s);     printf( "%s", s );
	fscanf(f1,"%s",s);     printf( "%s", s );
	fscanf(f1,"%d",&fnum);     printf( "%d\n", fnum);

	mface = (Face*)malloc(sizeof(Face)*fnum);
	for (i=0; i<fnum; i++){
		fscanf(f1,"%d",&mface[i].ip[0]);
		fscanf(f1,"%d",&mface[i].ip[1]);
		fscanf(f1,"%d",&mface[i].ip[2]);
	    printf("%d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}
	fclose(f1);
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    moving = 1;
    beginx = x;
	beginy = y;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    moving = 0;
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
	scaling=0;
    light_moving = 1;
	beginx = x;
	beginy = y;
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    light_moving = 0;
  }
}

void motion(int x, int y)
{
  if (scaling) {
    scalefactor = scalefactor * (1.0+ (beginx - x)*0.0001);
    glutPostRedisplay();
  }
  if (moving) {
    anglex = anglex + (x - beginx);
	angley = angley + (beginy - y);
	beginx = x;
	beginy = y;
    glutPostRedisplay();
  }
  if (light_moving) {
    light_angle = light_angle + (x - beginx);
    beginx = x;
	beginy = y;
    glutPostRedisplay();
  }
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
		case 'c':
			if (cull) cull=0;
			else cull=1;
		    glutPostRedisplay();
			break;
		case '1':
			fname="cube.dat";
			ReadModel();
		    glutPostRedisplay();
			break;
		case '2':
			fname="sphere.dat";	
			ReadModel();
		    glutPostRedisplay();
			break;
		case '3':
			fname="teapot.dat";
			ReadModel();
		    glutPostRedisplay();
			break;
		case '4':
			fname = "plane.dat";
			ReadModel();
			glutPostRedisplay();
			break;
		case '5':
			MakeSORModel(); 
			glutPostRedisplay();
			break;
		case '6':
			fname = "chair.dat";
			ReadModel();
			glutPostRedisplay();
			break;
		case '7':
			MakeSweepModel();
			glutPostRedisplay();
			break;
		case 'd':  // x축 이동
			xloc += 20;
			glutPostRedisplay();
			break;
		case 'f':  // x축 이동
			xloc -= 20;
			glutPostRedisplay();
			break;
		case 'g':  // y축 이동
			yloc += 20;
			glutPostRedisplay();
			break;
		case 'h':  // y축 이동 
			yloc -= 20;
			glutPostRedisplay();
			break;
		case 'j':  // z축 이동
			zloc += 20;
			glutPostRedisplay();
			break;
		case 'k':  // z축이동
			zloc -= 20;
			glutPostRedisplay();
			break;		
		case 'n': // 크기 변환
			if (zoom > 0.0)
				zoom++;
			GLSetupRC();
			glutPostRedisplay();
			break;
		case 'm': // 크기 변환
			if (zoom <= 100.0)
				zoom--;
			GLSetupRC();
			glutPostRedisplay();
			break;
		case 'x': //x축으로 시점 전환
			point_change(1, 0, 0);
			glutPostRedisplay();
			break;
		case 'y': //y축으로 시점 전환
			point_change(0, 1, 0);
			glutPostRedisplay();
			break;
		case 'z': //z축으로 시점 전환
			point_change(0, 0, 1);
			glutPostRedisplay();
			break;
		case 'e':   // 회전 x축 +100
			anglex = anglex + 100;
			glutPostRedisplay();
			break;
		case 'r':   // 회전 x축 -100
			anglex = anglex - 100;
			glutPostRedisplay();
			break;
		case 't':   // 회전 y축 +100
			angley = angley + 100;
			glutPostRedisplay();
			break;
		case 'u':   // 회전 y축 -100
			angley = angley - 100;
			glutPostRedisplay();
			break;
		case '27':
			exit(0);
			glutPostRedisplay();
			break;
	}
}

void point_change(double pointx, double pointy, double pointz) {
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, pointx, pointy, pointz);
	glutPostRedisplay();
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

void MakeSweepModel() {

	int i;
	int IncAngle = 10;

	pnum = (360 / IncAngle) * 2;
	mpoint = (Point*)malloc(sizeof(Point) * pnum);

	mpoint[0].x = 100;   mpoint[0].y = -100;   mpoint[0].z = 100;
	mpoint[1].x = -100;  mpoint[1].y = 100;  mpoint[1].z = -100;
	
	
	for (i = 0; i < pnum - 2; i++) {
		mpoint[i + 2].x = cos(IncAngle * PI / 180) * mpoint[i].x - sin(IncAngle * PI / 180) * mpoint[i].z+5;
		mpoint[i + 2].y = mpoint[i].y + 10;
		mpoint[i + 2].z = sin(IncAngle * PI / 180) * mpoint[i].x + cos(IncAngle * PI / 180) * mpoint[i].z -10;
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
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //더블 버퍼 사용 RGB칼라모델 , 깊이 버퍼 사용
	glutCreateWindow("Simple Modeling");
	glutDisplayFunc(display);  // display(): Rendering Loop에서 계속 불림
	glutKeyboardFunc(keyboard);  // keyboard(): 일반 키보드 이벤트처리
	glutMouseFunc(mouse);  // mouse(): 마우스 이벤트 처리
	glutMotionFunc(motion); // motion(): 마우스 포인터 위치(x, y) 움직임 이벤트처리(절대좌표)
	ReadModel(); // ReadModel(): 파일로 부터 물체를 읽어드리는 함수
	GLSetupRC(); // GLSetupRC(): OpenGL을 사용하여 빛설정, 시각좌표계설정, 프로젝트 설정
	glutMainLoop();    
	return 0;             /* ANSI C requires main to return int. */
}

