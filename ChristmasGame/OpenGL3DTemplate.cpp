#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <random>
#include <cmath>
using namespace std;
#include <glut.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};
//float eyeX = 0.5f, float eyeY = 1.5f, float eyeZ = 0.5f, float centerX = 0.5f, float centerY = 0.0f, float centerZ = 0.5f, float upX = 1.0f, float upY = 1.0f, float upZ = 0.0f


float eyeX = 0.5f;
float eyeY = 0.909861f;
float eyeZ = 1.91423f;
float centerX = 0.5f;
float centerY = 0.634224f;
float centerZ = 0.952973f;
float upX = 0.0f;
float upY = 0.961262f;
float upZ = -0.275637f;

float eyeXT = 0.5f;
float eyeYT = 1.5f;
float eyeZT = 0.5f;
float centerXT = 0.5f;
float centerYT = 0.0f;
float centerZT = 0.5f;
float upXT = 1.0f;
float upYT = 1.0f;
float upZT = 0.0f;

float eyeXF = 0.5f;
float eyeYF = 0.5f;
float eyeZF = 2.0f;
float centerXF = 0.5f;
float centerYF = 0.5f;
float centerZF = 0.0f;
float upXF = 0.0f;
float upYF = 1.0f;
float upZF = 0.0f;

float eyeXS = 2.0f;
float eyeYS = 0.5f;
float eyeZS = 0.5f;
float centerXS = 0.0f;
float centerYS = 0.5f;
float centerZS = 0.5f;
float upXS = 0.0f;
float upYS = 1.0f;
float upZS = 0.0f;


int camView = 0;

class Camera {
public:
	Vector3f eye, center, up;

	Camera() {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		//std::cout << eye.x <<" "<< eye.y<<" "<< eye.z<<"eye"<<"\n";
		//std::cout << center.x << " " << center.y << " " << center.z <<"center"<< "\n";
		//std::cout << up.x << " " << up.y << " " << up.z <<"up"<< "\n";
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

float groundSide = 1.0;
float maxHeight = 1.0;
float groundThick = 0.02;
float WoodThick = 0.008;
float woodFactor = 8;
float woodLen = 0.35;
float numberOfWood = 6;
float treeRedius = groundSide / 7;
float treeHeight = 0.4 * (maxHeight);
float woodWidth = woodFactor * WoodThick;
float JapaneseLanternsRedius = 0.1;
float compressYJL = 0.6;
float snowmanRed = 0.1;
float xGate = groundSide / 10;
float xPresent = groundSide / 10;
float xPlayerFactor = groundSide / 15;

float xPlayer = groundSide / 2;
float yPlayer = 0.0;
float zPlayer = xGate*1.2;

float xPresent1 = 1.5 * treeRedius;//1.5
float yPresent1 = 0.0;
float zPresent1 = 3.5 * treeRedius;

float xPresent2 = 1.5 * treeRedius;
float yPresent2 = 0.0;
float zPresent2 = 5 * treeRedius;

float xPresent3 = groundSide - 1.5 * treeRedius;
float yPresent3 = 0.0;
float zPresent3 = 5 * treeRedius;

float xToriiGate = groundSide / 2;
float yToriiGate = 0.0;
float zToriiGate = xGate / 2;

float xSnowman = groundSide - (snowmanRed * 2);
float ySnowman = 0.0;
float zSnowman = groundSide / 2;

float xJapaneseLanterns1 = JapaneseLanternsRedius * 1.5;
float yJapaneseLanterns1 = 0.0;
float zJapaneseLanterns1 = groundSide - (JapaneseLanternsRedius);

float xJapaneseLanterns2 = groundSide / 2;
float yJapaneseLanterns2 = 0.0;
float zJapaneseLanterns2 = groundSide - (JapaneseLanternsRedius);

float xJapaneseLanterns3 = groundSide - (JapaneseLanternsRedius * 1.5);
float yJapaneseLanterns3 = 0.0;
float zJapaneseLanterns3 = groundSide - (JapaneseLanternsRedius);

float xTree1 = 1.5 * treeRedius;
float yTree1 = 0.0;
float zTree1 = 1.5 * treeRedius;

float xTree2 = groundSide - 1.5 * treeRedius;
float yTree2 = 0.0;
float zTree2 = 1.5 * treeRedius;

bool SnowmanAnim = false;
bool japaneseLanternsAnim = false;
bool treeAnim = false;
bool toriiGateAnim = false;
bool fenceAnim = false;

int playerAngle = 0;
float currentXPlayer = xPlayer;
float currentzPlayer = zPlayer;
float step = 0.02;
bool movePlayer = false;

int timeOfGame = 60*60;
int count = timeOfGame;
int colorChange = 60;

bool present1 = true;
bool present2 = true;
bool present3 = true;

bool gameStarted = false;
bool gameOver = false;
bool winn = !present1 && !present2 && !present3;
int soundVar = 0;

float widthBetweenAnim = woodLen / 4.0;
float heightAnim = (woodLen / 2.0) - (widthBetweenAnim / 2);
float animDisFence = heightAnim;
bool animDirectionFence = true;
float R = 1;
float G = 1;
float B = 0;
float animDisToriiGate = xToriiGate - 0.001;
bool animDirectionToriiGate = true;
float animAngleSnowman = 0.2;
bool animDirectionSnowman = true;
float animDisJL = 0.001;
bool animDirectionJL = true;
float animAngelTree = 0.3;

void drawCylinder(double baseRadius, double topRadius, double height) {
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluCylinder(qobj, baseRadius, topRadius, height, 50, 50);
}
void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(groundSide/2.0,  thickness /2, groundSide / 2.0);
	glScaled(groundSide , thickness, groundSide);
	glutSolidCube(1);
	glPopMatrix();
}
void drawWood(double thick, double len,double width) {
	glPushMatrix();
	glTranslated(0, len / 2, width / 2);
	glScaled(thick, len, width);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawFenceRight() {
	float right = groundSide - (WoodThick * woodFactor);
	float woodGap = (groundSide - (numberOfWood * woodWidth)) / (numberOfWood - 1);
	float move = woodGap + woodWidth;
	float widthBetween = woodLen / 4.0;
	float height = (woodLen / 2.0)-(widthBetween/2);
	for (int i = 0; i < numberOfWood; i++) {
		glPushMatrix();
		glTranslated(groundSide, 0.0, (float)(move * i));
		drawWood(WoodThick, woodLen,woodWidth);
		glPopMatrix();
	}
	for (int i = 0; i < numberOfWood - 1; i++) {
		glPushMatrix();
		glTranslated(groundSide, height, woodWidth + (move * i));
		drawWood(WoodThick, widthBetween, woodGap);
		glPopMatrix();
	}
}
void drawFenceLeft() {
	float right = groundSide - (WoodThick * woodFactor);
	float woodGap = (groundSide - (numberOfWood * woodWidth)) / (numberOfWood - 1);
	float move = woodGap + woodWidth;
	float widthBetween = woodLen / 4.0;
	float height = (woodLen / 2.0) - (widthBetween / 2);
	for (int i = 0; i < numberOfWood; i++) {
		glPushMatrix();
		glTranslated(0.0, 0.0, (float)(move * i));
		drawWood(WoodThick, woodLen, woodWidth);
		glPopMatrix();
	}
	for (int i = 0; i < numberOfWood - 1; i++) {
		glPushMatrix();
		glTranslated(0.0, height, woodWidth + (move * i));
		drawWood(WoodThick, widthBetween, woodGap);
		glPopMatrix();
	}
}
void drawFenceBack() {
	float right = groundSide - (WoodThick * woodFactor);
	float woodGap = (groundSide - (numberOfWood * woodWidth)) / (numberOfWood - 1);
	float move = woodGap + woodWidth;
	float widthBetween = woodLen / 4.0;
	float height = (woodLen / 2.0) - (widthBetween / 2);
	for (int i = 0; i < numberOfWood; i++) {
		glPushMatrix();
		glTranslated((float)(move * i), 0.0, 0.0);
		glRotated(90.0, 0, 1, 0);
		drawWood(WoodThick, woodLen, woodWidth);
		glPopMatrix();
	}
	for (int i = 0; i < numberOfWood - 1; i++) {
		glPushMatrix();
		glTranslated(woodWidth+(move*i), height, 0.0);
		glRotated(90.0, 0, 1, 0);
		drawWood(WoodThick, widthBetween, woodGap);
		glPopMatrix();
	}



}
void drawFence(float R , float G , float B) {
	glColor3d(R, G, B);
	glPushMatrix();
	drawFenceBack();
	drawFenceLeft();
	drawFenceRight();
	glPopMatrix();
}
void drawFenceSide() {
	float right = groundSide - (WoodThick * woodFactor);
	float woodGap = (groundSide - (numberOfWood * woodWidth)) / (numberOfWood - 1);
	float move = woodGap + woodWidth;
	float widthBetween = woodLen / 4.0;
	float height = (woodLen / 2.0) - (widthBetween / 2);
	for (int i = 0; i < numberOfWood; i++) {
		glPushMatrix();
		glTranslated((float)(move * i), 0.0, 0.0);
		glRotated(90.0, 0, 1, 0);
		drawWood(WoodThick, woodLen, woodWidth);
		glPopMatrix();
	}




}
void drawFenceGaps() {
	float right = groundSide - (WoodThick * woodFactor);
	float woodGap = (groundSide - (numberOfWood * woodWidth)) / (numberOfWood - 1);
	float move = woodGap + woodWidth;
	float widthBetween = woodLen / 4.0;
	float height = (woodLen / 2.0) - (widthBetween / 2);
	glPushMatrix();
	glRotated(90.0, 0, 1, 0);
	drawWood(WoodThick, widthBetween, groundSide);
	glPopMatrix();


}
void drawFenceSides(float R, float G, float B) {
	glColor3d(R, G, B);
	glPushMatrix();
	drawFenceSide();
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 0.0, 1.0, 0.0);
	drawFenceSide();
	glPopMatrix();

	glPushMatrix();
	glTranslated(groundSide, 0.0, 0.0);
	glRotated(-90, 0.0, 1.0, 0.0);
	drawFenceSide();
	glPopMatrix();
}
void drawFenceGaps(float R, float G, float B) {
	glColor3d(R, G, B);
	glPushMatrix();
	drawFenceGaps();
	glPopMatrix();

	glPushMatrix();
	glRotated(-90, 0.0, 1.0, 0.0);
	drawFenceGaps();
	glPopMatrix();

	glPushMatrix();
	glTranslated(groundSide, 0.0, 0.0);
	glRotated(-90, 0.0, 1.0, 0.0);
	drawFenceGaps();
	glPopMatrix();
}
void drawSphereForCone(float h,float r,float x , float z ,float y,float red,float R,float G,float B) {
	float pos = r - ((r * y) / h);
	glColor3d(R, G, B);
	srand(time(NULL));
	int tem = (pos * 1000);
	 float xrand = rand() %tem;
	xrand /= 1000.0;
	int sign = rand() % 2;
	if (sign == 1)
		xrand *= -1;
	float tempZ = z+ sqrt((pos*pos)-((x - xrand)* (x - xrand)));
	std::cout << z << ' ';
	std::cout << pos << ' ';
	std::cout << tempZ << ' ';
	std::cout << xrand << ' ';

	glPushMatrix();
	glTranslated(xrand, y, tempZ);
	glutSolidSphere(red, 15, 15);
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(x, y, z+pos);
	glutSolidSphere(red, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, y, z - pos);
	glutSolidSphere(red, 15, 15);
	glPopMatrix();*/
}
void drawSphereForConeWithRotate(int ang ,float h, float r, float x, float z, float y, float red, float R, float G, float B) {
	
    float pos = r - ((r * y) / h);
	glColor3d(R, G, B);
	glPushMatrix();
	glRotated(ang, 0.0, 1.0, 0);
	glTranslated(x+pos, y, 0);
	glutSolidSphere(red, 15, 15);
	glPopMatrix();
}
void drawTree(float x, float y, float z) {
	
	float r = treeRedius;
	float h = treeHeight;

	glPushMatrix();
	glTranslated(x, y, z);


	glColor3d(128 / 255.0, 64 / 255.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, r / 4, 0.0);
	glutSolidCube(r / 2);
	glPopMatrix();


	glColor3d(0, 150/255.0, 0);
	glPushMatrix();
	glTranslated(0.0, r/2 , 0.0);

	glPushMatrix();
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(r, h ,20, 20);
	glPopMatrix();


	drawSphereForConeWithRotate(-100, h, r, 0, 0, h / 5.5, r / 10, 1, 0.5, 0);
	drawSphereForConeWithRotate(-130, h, r, 0, 0, h / 6, r / 10, 1, 0.1, 0.3);

	drawSphereForConeWithRotate(-250, h, r, 0, 0, h / 4.7, r / 10, 0.8, 0.68, 0.4);

	drawSphereForConeWithRotate(-35, h, r, 0, 0, h / 4.2, r / 10, 1, 0.25, 0.6);
	drawSphereForConeWithRotate(45, h, r, 0, 0, h / 4.5, r / 10, 1, 0.35, 0.6);
	
	drawSphereForConeWithRotate(78, h, r, 0, 0, h / 5, r / 10, 0.85, 0.65, 0.4);


	drawSphereForConeWithRotate(52, h, r, 0, 0, h / 3.45, r / 10, 0.9, 0.7, 0.2);
	drawSphereForConeWithRotate(-153, h, r, 0, 0, h / 3.4, r / 10, 0.6, 0.3, 0.123);
	drawSphereForConeWithRotate(-85, h, r, 0, 0, h / 3.5, r / 10, 0.8, 0.3, 0.7);




	glColor3d(0, 150 / 255.0, 0);
	glPushMatrix();
	glTranslated(0.0, h/2.7, 0.0);
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(r*(0.8), h, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, h / 2.7, 0.0);
	drawSphereForConeWithRotate(-100, h, r * (0.8), 0, 0, h / 5.5, r / 10, 1, 0.5, 0);
	drawSphereForConeWithRotate(-130, h, r * (0.8), 0, 0, h / 6, r / 10, 1, 0.1, 0.3);

	drawSphereForConeWithRotate(-250, h, r * (0.8), 0, 0, h / 4.7, r / 10, 0.8, 0.68, 0.4);

	drawSphereForConeWithRotate(-35, h, r * (0.8), 0, 0, h / 4.2, r / 10, 1, 0.25, 0.6);
	drawSphereForConeWithRotate(45, h, r * (0.8), 0, 0, h / 4.5, r / 10, 1, 0.35, 0.6);

	drawSphereForConeWithRotate(78, h, r * (0.8), 0, 0, h / 5, r / 10, 0.85, 0.65, 0.4);


	drawSphereForConeWithRotate(-85, h, r * (0.8), 0, 0, h / 3.5, r / 10, 0.8, 0.3, 0.7);
	glPopMatrix();


	glColor3d(0, 150 / 255.0, 0);
	glPushMatrix();
	glTranslated(0.0, h / 1.35, 0.0);
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(r * (0.6), h*0.8, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, h / 1.35, 0.0);
	drawSphereForConeWithRotate(-110, h * 0.8, r * (0.6), 0, 0, h / 5.5, r / 10, 1, 0.5, 0);
	drawSphereForConeWithRotate(-145, h * 0.8, r * (0.6), 0, 0, h / 6, r / 10, 1, 0.1, 0.3);


	drawSphereForConeWithRotate(35, h * 0.8, r * (0.6), 0, 0, h / 4.5, r / 10, 1, 0.35, 0.6);

	drawSphereForConeWithRotate(43, h * 0.8, r * (0.6), 0, 0, h / 5, r / 10, 0.85, 0.65, 0.4);

	drawSphereForConeWithRotate(62, h * 0.8, r * (0.6), 0, 0, h / 3.45, r / 10, 0.9, 0.7, 0.2);
	drawSphereForConeWithRotate(-120, h * 0.8, r * (0.6), 0, 0, h / 3.4, r / 10, 0.6, 0.3, 0.123);
	drawSphereForConeWithRotate(-30, h * 0.8, r * (0.6), 0, 0, h / 3.5, r / 10, 0.8, 0.3, 0.7);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

}
void drawJapaneseLanterns(float xPos , float yPos , float zPos) {
	float height = JapaneseLanternsRedius * compressYJL * 2;

	glPushMatrix();
	glTranslated(xPos, yPos, zPos);
	glColor3d(0.1, 0.1, 0.1);
	float torusRed = JapaneseLanternsRedius / 2.5;
	float f = (30 * 0.12) / height;
	float factor = (f * JapaneseLanternsRedius) / 0.1;
	float hAdd = ((torusRed / 100) * factor) ;
	glPushMatrix();
	glTranslated(0.0, hAdd, 0);
	glScaled(1.0, factor, 1.0);
	glRotated(90, 1.0, 0, 0);
	glutSolidTorus(torusRed / 100, torusRed, 20, 20);
	//glutSolidTorus(0.1, 0.099999, 20, 20);
	glPopMatrix();

	glColor3d(209/255.0, 7/255.0, 23/255.0);
	
	glPushMatrix();
	
	glTranslated(0.0, height/2+ hAdd, 0);
	glScaled(1.0, compressYJL, 1.0);
	glutSolidSphere(JapaneseLanternsRedius, 100, 100);
	glPopMatrix();


	glColor3d(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslated(0.0, ((torusRed / 100)* factor)+height- 0.006 + hAdd, 0);
	glScaled(1.0, factor, 1.0);
	glRotated(90, 1.0, 0, 0);
	glutSolidTorus(torusRed /100, torusRed, 20, 20);
	//glutSolidTorus(0.1, 0.099999, 20, 20);
	glPopMatrix();

	glPopMatrix();
}
void drawSnowman(float xPos , float yPos , float zPos) {


	float factorConnect = (snowmanRed * 0.2);
	float factorRed = 1.2;
	float red2 = snowmanRed / factorRed;
	float red3 = red2 / 1.4;
	float h1 = snowmanRed * 0.8;
	float h2 = 2 * h1 + red2 * 0.8 - factorConnect;
	float h3 = 2*h1+ red2 * 0.8 * 2 + red3 - 2 * factorConnect;

	glPushMatrix();
	glTranslated(xPos, yPos, zPos);

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, h1, 0);
	glScaled(1.0, 0.8, 1.0);
	glutSolidSphere(snowmanRed, 30, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.0, h2, 0);
    glScaled(1.0, 0.8, 1.0);
	glPushMatrix();
	glutSolidSphere(red2, 30, 30);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, 0.0, red2);
	glutSolidSphere(red2/10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(20,1.0,0.0,0.0);
	glTranslated(0.0, 0.0, red2);
	glutSolidSphere(red2 / 10, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(-20, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, red2);
	glutSolidSphere(red2 / 10, 30, 30);
	glPopMatrix();
	glPopMatrix();

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, h3, 0);
	glutSolidSphere(red3, 30, 30);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(15, 0, 1.0, 0);
	glTranslated(0.0, h3+(red3 /3), red3- red3 / 10);
	glutSolidSphere(red3/10, 30, 30);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-15, 0, 1.0, 0);
	glTranslated(0.0, h3 + (red3 / 3), red3- red3 / 10);
	glutSolidSphere(red3 / 10, 30, 30);
	glPopMatrix();

	glColor3d(240/255.0, 120/255.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, h3 , red3 - red3 / 10);
	glutSolidCone(red3 / 5, red3 / 2, 30, 30);
	glPopMatrix();
	
	
	float ratio = 8;
	float coneY = h3 + (red3 / ratio);
	float coneRed = red3 * sqrt(1 - 1 / ratio);
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, coneY, 0.0);
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(coneRed, red3*3, 20, 20);
	glPopMatrix();


	glColor3d(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0.0, coneY+ coneRed/1.5, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(coneRed/6, coneRed/1.2, 20, 20);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.0, coneY +(red3 / 5)+ red3 * 3 -(0.009), 0.0);
	glutSolidSphere(red3 / 5, 30, 30);
	glPopMatrix();

	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, 2 * h1 + red2 * 0.8 * 2 -(red2 / 3), 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(red2 / 6, red2 / 1.6, 20, 20);
	glPopMatrix();

	glPopMatrix();


}
void drawToriiGate(float xPos , float yPos , float zPos) {

	glPushMatrix();
	glTranslated(xPos, yPos, zPos);
	float x = xGate;
	glColor3d(128/255.0, 64/255.0, 0.0);
	glPushMatrix();
	glTranslated(x, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 4 , 0.0);
	glutSolidCube(x / 2);
	glPopMatrix();

	glColor3d(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0,x/2+ (x * 3)/2, 0.0);
	glScaled((x / 2.5), x * 3, x / 12);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, 0.0, 0.0);
	glColor3d(128 / 255.0, 64 / 255.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 4, 0.0);
	glutSolidCube(x / 2);
	glPopMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 2 + (x * 3) / 2, 0.0);
	glScaled((x / 2.5), x * 3, x / 12);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x / 2 + (x * 3) + (x / 2.5)/2, 0.0);
	glScaled(x * 3,(x / 2.5),x / 6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x / 2 + (x * 3) + (x / 2.5) + (x * 0.2)/2, 0.0);
	glScaled((x / 2.5), x * 0.2, x / 12);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, x / 2 + (x * 3) + (x / 2.5) + (x * 0.2) / 2, 0.0);
	glScaled((x / 2.5), x * 0.2, x / 12);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, x / 2 + (x * 3) + (x / 2.5) + (x * 0.2) / 2, 0.0);
	glScaled((x / 2.5), x * 0.2, x / 12);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x / 2 + (x * 3) + (x / 2.5) + (x * 0.2)+ (x / 3)/2, 0.0);
	glScaled(x * 4, (x / 3), x / 6);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 2 + (x * 3) + (x / 2.5) + (x * 0.2) + (x / 3) + (x / 2.3)/2, 0.0);
	glScaled(x * 5, (x / 2.3), x / 4);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();


}
void drawPresent(float xPos , float yPos , float zPos) {
	float x = xPresent;

	glPushMatrix();
	glTranslated(xPos, yPos, zPos);

	glColor3d(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0, (x * 0.8)/2, 0);
	glPushMatrix();
	glScaled(x*1.4, x*0.8, x*0.8);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(1.0, 1.0, 11/255.0);
	glPushMatrix();
	glTranslated(0.0, 0.0, (x * 0.8)/2 + 0.0008 / 2);
	glScaled(x/5, x * 0.8, 0.0008);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, -((x * 0.8) / 2 + 0.0008 / 2));
	glScaled(x / 5, x * 0.8, 0.0008);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated((x * 1.4) / 2 + 0.0008 / 2, 0.0, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glScaled(x / 5, x * 0.8, 0.0008);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-((x * 1.4) / 2 + 0.0008 / 2), 0.0, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glScaled(x / 5, x * 0.8, 0.0008);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, (x * 0.8) / 2 + 0.0008 / 2, 0.0);
	glScaled(x / 5,  0.0008 , x * 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -((x * 0.8) / 2 + 0.0008 / 2), 0.0);
	glScaled(x / 5, 0.0008, x * 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, (x * 0.8) / 2 + 0.0008 / 2, 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glScaled(x / 5, 0.0008, x * 1.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -((x * 0.8) / 2 + 0.0008 / 2), 0.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glScaled(x / 5, 0.0008, x * 1.4);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();



}
void drawPlayerArm() {
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	glTranslated(0, 0, 1);
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
	glPopMatrix();
}
void drawPlayer(float xPos , float yPos ,float zPos) {
	float x = xPlayerFactor;

	glPushMatrix();
	glTranslated(xPos, yPos, zPos);

	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(-0.3*x, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 3+(x/8), 0.0);
	glScaled(x/4, x/1.5 , x/4);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x/16, 0.0);
	glScaled(x*0.5, x / 8, x*0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();


	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.3 * x, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 3 + (x / 8), 0.0);
	glScaled(x / 4, x / 1.5, x / 4);
	glutSolidCube(1);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 16, 0.0);
	glScaled(x * 0.5, x / 8, x * 0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x / 1.5 + (x / 8), 0.0);
	glPushMatrix();
	glTranslated(0.0, x * 0.06, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x*0.1, x*0.98, 30, 30);
	glPopMatrix();

	glColor3d(200.0/255.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(x, x*3, 30, 30);
	glPopMatrix();

	float redT = x - ((x * (x * 1)) / (x * 3));
	glColor3d(133/255.0, 44/255.0, 44 / 255.0);
	glPushMatrix();
	glTranslated(0.0, x * 1.05, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.05, redT, 30, 30);
	glPopMatrix();

	redT = x - ((x * (x * 2.2)) / (x * 3));

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x * 2.29, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.09, redT*0.95, 30, 30);
	glPopMatrix();

	redT *= 1.1;
	glColor3d(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslated(0.0, x * 2.2 + redT, 0.0);
	glutSolidSphere(redT, 30, 30);
	glPopMatrix();


	float r = redT * sqrt(1 - ((1 / 2) * (1 / 2)));
	glColor3d(0.0, 0.0, 0.0);
	
	glPushMatrix();
	glRotated(15, 0.0, 1.0, 0.0);
	glTranslated(0.0, x * 2.2 + redT, r- (redT * 0.1));
	glutSolidSphere(redT*0.2, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(-15, 0.0, 1.0, 0.0);
	glTranslated(0.0, x * 2.2 + redT, r- (redT * 0.1));
	glutSolidSphere(redT * 0.2, 30, 30);
	glPopMatrix();

	
	float rs = x * 2.2 + redT;
	float rCone = redT * sqrt(1 - ((1 / 2) * (1 / 2)));
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x * 2.2 + redT*1.5, 0.0);
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(rCone, redT*2.5, 30, 30);
	glPopMatrix();

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x * 2.2 + redT * 1.3 + x * 0.06, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.06, redT * 0.8, 30, 30);
	glPopMatrix();

	glColor3d(1.0, 1.0, 180/255.0);
	glPushMatrix();
	glTranslated(0.0, x * 2.2 + redT * 1.3+ redT * 2.5, 0.0);
	glutSolidSphere(redT * 0.5, 30, 30);
	glPopMatrix();


	float armH = 0.6*x;
	glPushMatrix();
	glTranslated(-armH/1.7, x*1.8, 0.0);
	glRotated(140, 0.0, 0.0, 1.0);
	glScaled(x/2, x/2, x/2);
	drawPlayerArm();
	glPopMatrix();

	glPushMatrix();
	glTranslated(armH / 1.7, x * 1.8, 0.0);
	glRotated(-140, 0.0, 0.0, 1.0);
	glScaled(x / 2, x / 2, x / 2);
	drawPlayerArm();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();




}
void drawArm2(float x) {
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(x / 8, x / 8, x*1.5);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x*1.5 , 0.0);
	glutSolidSphere(x / 8, 30, 30);
	glPopMatrix();
}
void drawPlayer2(float xPos, float yPos, float zPos) {
	float x = xPlayerFactor;
	glPushMatrix();
	glTranslated(xPos, yPos, zPos);
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(-0.3 * x, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0,(x / 8), 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(x / 6, x / 6, x / 1.5);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 16, 0.0);
	glScaled(x * 0.5, x / 8, x * 0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();


	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.3 * x, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0,(x / 8), 0.0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(x / 6, x / 6, x / 1.5);
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x / 16, 0.0);
	glScaled(x * 0.5, x / 8, x * 0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x / 1.5 + (x / 8), 0.0);
	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawCylinder(x, x/2.5, x*2);
	glPopMatrix();

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x * 0.06, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.08, x*0.95, 30, 30);
	glPopMatrix();

	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x * 2, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.09, x / 2.4, 30, 30);
	glPopMatrix();

	glColor3d(239 / 255.0, 228 / 255.0, 176 / 255.0);
	glPushMatrix();
	glTranslated(0.0, x, 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.05, (x / 2.5)*1.7, 30, 30);
	glPopMatrix();


	glColor3d(239/255.0, 228/255.0, 176/255.0);
	glPushMatrix();
	glTranslated(0.0, x * 2+x/3, 0.0);
	glutSolidSphere(x/2, 30, 30);
	glPopMatrix();

	float r = (x / 2) * sqrt(1 - ((1 / 2) * (1 / 2)));
	glColor3d(0.0, 0.0, 0.0);

	glPushMatrix();
	glRotated(20, 0.0, 1.0, 0.0);
	glTranslated(0.0, x * 1.9 + (x / 2), r - ((x / 2) * 0.01));
	glutSolidSphere((x / 2) * 0.1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(-20, 0.0, 1.0, 0.0);
	glTranslated(0.0, x * 1.9 + (x / 2), r - ((x / 2) * 0.01));
	glutSolidSphere((x / 2) * 0.1, 30, 30);
	glPopMatrix();




	glColor3d(0.9, 0.9, 0.9);
	glPushMatrix();
	glTranslated(0.0, x * 2.64 , 0.0);
	glRotated(90.0, 1, 0, 0);
	glutSolidTorus(x * 0.08, x / 2.4, 30, 30);
	glPopMatrix();

	glColor3d(200.0 / 255.0, 0.0, 0.0);
	glPushMatrix();
	glTranslated(0.0, x * 2.65, 0.0);
	glRotated(-90.0, 1, 0, 0);
	glutSolidCone(x / 2.3, x*1.2, 30, 30);
	glPopMatrix();

	glColor3d(239 / 255.0, 228 / 255.0, 176 / 255.0);
	glPushMatrix();
	glTranslated(0.0, x * 2.60+ x * 1.2, 0.0);
	glutSolidSphere(x / 6, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x*2, 0.0);
	glRotated(130, 0.0, 0.0, 1.0);
	drawArm2(x);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, x * 2, 0.0);
	glRotated(-130, 0.0, 0.0, 1.0);
	drawArm2(x);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();




}
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 1, 1, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
bool collTest(float x, float z, float XRed,float yRed, float FOC) {
		if ((currentXPlayer - xPlayerFactor < x + XRed * FOC && currentXPlayer - xPlayerFactor> x - XRed * FOC) &&
		((currentzPlayer - xPlayerFactor<z + yRed * FOC && currentzPlayer - xPlayerFactor> z - yRed * FOC) ||
		(currentzPlayer + xPlayerFactor < z + yRed * FOC && currentzPlayer + xPlayerFactor > z - yRed * FOC)||
			(currentzPlayer - xPlayerFactor < z - yRed * FOC && currentzPlayer + xPlayerFactor > z + yRed * FOC))) {
			//std::cout << "test1" << ' ';
			return true;
	}
		else if ((currentXPlayer + xPlayerFactor> x - XRed * FOC && currentXPlayer + xPlayerFactor < x + XRed * FOC) &&
		((currentzPlayer - xPlayerFactor<z + yRed * FOC && currentzPlayer - xPlayerFactor > z - yRed * FOC) ||
		(currentzPlayer + xPlayerFactor < z + yRed * FOC && currentzPlayer + xPlayerFactor > z - yRed * FOC)||
			(currentzPlayer - xPlayerFactor < z - yRed * FOC && currentzPlayer + xPlayerFactor > z + yRed * FOC))) {
			//std::cout << "test2" << ' ';
		     return true;
	     }
		else if ((currentXPlayer - xPlayerFactor < x - XRed * FOC && currentXPlayer + xPlayerFactor > x + XRed * FOC) &&
			((currentzPlayer - xPlayerFactor<z + yRed * FOC && currentzPlayer - xPlayerFactor > z - yRed * FOC) ||
				(currentzPlayer + xPlayerFactor < z + yRed * FOC && currentzPlayer + xPlayerFactor > z - yRed * FOC) ||
				(currentzPlayer - xPlayerFactor < z - yRed * FOC && currentzPlayer + xPlayerFactor > z + yRed * FOC))) {
			//std::cout << "test2" << ' ';
			return true;
		}
		return false;
}
bool playerColl() {
	if (currentXPlayer - xPlayerFactor < 0 || currentXPlayer + xPlayerFactor > groundSide||
		currentzPlayer < zPlayer|| currentzPlayer + xPlayerFactor > groundSide){
		PlaySound(TEXT("res/crash.wav"), NULL, SND_ASYNC | SND_FILENAME);
		soundVar = 60;
		return true;
	}
	else if (collTest(xTree1, zTree1, treeRedius, treeRedius,0.7) || collTest(xTree2, zTree2, treeRedius, treeRedius,0.7) || collTest(xSnowman, zSnowman, snowmanRed, snowmanRed,0.7)||
		     collTest(xJapaneseLanterns1,zJapaneseLanterns1,JapaneseLanternsRedius, JapaneseLanternsRedius,0.7)|| collTest(xJapaneseLanterns2, zJapaneseLanterns2, JapaneseLanternsRedius, JapaneseLanternsRedius,0.7)||
		     collTest(xJapaneseLanterns3, zJapaneseLanterns3, JapaneseLanternsRedius, JapaneseLanternsRedius,0.7)) {
		return true;
	}

	return false;
}
void animPlayer() {
	if (movePlayer) {
		if (playerAngle == 0) {
			currentzPlayer += step;
		}
		else if (playerAngle == 90) {
			currentXPlayer += step;
		}
		else if (playerAngle == 180) {
			currentzPlayer -= step;
		}
		else {
			currentXPlayer -= step;
		}
	}
	if (playerColl()) {
		if (movePlayer) {
			if (playerAngle == 0) {
				currentzPlayer -= step;
			}
			else if (playerAngle == 90) {
				currentXPlayer -= step;
			}
			else if (playerAngle == 180) {
				currentzPlayer += step;
			}
			else {
				currentXPlayer += step;
			}
			
		}
	}
	    movePlayer = false;
		glPushMatrix();
		glTranslated(currentXPlayer, yPlayer, currentzPlayer);
		glRotated(playerAngle, 0.0, 1.0, 0.0);
		drawPlayer2(0, 0, 0);
		glPopMatrix();
	

	
}
void animAllPresents() {
	if (present1) {
		if (collTest(xPresent1, zPresent1, 0.7 * xPresent, 0.4 * xPresent, 0.8)) {
			PlaySound(TEXT("res/power.wav"), NULL, SND_ASYNC | SND_FILENAME);
			soundVar = 60;
			present1 = false;
		}
		else {
			drawPresent(xPresent1, yPresent1, zPresent1);
		}

		
		
	}
	if (present2) {
		if (collTest(xPresent2, zPresent2, 0.7 * xPresent, 0.4 * xPresent, 0.8)) {
			PlaySound(TEXT("res/power.wav"), NULL, SND_ASYNC | SND_FILENAME);
			soundVar = 60;
			present2 = false;
		}
		else {
			drawPresent(xPresent2, yPresent2, zPresent2);
		}
		
	}
	if (present3) {
		if (collTest(xPresent3, zPresent3, 0.7 * xPresent, 0.4 * xPresent, 0.8)) {
			PlaySound(TEXT("res/power.wav"), NULL, SND_ASYNC | SND_FILENAME);
			soundVar = 60;
			present3 = false;
		}
		else {
			drawPresent(xPresent3, yPresent3, zPresent3);
		}
		
	}
}
void animPresent1() {
	drawPresent(xPresent1, yPresent1, zPresent1);
}
void animPresent2() {
	drawPresent(xPresent2, yPresent2, zPresent2);
}
void animPresent3() {
	drawPresent(xPresent3, yPresent3, zPresent3);
}
void animToriiGate() {
	if (toriiGateAnim) {
		drawToriiGate(animDisToriiGate, yToriiGate, zToriiGate);
		if (animDirectionToriiGate) {
			if (animDisToriiGate <= xGate*1.25) {
				animDisToriiGate += 0.001;
				animDirectionToriiGate = false;
			}
			else {
				animDisToriiGate -= 0.001;
			}
		}
		else {
			if (animDisToriiGate >= groundSide-xGate*1.25) {
				animDisToriiGate -= 0.001;
				animDirectionToriiGate = true;
			}
			else {
				animDisToriiGate += 0.001;
			}
		}
	}
	else {
		drawToriiGate(xToriiGate, yToriiGate, zToriiGate);
	}
	
}
void animSnowman() {
	if (SnowmanAnim) {
		
		glPushMatrix();
		glTranslated(xSnowman, ySnowman, zSnowman);
		glRotated(animAngleSnowman, 0.0, 0.0, 1.0);
		drawSnowman(0, 0, 0);
		glPopMatrix();
		if (animDirectionSnowman) {
			if (animAngleSnowman >= 5) {
				animAngleSnowman -= 0.2;
				animDirectionSnowman = false;
			}
			else {
				animAngleSnowman += 0.2;
			}
		}
		else {
			if (animAngleSnowman <= -5) {
				animAngleSnowman += 0.2;
				animDirectionSnowman = true;
			}
			else {
				animAngleSnowman -= 0.2;
			}

		}
	}
	else {
		drawSnowman(xSnowman, ySnowman, zSnowman);
	}
	
}
void animJapaneseLanterns1() {
	if (japaneseLanternsAnim) {
		drawJapaneseLanterns(xJapaneseLanterns1, animDisJL, zJapaneseLanterns1);
		if (animDirectionJL) {
			if (animDisJL >= groundSide / 2) {
				animDisJL -= 0.001;
				animDirectionJL = false;
			}
			else {
				animDisJL += 0.001;
			}
		}
		else {
			if (animDisJL <= 0) {
				animDisJL += 0.001;
				animDirectionJL = true;
			}
			else {
				animDisJL -= 0.001;
			}
		}
	}
	else {
		drawJapaneseLanterns(xJapaneseLanterns1, yJapaneseLanterns1, zJapaneseLanterns1);
	}

	
}
void animJapaneseLanterns2() {
	if (japaneseLanternsAnim) {
		drawJapaneseLanterns(xJapaneseLanterns2, animDisJL, zJapaneseLanterns2);
		if (animDirectionJL) {
			if (animDisJL >= groundSide / 2) {
				animDisJL -= 0.001;
				animDirectionJL = false;
			}
			else {
				animDisJL += 0.001;
			}
		}
		else {
			if (animDisJL <= 0) {
				animDisJL += 0.001;
				animDirectionJL = true;
			}
			else {
				animDisJL -= 0.001;
			}
		}
	}
	else {
		drawJapaneseLanterns(xJapaneseLanterns2, yJapaneseLanterns2, zJapaneseLanterns2);
	}
	
}
void animJapaneseLanterns3() {
	if (japaneseLanternsAnim) {
		drawJapaneseLanterns(xJapaneseLanterns3, animDisJL, zJapaneseLanterns3);
		if (animDirectionJL) {
			if (animDisJL >= groundSide / 2) {
				animDisJL -= 0.001;
				animDirectionJL = false;
			}
			else {
				animDisJL += 0.001;
			}
		}
		else {
			if (animDisJL <= 0) {
				animDisJL += 0.001;
				animDirectionJL = true;
			}
			else {
				animDisJL -= 0.001;
			}
		}
	}
	else {
		drawJapaneseLanterns(xJapaneseLanterns3, yJapaneseLanterns3, zJapaneseLanterns3);
	}
	
}
void animTree1() {
	if (treeAnim) {
		glPushMatrix();
		glTranslated(xTree1, yTree1, zTree1);
		glRotated(animAngelTree, 0.0, 1.0, 0.0);
		drawTree(0,0,0);
		glPopMatrix();
		
	}
	else {
		drawTree(xTree1, yTree1, zTree1);
	}
	animAngelTree += 0.3;
	if (animAngelTree >= 360) {
		animAngelTree = 0.0;
	}
	
}
void animTree2() {
	if (treeAnim) {
		glPushMatrix();
		glTranslated(xTree2, yTree2, zTree2);
		glRotated(animAngelTree, 0.0, 1.0, 0.0);
		drawTree(0, 0, 0);
		glPopMatrix();

	}
	else {
		drawTree(xTree2, yTree2, zTree2);
	}
	animAngelTree += 0.3;
	if (animAngelTree >= 360) {
		animAngelTree = 0.0;
	}
}
void animFence() {

	if (colorChange == 0) {
		R = (rand()%255)/255.0;
		G = (rand() % 255) / 255.0;
	    B = (rand() % 255) / 255.0;
		colorChange = 60;
	}

    drawFenceSides(R, G, B);
	glPushMatrix();
	glTranslated(0.0, animDisFence, 0.0);
	drawFenceGaps(R, G, B);
	glPopMatrix();
	  if(fenceAnim) {
		if (animDirectionFence) {
			animDisFence += 0.005;
			if (animDisFence > woodLen - widthBetweenAnim) {
				animDisFence -= 0.005;
				animDirectionFence = false;
			}
		}
		else {
			animDisFence -= 0.005;
			if (animDisFence < 0) {
				animDisFence += 0.005;
				animDirectionFence = true;
			}
		}
	}

}
void Display() {
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glColor3d(1, 1, 1);
	drawWall(groundThick);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.0, groundThick, 0.0);


	if (!gameOver) {
		animTree2();
		animTree1();
		animSnowman();
		animAllPresents();
		animJapaneseLanterns3();
		animJapaneseLanterns2();
		animJapaneseLanterns1();
		animToriiGate();
	}
	

	animPlayer();
	
	animFence();

	glPopMatrix();


	glFlush();
}
void Timer(int value) {
	if (timeOfGame == 0 &&!gameOver) {
		gameOver = true;
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glutPostRedisplay();
		PlaySound(TEXT("res/gameOver.wav"), NULL,SND_ASYNC | SND_FILENAME);
		gameOver = true;
	}
	if (soundVar == 1) {
		PlaySound(TEXT("res/back.wav"), NULL, SND_LOOP|SND_ASYNC | SND_FILENAME);
	}
	if (soundVar > 0) {
		soundVar--;
	}
	if (!present1&& !present2&& !present3&& !gameOver) {
		PlaySound(TEXT("res/win.wav"), NULL, SND_ASYNC | SND_FILENAME);
		gameOver = true;
	}

	if (!gameOver) {
		colorChange -= 1;
		glutPostRedisplay();
		timeOfGame--;
		glutTimerFunc(1000 / 120, Timer, 0);
	}


}
void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 't':
		camera.eye.x=eyeXT;
		camera.eye.y = eyeYT;
		camera.eye.z = eyeZT;
		camera.center.x = centerXT;
		camera.center.y = centerYT;
		camera.center.z = centerZT;
		camera.up.x = upXT;
		camera.up.y = upYT;
		camera.up.z = upZT;
		camView = 1;
		break;
	case 'y':
		camera.eye.x = eyeXF;
		camera.eye.y = eyeYF;
		camera.eye.z = eyeZF;
		camera.center.x = centerXF;
		camera.center.y = centerYF;
		camera.center.z = centerZF;
		camera.up.x = upXF;
		camera.up.y = upYF;
		camera.up.z = upZF;
		camView = 2;
		break;
	case 'u':
		camera.eye.x = eyeXS;
		camera.eye.y = eyeYS;
		camera.eye.z = eyeZS;
		camera.center.x = centerXS;
		camera.center.y = centerYS;
		camera.center.z = centerZS;
		camera.up.x = upXS;
		camera.up.y = upYS;
		camera.up.z = upZS;
		camView = 0;
		break;
	case 'i':
		camera.eye.x = eyeX;
		camera.eye.y = eyeY;
		camera.eye.z = eyeZ;
		camera.center.x = centerX;
		camera.center.y = centerY;
		camera.center.z = centerZ;
		camera.up.x = upX;
		camera.up.y = upY;
		camera.up.z = upZ;
		camView = 3;
		break;

	case 'c':
		SnowmanAnim=true;
		break;
	case 'C':
		animAngleSnowman = 0.2;
		animDirectionSnowman = true;
		SnowmanAnim = false;
		break;
	case 'v':
		japaneseLanternsAnim = true;
		break;
	case 'V':
		animDisJL = 0.001;
		animDirectionJL = true;
		japaneseLanternsAnim = false;
		break;
	case 'b':
		treeAnim = true;
		break;
	case 'B':
		animAngelTree = 0.1;
		treeAnim = false;
		break;
	case 'n':
		toriiGateAnim = true;
		break;
	case 'N':
		toriiGateAnim = false;
		animDisToriiGate = xToriiGate - 0.001;
		animDirectionToriiGate = true;
		break;
	case 'm':
		fenceAnim = true;
		break;
	case 'M':
		fenceAnim = false;
		animDisFence = heightAnim;
		animDirectionFence = true;
		break;
	case '6':
		playerAngle += 90;
		playerAngle %= 360;
		break;
	case '4':
		playerAngle -= 90;
		if (playerAngle == -90) {
			playerAngle = 270;
		}
		break;
	case '8':
		movePlayer = true;
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	//glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	//glutPostRedisplay();
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutTimerFunc(0, Timer, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	PlaySound(TEXT("res/back.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
	glutMainLoop();
}
