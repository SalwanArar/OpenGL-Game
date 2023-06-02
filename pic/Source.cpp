/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
#include<cmath>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma warning (disable:4996)
GLuint texturee[8];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1500.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


/*
GLuint loadBMP_custom(const char * imagepath, bool render)
{
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
unsigned char * data;// Actual RGB data

// Open the file
FILE * file = fopen(imagepath, "rb");
if (!file) { printf("Image could not be opened\n"); return 0; }

if (fread(header, 1, 54, file) != 54)
{ // If not 54 bytes read : problem
printf("Not a correct BMP file\n");
return false;
}
if (header[0] != 'B' || header[1] != 'M') {
printf("Not a correct BMP file\n");
return 0;
}
// Read ints from the byte array
dataPos = *(int*)&(header[0x0A]);
imageSize = *(int*)&(header[0x22]);
width = *(int*)&(header[0x12]);
height = *(int*)&(header[0x16]);

// Some BMP files are misformatted, guess missing information
if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

// Create a buffer
data = new unsigned char[imageSize];

// Read the actual data from the file into the buffer
fread(data, 1, imageSize, file);

//Everything is in memory now, the file can be closed
fclose(file);

GLuint textureID; 	// Create one OpenGL texture
glGenTextures(1, &textureID); 	// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, textureID); 	// Give the image to OpenGL
if (render)
{
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
else
{
gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
return textureID;
}
*/
unsigned char* loadImage(char* filename, int w, int h)
{
	ifstream inf(filename, ios::binary);
	char dummy[54];
	inf.read(dummy, 54);
	unsigned char* data = new  unsigned char[w * h * 3];
	inf.read((char*)data, w * h * 3);
	for (int i = 0; i < w * h * 3; i += 3)
	{
		unsigned char buf = data[i];
		data[i] = data[i + 2];
		data[i + 2] = buf;
	}
	return data;
}
unsigned int width, height;
void loadTexture8(bool render)
{
	unsigned char* data = loadImage("ss.bmp", 2048, 1536);

	glBindTexture(GL_TEXTURE_2D, 9);

	if (render)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2048, 1536, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);

	delete[] data;
}

void loadTexture11()
{
	unsigned char* data = loadImage("snowtree.bmp", 878, 840);

	glBindTexture(GL_TEXTURE_2D, 16);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 878, 840, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);

	delete[] data;
}


void loadTexture10()
{
	unsigned char* data = loadImage("snow.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 11);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture()
{
	unsigned char* data = loadImage("k.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}
void loadTexture12()
{
	unsigned char* data = loadImage("stone2.bmp", 225, 225);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 28);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 225, 225, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture20()
{
	unsigned char* data = loadImage("stone.bmp", 355, 142);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 20);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 355, 142, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture1()
{
	unsigned char* data = loadImage("test2.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture2()
{
	unsigned char* data = loadImage("test3.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture3()
{
	unsigned char* data = loadImage("test4.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture4()
{
	unsigned char* data = loadImage("test5.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture5()
{
	unsigned char* data = loadImage("test6.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 6);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}


void loadTexture6()
{
	unsigned char* data = loadImage("test7.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 7);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

void loadTexture7()
{
	unsigned char* data = loadImage("test8.bmp", 256, 256);
	glEnable(GL_TEXTURE_2D);
	//glGenTextures
	glBindTexture(GL_TEXTURE_2D, 8);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	delete[] data;
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	loadTexture();	// Really Nice Perspective Calculations
	loadTexture1();
	loadTexture2();
	loadTexture3();
	loadTexture4();
	loadTexture5();
	loadTexture6();
	loadTexture7();	// Really Nice Perspective Calculations
	loadTexture8(1);
	loadTexture10();
	loadTexture11();
	loadTexture20();
	loadTexture12();
	return TRUE;										// Initialization Went OK
}

bool score = false;
bool score1 = false;
bool score2 = false;
bool score3 = false;
bool score4 = false;
bool score5 = false;
bool score6 = false;
bool score7 = false;


float PI = 3.1415926535897932384626433832795;
float x = 0, y = 0, z = 0;
float lx = 0, ly = 0, lz = -3.8;
float th = 0, th1 = 0;
static double cx = -34, cy = 0, cz = 48, ca, cup;
static float xup = 0, yup = 0;
static float bx, by, bz;
static float bvx, bvy, bvz;
float counter = 0;
static float gf;
bool jump = false;
static bool fire = false;
static bool goal_1 = true,
goal_2 = true,
goal_3 = true,
goal_4 = true,
goal_5 = true,
goal_6 = true,
goal_7 = true,
goal_8 = true,
goal_9 = true,
goal_10 = true;
bool tt = false,
tt1 = false,
tt2 = false,
tt3 = false,
tt4 = false,
tt5 = false,
tt6 = false,
tt7 = false;
bool d1 = true,
d2 = true,
d3 = true,
d4 = true,
d5 = true,
d6 = true,
d7 = true,
d8 = true,
d9 = true;
bool mov_w = true,
mov_s = true,
mov_d = true,
mov_a = true;
bool SSMAN = true;
double r = 0;


int shape(int n, float radius1, float radius2, float H1, float H2)
{
	glBegin(GL_TRIANGLE_STRIP);
	float header;
	for (int i = 0; i <= n; i++)
	{
		header = 2 * PI * i / n;
		//glColor3f(0, 0.6, 0.9);
		glNormal3f(cos(header) * radius1, H1, sin(header) * radius1);
		glVertex3f(cos(header) * radius1, H1, sin(header) * radius1);
		//glColor3f(1, 0.5, 0.3);
		glNormal3f(cos(header) * radius2, H2, sin(header) * radius2);
		glVertex3f(cos(header) * radius2, H2, sin(header) * radius2);
	}
	glEnd();
	return TRUE;
}
int ball(int n, float v)
{
	for (int i = 0; i < n; i++)
	{
		float header1 = 2 * PI * i / n;
		float header2 = 2 * PI * (i + 1) / n;
		shape(n, sin(header1) * v, sin(header2) * v, cos(header1) * v, cos(header2) * v);
	}
	return TRUE;
}
int cube()
{
	float p1[] = { -1, -1, 1 };
	float p2[] = { 1, -1, 1 };
	float p3[] = { 1, -1, -1 };
	float p4[] = { -1, -1, -1 };
	float p5[] = { -1, 1, 1 };
	float p6[] = { 1, 1, 1 };
	float p7[] = { 1, 1, -1 };
	float p8[] = { -1, 1, -1 };

	glBegin(GL_QUADS);
	//first face
	//glColor3f(0.2, 0.9, 1);
	glNormal3f(0, 0, 1);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p6);
	glVertex3fv(p5);

	//sec face
	glNormal3f(1, 0, 0);
	//glColor3f(0.8, 0.3, 0.5);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p7);
	glVertex3fv(p6);

	//third face
	glNormal3f(0, 0, -1);
	//glColor3f(0.9, 0.9, 0.3);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p8);
	glVertex3fv(p7);

	//4th face
	glNormal3f(-1, 0, 0);
	//glColor3f(0.5, 0.3, 0.5);
	glVertex3fv(p1);
	glVertex3fv(p4);
	glVertex3fv(p8);
	glVertex3fv(p5);

	//up face
	glNormal3f(0, 1, 0);
	//glColor3f(0.5, 0.8, 0);
	glVertex3fv(p5);
	glVertex3fv(p6);
	glVertex3fv(p7);
	glVertex3fv(p8);

	//down face
	glNormal3f(0, -1, 0);
	//glColor3f(0.9, 0.5, 0.1);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);

	glEnd();
	return TRUE;
}
void Floor()
{

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 11);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3d(1, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3d(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3d(-1, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3d(-1, 0, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);




}
int circul(int n, float radius, float H)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i <= n; i++)
	{
		float header = 2 * PI * i / n;
		glNormal3d(cos(header) * radius, H, sin(header) * radius);
		glVertex3d(cos(header) * radius, H, sin(header) * radius);
	}
	glEnd();
	return TRUE;
}
void tree()
{
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	GLUquadric* quadric = gluNewQuadric();
	glColor3d(0.4, 0.2, 0);
	gluCylinder(quadric, 0.5, 0.5, 2, 32, 16);
	//shape(30, 0.5, 0.5, 0, 2);

	glColor3d(0, 0.6, 0.2);
	glTranslated(0, 0, 1.9);
	gluCylinder(quadric, 4, 0, 1.8, 32, 16);
	gluCylinder(quadric, 4, 0, 0, 32, 16);
	//shape(30, 0, 4, 3.7, 1.9);
	//circul(30, 4, 1.9);
	glTranslated(0, 0, 1.7);
	gluCylinder(quadric, 3, 0, 1.5, 32, 16);
	gluCylinder(quadric, 3, 0, 0, 32, 16);
	//shape(30, 0, 3, 5, 3.5);
	//circul(30, 3, 3.5);
	glTranslated(0, 0, 1.4);
	gluCylinder(quadric, 2, 0, 1.7, 32, 16);
	gluCylinder(quadric, 2, 0, 0, 32, 16);
	//shape(30, 0, 2, 6.5, 4.8);
	//circul(30, 2, 4.8);
	glPopMatrix();
}
void stone()
{
	float p1[] = { -1, -1, 1 };
	float p2[] = { 1, -1, 1 };
	float p3[] = { 1, -1, -1 };
	float p4[] = { -1, -1, -1 };
	float p5[] = { -1, 1, 1 };
	float p6[] = { 1, 1, 1 };
	float p7[] = { 1, 1, -1 };
	float p8[] = { -1, 1, -1 };


	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 20);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glBegin(GL_QUADS);

	//first face
	glNormal3f(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3fv(p1);
	glTexCoord2d(1, 0);
	glVertex3fv(p2);
	glTexCoord2d(1, 1);
	glVertex3fv(p6);
	glTexCoord2d(0, 1);
	glVertex3fv(p5);

	//sec face
	glNormal3f(1, 0, 0);
	glTexCoord2d(0, 0);
	glVertex3fv(p2);
	glTexCoord2d(1, 0);

	glVertex3fv(p3);
	glTexCoord2d(1, 1);

	glVertex3fv(p7);
	glTexCoord2d(0, 1);

	glVertex3fv(p6);

	//third face
	glNormal3f(0, 0, -1);
	glTexCoord2d(0, 0);

	glVertex3fv(p3);
	glTexCoord2d(1, 0);

	glVertex3fv(p4);
	glTexCoord2d(1, 1);

	glVertex3fv(p8);
	glTexCoord2d(0, 1);

	glVertex3fv(p7);

	//4th face
	glNormal3f(-1, 0, 0);
	glTexCoord2d(0, 0);

	glVertex3fv(p1);
	glTexCoord2d(1, 0);

	glVertex3fv(p4);
	glTexCoord2d(1, 1);

	glVertex3fv(p8);
	glTexCoord2d(0, 1);

	glVertex3fv(p5);

	//up face
	glNormal3f(0, 1, 0);
	glTexCoord2d(0, 0);

	glVertex3fv(p5);
	glTexCoord2d(1, 0);

	glVertex3fv(p6);
	glTexCoord2d(1, 1);

	glVertex3fv(p7);
	glTexCoord2d(0, 1);

	glVertex3fv(p8);

	//down face
	glNormal3f(0, -1, 0);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glDisable(GL_TEXTURE_2D);
	glEnd();
}


void stone1()
{
	float p1[] = { -1, -1, 1 };
	float p2[] = { 1, -1, 1 };
	float p3[] = { 1, -1, -1 };
	float p4[] = { -1, -1, -1 };
	float p5[] = { -1, 1, 1 };
	float p6[] = { 1, 1, 1 };
	float p7[] = { 1, 1, -1 };
	float p8[] = { -1, 1, -1 };


	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 23);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glBegin(GL_QUADS);

	//first face
	glNormal3f(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3fv(p1);
	glTexCoord2d(1, 0);
	glVertex3fv(p2);
	glTexCoord2d(1, 1);
	glVertex3fv(p6);
	glTexCoord2d(0, 1);
	glVertex3fv(p5);

	//sec face
	glNormal3f(1, 0, 0);
	glTexCoord2d(0, 0);

	glVertex3fv(p2);
	glTexCoord2d(1, 0);

	glVertex3fv(p3);
	glTexCoord2d(1, 1);

	glVertex3fv(p7);
	glTexCoord2d(0, 1);

	glVertex3fv(p6);

	//third face
	glNormal3f(0, 0, -1);
	glTexCoord2d(0, 0);

	glVertex3fv(p3);
	glTexCoord2d(1, 0);

	glVertex3fv(p4);
	glTexCoord2d(1, 1);

	glVertex3fv(p8);
	glTexCoord2d(0, 1);

	glVertex3fv(p7);

	//4th face
	glNormal3f(-1, 0, 0);
	glTexCoord2d(0, 0);

	glVertex3fv(p1);
	glTexCoord2d(1, 0);

	glVertex3fv(p4);
	glTexCoord2d(1, 1);

	glVertex3fv(p8);
	glTexCoord2d(0, 1);

	glVertex3fv(p5);

	//up face
	glNormal3f(0, 1, 0);
	glTexCoord2d(0, 0);

	glVertex3fv(p5);
	glTexCoord2d(1, 0);

	glVertex3fv(p6);
	glTexCoord2d(1, 1);

	glVertex3fv(p7);
	glTexCoord2d(0, 1);

	glVertex3fv(p8);

	//down face
	glNormal3f(0, -1, 0);
	glTexCoord2d(0, 0);
	glVertex3fv(p1);
	glTexCoord2d(1, 0);
	glVertex3fv(p2);
	glTexCoord2d(1, 1);
	glVertex3fv(p3);
	glTexCoord2d(0, 1);
	glVertex3fv(p4);
	glDisable(GL_TEXTURE_2D);
	glEnd();
}


void gift()
{
	glPushMatrix();
	glRotatef(gf, 0, 1, 0);
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(-0.2, 1, 1);
	glVertex3f(-0.2, -1, 1);
	glVertex3f(-1, -1, 1);

	glVertex3f(0.2, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(0.2, -1, 1);

	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, -0.2);
	glVertex3f(0.2, -1, -0.2);
	glVertex3f(0.2, -1, -1);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0.2);
	glVertex3f(1, -1, 0.2);
	glVertex3f(1, -1, 1);

	glVertex3f(1, 1, -0.2);
	glVertex3f(1, -1, -0.2);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);

	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(0.2, -1, -1);
	glVertex3f(0.2, 1, -1);

	glVertex3f(-1, 1, 0.2);
	glVertex3f(-1, -1, 0.2);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);

	glVertex3f(-0.2, 1, -1);
	glVertex3f(-0.2, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);

	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, -0.2);
	glVertex3f(-1, 1, -0.2);

	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0.2);
	glVertex3f(0.2, 1, 0.2);
	glVertex3f(0.2, 1, 1);

	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, 0.2);
	glVertex3f(0.2, -1, 0.2);
	glVertex3f(0.2, -1, 1);

	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, 0.2);
	glVertex3f(-0.2, 1, 0.2);
	glVertex3f(-0.2, 1, 1);

	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, 0.2);
	glVertex3f(-0.2, -1, 0.2);
	glVertex3f(-0.2, -1, 1);

	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, -0.2);
	glVertex3f(-0.2, 1, -0.2);
	glVertex3f(-0.2, 1, -1);

	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, -0.2);
	glVertex3f(-0.2, -1, -0.2);
	glVertex3f(-0.2, -1, -1);

	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, -0.2);
	glVertex3f(0.2, 1, -0.2);
	glVertex3f(0.2, 1, -1);

	glColor3f(1, 0, 0);
	glVertex3f(-0.2, 1, 1);
	glVertex3f(0.2, 1, 1);
	glVertex3f(0.2, -1, 1);
	glVertex3f(-0.2, -1, 1);

	glVertex3f(1, 1, 0.2);
	glVertex3f(1, -1, 0.2);
	glVertex3f(1, -1, -0.2);
	glVertex3f(1, 1, -0.2);

	glVertex3f(0.2, 1, -1);
	glVertex3f(0.2, -1, -1);
	glVertex3f(-0.2, -1, -1);
	glVertex3f(-0.2, 1, -1);

	glVertex3f(-1, 1, -0.2);
	glVertex3f(-1, -1, -0.2);
	glVertex3f(-1, -1, 0.2);
	glVertex3f(-1, 1, 0.2);

	glVertex3f(-0.2, 1, 1);
	glVertex3f(0.2, 1, 1);
	glVertex3f(0.2, 1, -1);
	glVertex3f(-0.2, 1, -1);

	glVertex3f(-0.2, -1, 1);
	glVertex3f(0.2, -1, 1);
	glVertex3f(0.2, -1, -1);
	glVertex3f(-0.2, -1, -1);

	glVertex3f(1, 1, 0.2);
	glVertex3f(1, 1, -0.2);
	glVertex3f(-1, 1, -0.2);
	glVertex3f(-1, 1, 0.2);

	glVertex3f(1, -1, 0.2);
	glVertex3f(1, -1, -0.2);
	glVertex3f(-1, -1, -0.2);
	glVertex3f(-1, -1, 0.2);
	glEnd();
	glPopMatrix();
}

void drawSkybox()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 9);
	glDisable(GL_DEPTH_TEST);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glBegin(GL_QUADS);


	glTexCoord2d(0, 0.666666);
	glVertex3d(-1, 1, 1);
	glTexCoord2d(0, 0.333333);
	glVertex3d(-1, -1, 1);
	glTexCoord2d(0.25, 0.333333);
	glVertex3d(1, -1, 1);
	glTexCoord2d(0.25, 0.666666);
	glVertex3d(1, 1, 1);


	glTexCoord2d(0.25, 0.66);
	glVertex3d(1, 1, 1);
	glTexCoord2d(0.25, 0.33);
	glVertex3d(1, -1, 1);
	glTexCoord2d(0.5, 0.33);
	glVertex3d(1, -1, -1);
	glTexCoord2d(0.5, 0.66);
	glVertex3d(1, 1, -1);


	glTexCoord2d(0.5, 0.66);
	glVertex3d(1, 1, -1);
	glTexCoord2d(0.5, 0.33);
	glVertex3d(1, -1, -1);
	glTexCoord2d(0.75, 0.33);
	glVertex3d(-1, -1, -1);
	glTexCoord2d(0.75, 0.66);
	glVertex3d(-1, 1, -1);


	glTexCoord2d(1, 0.66);
	glVertex3d(-1, 1, 1);
	glTexCoord2d(0.75, 0.66);
	glVertex3d(-1, 1, -1);
	glTexCoord2d(0.75, 0.33);
	glVertex3d(-1, -1, -1);
	glTexCoord2d(1, 0.33);
	glVertex3d(-1, -1, 1);

	glTexCoord2d(0.25, 1);
	glVertex3d(-1, 1, 1);
	glTexCoord2d(0.25, 0.66);
	glVertex3d(1, 1, 1);
	glTexCoord2d(0.5, 0.66);
	glVertex3d(1, 1, -1);
	glTexCoord2d(0.5, 1);
	glVertex3d(-1, 1, -1);



	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, -1, 1);

	glEnd();


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


	glPushMatrix();
	//glRotated(cup * 180 / PI, -1, 0, 0);
	glRotated(ca * 180 / PI, 0, 1, 0);
	drawSkybox();
	glPopMatrix();												//glRotated(5, 1, 0, 0);
	gf += 2;												// To Make The Gift Goes Around Itself
															/*if (keys['J'])
															lx -= 0.01;
															if (keys['L'])
															lx += 0.01;
															if (keys['K'])
															lz += 0.01;
															if (keys['I'])
															lz -= 0.01;*/

	if (keys[VK_LEFT])
		ca -= 0.05;
	if (keys[VK_RIGHT])
		ca += 0.05;
	if (keys[VK_UP])
	{
		if (yup < 27)
		{
			yup++;
			cup += 0.01;
		}
	}
	if (keys[VK_DOWN])
	{
		if (yup > -10)
		{
			yup--;
			cup -= 0.01;
		}
	}
	if (keys[VK_SPACE])
	{

		bx = cx;
		by = 1.25;
		bz = cz;
		bvx = cos(ca) * cos(cup) * 0.5;
		bvy = sin(cup) * 0.5;
		bvz = sin(ca) * cos(cup) * 0.5;
		keys[VK_SPACE] = false;
		fire = true;
	}
	if (keys['W'])
	{
		if (mov_w)
		{
			cx += cos(ca) * 0.5;
			cz += sin(ca) * 0.5;
		}
	}
	if (keys['S'])
	{
		if (mov_s)
		{
			cx -= cos(ca) * 0.5;
			cz -= sin(ca) * 0.5;
		}
	}
	if (keys['A'])
	{
		if (mov_a)
		{
			cz -= cos(ca) * 0.5;
			cx += sin(ca) * 0.5;
		}
	}

	if (keys['D'])
	{
		if (mov_d)
		{
			cz += cos(ca) * 0.5;
			cx -= sin(ca) * 0.5;
		}
	}
	if (keys['G'])
	{
		jump = true;
	}
	if (jump)
	{
		counter += PI / 30;
		ly = abs(sin(counter)) * 1.5;
		if (ly <= 0.01)
		{
			ly = 0;
			jump = false;
		}
	}
	if (SSMAN)
	{
		/*******************************SnowMan and Cannon************************************/
		float postion[] = { 0,2.5,-4,1 },
			ambient[] = { 0.3,0.3,0.3,1 },
			emission[] = { 1,0.5,0,1 },
			specular[] = { 0,1,0,1 },
			diff_body[] = { 1,1,1,1 },
			diff_eyes[] = { 0,0,1,1 },
			diff_butt[] = { 1,0,0,1 },
			diff_nose[] = { 1,0.5,0,1 },
			diff_hand[] = { 1,0.7,0,1 },
			diff_con1[] = { 1,0.5,0.2,1 },
			diff_con2[] = { 0.7,0.6,0.35,1 },
			no_mat[] = { 0,0,0,1 },
			shininess = 80, no_shininess = 0;
		glPushMatrix();
		glTranslated(lx, ly - 1.3, lz);
		//glRotated(xup / 2, 1, 0, 0);
		glScaled(0.45, 0.45, 0.45);
		//xup += 0.05;
		//glRotated(-90, 0, 1, 0);
		//glTranslated(cx, 1.25, cz);
		//glRotated(-90, 0, 0, 1);
		GLUquadric* a = gluNewQuadric();

		/*------------------------------Cannon-----------------------------------------------*/
		glPushMatrix();
		glTranslated(0, 2.5, 1.5);
		glScaled(0.6, 0.6, 1.2);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glLightf(GL_LIGHT1, GL_SHININESS, shininess);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_EMISSION, emission);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_con1);
		glRotatef(-90.0f + yup, 1, 0, 0);
		shape(30, 0.6, 0.6, 0, 2.5);
		circul(30, 0.6, 0);
		//gluCylinder(a, 0.6, 0.6, 2.5, 32, 16);
		//gluCylinder(a, 0.6, 0, 0, 32, 16);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diff_con2);
		glTranslated(0, 0.4, 0.7);
		shape(30, 0.2, 0.2, 0, 1.25);
		circul(30, 0.2, 0);
		//gluCylinder(a, 0.2, 0.2, 1.25, 32, 16);
		//gluCylinder(a, 0.2, 0, 0, 32, 16);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
		glPopMatrix();



		/*------------------------------SonwMan----------------------------------------------*/

		glRotated(180 - r, 0, 1, 0);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_body);
		glTranslated(0, 0.75, 0);					//body
													//glColor3d(1, 1, 1);
		gluSphere(a, 0.75, 32, 16);

		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_hand);
		glPushMatrix();
		glTranslated(0.5, 0.5, 0);
		glRotated(-15, 0, 0, 1);
		shape(10, 0.035, 0.04, 0.6, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-0.5, 0.5, 0);
		glRotated(15, 0, 0, 1);
		shape(10, 0.035, 0.04, 0.6, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.66, 1.07, 0);
		glRotated(30, 0, 0, 1);
		shape(10, 0.025, 0.03, 0.4, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-0.66, 1.07, 0);
		glRotated(-30, 0, 0, 1);
		shape(10, 0.025, 0.03, 0.4, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.45, 1.42, 0);
		glRotated(45, 0, 0, 1);
		shape(10, 0.015, 0.02, 0.2, 0);
		glRotated(30, 1, 0, 0);
		shape(10, 0.015, 0.02, 0.2, 0);
		glRotated(-60, 1, 0, 0);
		shape(10, 0.015, 0.02, 0.2, 0);
		glPopMatrix();

		glPushMatrix();
		glTranslated(-0.45, 1.42, 0);
		glRotated(-45, 0, 0, 1);
		shape(10, 0.015, 0.02, 0.2, 0);
		glRotated(-30, 1, 0, 0);
		shape(10, 0.015, 0.02, 0.2, 0);
		glRotated(60, 1, 0, 0);
		shape(10, 0.015, 0.02, 0.2, 0);
		glPopMatrix();
		glPopMatrix();


		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_butt);
		glTranslated(0, 0.3, 0.65);					//first button
													//glColor3d(1, 0, 0);
		gluSphere(a, 0.07, 32, 16);

		glTranslated(0, -0.3, 0.08);				//second button
		gluSphere(a, 0.07, 36, 16);

		glTranslated(0, -0.3, -0.08);				//third button
		gluSphere(a, 0.07, 36, 16);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_body);
		glTranslated(0, 0.89, 0);
		//glColor3d(1, 1, 1);
		gluSphere(a, 0.25, 32, 16);

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_nose);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		//glColor3d(1, 0.5, 0);
		gluCylinder(a, 0.08, 0, 0.5, 32, 16);

		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_eyes);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
		glTranslated(0.05, 0.1, 0.18);
		//glColor3d(0, 0, 1);
		gluSphere(a, 0.05, 32, 16);

		glTranslated(-0.1, 0, 0);
		//glColor3d(0, 0, 1);
		gluSphere(a, 0.05, 32, 16);
		glPopMatrix();
		glPopMatrix();

		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glPopMatrix();

	}


	/*----------------------------------------sky box-------------------------------------------*/


	gluLookAt(cx, cy + 1.5, cz, cx + cos(ca), cy + 1.5, cz + sin(ca), 0, 1, 0);




	if (score)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 1);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

	if (score1)
	{


		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 2);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}


	if (score2)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 3);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}


	if (score3)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 4);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

	if (score4)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 5);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

	if (score5)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 6);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

	if (score6)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 7);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

	if (score7)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 8);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glBegin(GL_QUADS);

		glTexCoord2d(0, 0);
		glVertex3d(-4, 3, -40);
		glTexCoord2d(1, 0);
		glVertex3d(4, 3, -40);
		glTexCoord2d(1, 1);
		glVertex3d(4, 8, -40);
		glTexCoord2d(0, 1);
		glVertex3d(-4, 8, -40);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}
	//-----------------------------------Fire----------------------------------------//
	if (fire)
	{
		SSMAN = false;
		glPushMatrix();
		glTranslatef(bx, by, bz);
		glScalef(0.1, 0.1, 0.1);
		glColor3f(1, 0, 0);
		ball(30, 1);
		bx += bvx;
		by += bvy;
		bz += bvz;
		bvy -= 0.005;
		glPopMatrix();

		if (by < 0)
			fire = false;
		if ((-25.8 <= bx && bx <= -24.2) && (0 <= by && by <= 0.8) && (28.2 <= bz && bz <= 29.8))
		{
			fire = false;
			goal_1 = false;
			tt = true;
			score = true;
		}

		if ((-15.8 <= bx && bx <= -14.2) && (0 <= by && by <= 0.8) && (28.2 <= bz && bz <= 29.8))
		{
			fire = false;
			goal_2 = false;
			tt1 = true;
			score1 = true;
		}

		if ((-0.8 <= bx && bx <= 0.8) && (0 <= by && by <= 0.8) && (28.2 <= bz && bz <= 29.8))
		{
			fire = false;
			goal_3 = false;
			tt2 = true;
			score2 = true;
		}

		if ((14.2 <= bx && bx <= 15.8) && (0 <= by && by <= 0.8) && (28.2 <= bz && bz <= 29.8))
		{
			fire = false;
			goal_4 = false;
			tt3 = true;
			score3 = true;
		}

		if ((-25.8 <= bx && bx <= -24.2) && (0 <= by && by <= 0.8) && (-11.8 <= bz && bz <= -10.2))
		{
			fire = false;
			goal_5 = false;
			tt4 = true;
			score7 = true;
		}

		if ((-15.8 <= bx && bx <= -14.2) && (0 <= by && by <= 0.8) && (-11.8 <= bz && bz <= -10.2))
		{
			fire = false;
			goal_6 = false;
			tt5 = true;
			score6 = true;
		}

		if ((-0.8 <= bx && bx <= 0.8) && (0 <= by && by <= 0.8) && (-11.8 <= bz && bz <= -10.2))
		{
			fire = false;
			goal_7 = false;
			tt6 = true;
			score5 = true;
		}

		if ((14.2 <= bx && bx <= 15.8) && (0 <= by && by <= 0.8) && (-11.8 <= bz && bz <= -10.2))
		{
			fire = false;
			goal_8 = false;
			tt7 = true;
			score4 = true;
		}
		if ((-20 <= bx && bx <= -18) && (0 <= by && by <= 2) && (22 <= bz && bz <= 26))
		{
			d1 = false;
		}
		if ((-20 <= bx && bx <= -18) && (0 <= by && by <= 2) && (-24 <= bz && bz <= -20))
		{
			d2 = false;
		}
		if ((-6 <= bx && bx <= -4) && (0 <= by && by <= 2) && (22 <= bz && bz <= 26))
		{
			d3 = false;
		}
		if ((-6 <= bx && bx <= -4) && (0 <= by && by <= 2) && (-24 <= bz && bz <= -20))
		{
			d4 = false;
		}
		if ((8 <= bx && bx <= 10) && (0 <= by && by <= 2) && (22 <= bz && bz <= 26))
		{
			d5 = false;
		}
		if ((8 <= bx && bx <= 10) && (0 <= by && by <= 2) && (-24 <= bz && bz <= -20))
		{
			d6 = false;
		}
		if ((22 <= bx && bx <= 24) && (0 <= by && by <= 2) && (22 <= bz && bz <= 26))
		{
			d7 = false;
		}
		if ((22 <= bx && bx <= 24) && (0 <= by && by <= 2) && (-24 <= bz && bz <= -20))
		{
			d8 = false;
		}
		if ((26 <= bx && bx <= 32) && (0 <= by && by <= 2) && (0 <= bz && bz <= 6))
		{
			d9 = false;
		}
	}
	else
		SSMAN = true;


	glTranslatef(-35, 0, 49);


	/*--------------------celebrate-------------------*/
	if (tt == true && tt1 == true && tt2 == true && tt3 == true && tt4 == true && tt5 == true && tt6 == true && tt7 == true)
	{
		/*---------------*/
		glPushMatrix();
		glTranslated(10, 10, -40);
		glEnable(GL_POINT_SMOOTH);
		glColor3d(1, 0, 0);
		glBegin(GL_POINTS);
		//srand(6);
		for (int i = 0; i < 2000; i++)
		{
			double x = (rand() % 200) - 100;
			double y = (rand() % 100) - 2;
			glVertex3d(x, y, 30);
		}

		glEnd();
		glPopMatrix();



		glPushMatrix();
		glTranslated(0, 0, -40);
		glEnable(GL_POINT_SMOOTH);
		glColor3d(0, 1, 0);
		glBegin(GL_POINTS);
		//srand(6);
		for (int i = 0; i < 2000; i++)
		{
			double x = (rand() % 110) - 40;
			double y = (rand() % 100) - 4;
			glVertex3d(x, y, 40);
		}

		glEnd();
		glPopMatrix();



		glPushMatrix();
		glTranslated(0, 0, -40);
		glEnable(GL_POINT_SMOOTH);
		glColor3d(0, 0, 1);
		glBegin(GL_POINTS);
		//srand(6);
		for (int i = 0; i < 2000; i++)
		{
			double x = (rand() % 110) - 10;
			double y = (rand() % 100) - 6;
			glVertex3d(x, y, 20);
		}

		glEnd();
		glPopMatrix();
		r = 180;

		keys['G'] = true;

	}
	/*******************************Floor, Stars and Tree*********************************/
	/*------------------------------Goals------------------------------------------------*/
	/*glPushMatrix();
	glTranslatef(14, 1, -2);
	stone();
	glPopMatrix();*/
	if (goal_1)
	{
		glPushMatrix();
		glTranslatef(10, 0.4, -20);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_2)
	{
		glPushMatrix();
		glTranslatef(20, 0.4, -20);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_3)
	{
		glPushMatrix();
		glTranslatef(35, 0.4, -20);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_4)
	{
		glPushMatrix();
		glTranslatef(50, 0.4, -20);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_5)
	{
		glPushMatrix();
		glTranslatef(10, 0.4, -60);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_6)
	{
		glPushMatrix();
		glTranslatef(20, 0.4, -60);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_7)
	{
		glPushMatrix();
		glTranslatef(35, 0.4, -60);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}

	if (goal_8)
	{
		glPushMatrix();
		glTranslatef(50, 0.4, -60);
		glScalef(0.4, 0.4, 0.4);
		gift();
		glPopMatrix();
	}
	/*------------------------------Walls------------------------------------------------*/
	glPushMatrix();

	glColor3d(0.663, 0.663, 0.663);
	glPushMatrix();
	glTranslatef(16, 1, -12);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 1, -48);
	glScalef(1, 1, 21);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 1, -84);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(28, 1, -12);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(28, 1, -48);
	glScalef(1, 1, 21);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(28, 1, -84);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(44, 1, -12);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(44, 1, -48);
	glScalef(1, 1, 21);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(44, 1, -84);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(56, 1, -12);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(56, 1, -48);
	glScalef(1, 1, 21);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(56, 1, -84);
	glScalef(1, 1, 11);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 1, -46);
	glScalef(7, 1, 1);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22, 1, -46);
	glScalef(5, 1, 1);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(36, 1, -46);
	glScalef(7, 1, 1);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, 1, -46);
	glScalef(5, 1, 1);
	stone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(59, 1, -46);
	glScalef(2, 1, 1);
	stone();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(69, 1, -46);
	glScalef(2, 1, 1);
	stone();
	glPopMatrix();
	glPopMatrix();

	/*------------------------------Floor------------------------------------------------*/
	glPushMatrix();

	bool tr = true;
	glTranslated(x, y, z);
	for (int i = 0; i < 49; i++)
	{
		for (int j = 0; j < 37; j++)
		{
			if (tr)
			{
				tr = false;
				Floor();
			}
			else
			{
				tr = true;
				Floor();

			}
			glTranslated(2, 0, 0);
		}

		glTranslated(-74, 0, -2);
	}
	glPopMatrix();

	/*------------------------------Trees------------------------------------------------*/
	glPushMatrix();

	float pos[] = { 10,20,45,0 };
	float white[] = { 1,1,1,1 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	for (int i = 0; i < 24; i++)
	{
		glTranslated(0, 0, -4);
		tree();
	}
	for (int i = 0; i < 18; i++)
	{
		glTranslated(4, 0, 0);
		tree();
	}
	for (int i = 0; i < 24; i++)
	{
		glTranslated(0, 0, 4);
		tree();
	}
	for (int i = 0; i < 18; i++)
	{
		glTranslated(-4, 0, 0);
		tree();
	}

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	/*------------------------------Doors------------------------------------------------*/
	glPushMatrix();
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0, 1, 1, 0.5);
	if (d1)
	{
		glPushMatrix();
		glTranslatef(16, 1, -25);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}
	if (d2)
	{
		glPushMatrix();
		glTranslatef(16, 1, -71);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}

	if (d3)
	{
		glPushMatrix();
		glTranslatef(28, 1, -25);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}
	if (d4)
	{
		glPushMatrix();
		glTranslatef(28, 1, -71);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}

	if (d5)
	{
		glPushMatrix();
		glTranslatef(44, 1, -25);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}
	if (d6)
	{
		glPushMatrix();
		glTranslatef(44, 1, -71);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}

	if (d7)
	{
		glPushMatrix();
		glTranslatef(56, 1, -25);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}
	if (d8)
	{
		glPushMatrix();
		glTranslatef(56, 1, -71);
		glScalef(1, 1, 2);
		stone1();
		glPopMatrix();
	}
	if (d9)
	{
		glPushMatrix();
		glTranslatef(64, 1, -46);
		glScalef(3, 1, 1);
		stone1();
		glPopMatrix();
	}

	glDisable(GL_BLEND);
	glPopMatrix();
	return TRUE;										// Everything Went OK
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(const char title[], int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
														//if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	SetTimer(hWnd, 23423, 20, NULL);
	while (GetMessage(&msg, NULL, 0, 0))									// Loop That Runs While done=FALSE
	{
		//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				//done = TRUE;							// If So done=TRUE
				break;
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		//else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					//done = TRUE;						// ESC Signalled A Quit
					break;
				}
				else if (msg.message == WM_TIMER)								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
														// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}

		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}