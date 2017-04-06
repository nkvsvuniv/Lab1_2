#include <GL/glut.h>
#include <math.h>

float angle = 0.0;

float lx = 0.0f, lz = 1.0f;

float x = 20.0f, z = 20.0f;

int deltaX = 0;
int deltaY = 0;

GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
	{ 0, 1, 2, 3 }, { 3, 2, 6, 7 }, { 7, 6, 5, 4 },
	{ 4, 5, 1, 0 }, { 5, 6, 2, 1 }, { 7, 4, 0, 3 } };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void
drawBox(float scale, unsigned int color, int posX, int posY, int posZ, float angleX, float angleY, float angleZ)
{
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
	
	int i;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x*lx, 1.0f, z*lz,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	
	glTranslatef(posX, posY, posZ);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 1.0);
	glScalef(scale, scale, scale);

	for (i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
		
		unsigned int r = (color & 0xFF000000) >> 24;
		unsigned int g = (color & 0x00FF0000) >> 16;
		unsigned int b = (color & 0x0000FF00) >> 8;
		
		glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
		
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void
drawSphere(float scale, unsigned int color, int posX, int posY, int posZ, float angleX, float angleY, float angleZ)
{
	
	int i;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x*lx, 1.0f, z*lz,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);


	glTranslatef(posX, posY, posZ);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 1.0);
	glScalef(scale, scale, scale);

	
		unsigned int r = (color & 0xFF000000) >> 24;
		unsigned int g = (color & 0x00FF0000) >> 16;
		unsigned int b = (color & 0x0000FF00) >> 8;

		glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);

		GLUquadricObj *quadObj;
		quadObj = gluNewQuadric();
		//gluQuadricDrawStyle(quadObj, GLU_FILL); // устанавливаем стиль: сплошной
		gluQuadricDrawStyle(quadObj, GLU_LINE); // устанавливаем стиль: проволочный
		gluSphere(quadObj, 1.3, 10, 10);
		gluDeleteQuadric(quadObj);
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 10.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//
	//glClearColor(0.5f, 0.5f, 0.5f, 0.5f);//
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);
	
}

void drawPyramid(float scale, unsigned int color, int posX, int posY, int posZ, float angleX, float angleY, float angleZ)
{
	
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x*lx, 1.0f, z*lz,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glTranslatef(posX, posY, posZ);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 1.0);
	glScalef(scale, scale, scale);

	unsigned int r = (color & 0xFF000000) >> 24;
	unsigned int g = (color & 0x00FF0000) >> 16;
	unsigned int b = (color & 0x0000FF00) >> 8;
	glBegin(GL_TRIANGLES);
	glColor3f(r/255.0f, g/255.0f, b/255.0f);// Сделали боковую сторону фиолетовой

	glVertex3f(1.0*scale, -1.0*scale, -1.0*scale);
	glVertex3f(1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(0.0*scale, 1.0*scale, 0.0*scale);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);  // Сделали боковую сторону желтой

	glVertex3f(1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(-1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(0.0*scale, 1.0*scale, 0.0*scale);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);// Сделали сторону  розовой

	glVertex3f(-1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(-1.0*scale, -1.0*scale, -1.0*scale);
	glVertex3f(0.0*scale, 1.0*scale, 0.0*scale);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);  // Сделали сторону  светло зеленой

	glVertex3f(-1.0*scale, -1.0*scale, -1.0*scale);
	glVertex3f(1.0*scale, -1.0*scale, -1.0*scale);
	glVertex3f(0.0*scale, 1.0*scale, 0.0*scale);
	glEnd();

	glBegin(GL_QUADS);// основание пирамиды
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f); // сделали основание рыжим

	glVertex3f(1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(-1.0*scale, -1.0*scale, 1.0*scale);
	glVertex3f(-1.0*scale, -1.0*scale, -1.0*scale);
	glVertex3f(1.0*scale, -1.0*scale, -1.0*scale);
	glEnd();
}

void processSpecialKeys(int key, int xx, int yy) {
	
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.1f;
		lx = sin(angle);
		lz = cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
		lx = sin(angle);
		lz = cos(angle);
		break;
	case GLUT_KEY_UP:
		x += 1;
		z += 1;
		break;
	case GLUT_KEY_DOWN:
		x -= 1;
		z -= 1;
		break;
	}
}

void drawCoordinates()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x*lx, 1.0f, z*lz,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	
	glBegin(GL_LINES);
	glPointSize(3.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glPointSize(3.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}


