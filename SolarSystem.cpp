#include <windows.h>
#include <iostream>
#include <glut.h>
#include <math.h>
#include "imageloader.h"
#include <stdlib.h>
#include "texturemodel.h"

namespace SolarSystem123 {
	GLuint _textureEarth, _textureSun, _textureMoon;
	TextureModel sky, skyTop, grass, earth, moon, sun, planet;
	Vector3 sky_t, skyTop_t, grass_t;
	float lx = 0.0f, lz = 0.0f;
	float x = 0.0f, z = 25.0f;
	float angle = -1.5f;
	float speed = 0.5f;
	float heightAngle = 0;
	float height_view = -1;

	void draw(TextureModel* m, Vector3 t) {
		glPushMatrix();
		glTranslatef(t.x, t.y, t.z);
		m->draw();
		glPopMatrix();
	}

	static void idle(void) {
		glutPostRedisplay();
	}

	void makeSky() {
		sky.clear();
		sky.setTextureFromBMP("data/stars2.bmp");
		sky.addVertex(point3(-100, -100, -100));//0
		sky.addVertex(point3(100, -100, -100));//1
		sky.addVertex(point3(-100, 100, -100));//2
		sky.addVertex(point3(100, 100, -100));//3
		sky.addVertex(point3(-100, -100, 100));//4
		sky.addVertex(point3(100, -100, 100));//5
		sky.addVertex(point3(-100, 100, 100));//6
		sky.addVertex(point3(100, 100, 100));//7
		sky.addQuad(quadIndex(2, 3, 1, 0, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(6, 7, 5, 4, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(2, 6, 4, 0, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));
		sky.addQuad(quadIndex(3, 7, 5, 1, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));

		sky_t = point3(0, 0, 0);
	}

	void makeSkyTop() {
		skyTop.clear();
		skyTop.setTextureFromBMP("data/stars8.bmp");
		skyTop.addVertex(point3(-100, 100, -100));
		skyTop.addVertex(point3(100, 100, -100));
		skyTop.addVertex(point3(100, 100, 100));
		skyTop.addVertex(point3(-100, 100, 100));
		skyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));

		skyTop_t = point3(0, 0, 0);
	}

	void makeGrass() {
		grass.clear();
		grass.setTextureFromBMP("data/stars1.bmp");
		grass.addVertex(point3(-100, -100, 100));
		grass.addVertex(point3(-100, -100, -100));
		grass.addVertex(point3(100, -100, -100));
		grass.addVertex(point3(100, -100, 100));
		grass.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 3), texCoord2(3, 3), texCoord2(3, 0), texCoord2(0, 0)));

		grass_t = point3(0, 0, 0);
	}

	double RotationAngle = 0.0;

	GLuint g_angle_year = 0;
	GLuint gl_angle_moon = 0;



	void drawSun() {
		sun.clear();
		sun.setTextureFromBMP("data/sun.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotated(RotationAngle, 0.0f, 1.0f, 0.0f); // Quay quanh trục y (tự quay)
		glTranslated(0.0, -9.0, 0.0);
		glScaled(5.0, 5.0, 5.0); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawMercury() {
		sun.clear();
		sun.setTextureFromBMP("data/Mercury.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 5, 0.0f, 1.0f, 0.0f);
		glTranslated(5.5, -9.0, 0.0);
		glRotated(RotationAngle * 5, 0.0f, 1.0f, 0.0f);
		glScaled(0.3, 0.3, 0.3); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawVenus() {
		sun.clear();
		sun.setTextureFromBMP("data/venus.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 3, 0.0f, 0.0f, 1.0f);

		glTranslated(7.0, -9.0, 0.0);
		glScaled(0.9, 0.9, 0.9);
		glRotated(RotationAngle * 5, 0.0f, 1.0f, 0.0f);// Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}


	void drawEarth() {
		earth.clear();
		earth.setTextureFromBMP("data/earth1.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotated(g_angle_year, 0.0f, 1.0f, 0.0f); // Quay quanh trục y (quay quanh Mặt Trời)
		glTranslated(10.0, -9.0, 0.0);
		glRotated(30.0f, 1.0f, 0.0f, 0.0f); // Góc nghiêng 30 độ
		glRotated(RotationAngle * 10, 0.0f, 1.0f, 0.0f); // Quay quanh trục y (tự quay)
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawMoon() {
		moon.clear();
		moon.setTextureFromBMP("data/moon.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotated(g_angle_year, 0.0f, 1.0f, 0.0f);
		glTranslated(10.0, -9.0, 0.0);
		glRotated(gl_angle_moon * 5, 0.0f, 1.0f, 0.0f); // Quay quanh trục y (quay quanh Trái Đất)
		glTranslated(1.5, 0.0, 0.0); // Khoảng cách từ Trái Đất đến Mặt Trăng
		glScaled(0.29, 0.29, 0.29); // Kích thước Mặt Trăng (giả định gấp 10 lần kích thước Trái Đất)
		glRotated(RotationAngle * 15, 0.0f, 1.0f, 0.0f);
		gluSphere(mapping, 1, 20, 20);
		glPopMatrix();
	}

	void drawMars() {
		sun.clear();
		sun.setTextureFromBMP("data/mars.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 2, 0.0f, 1.0f, 0.0f);
		glTranslated(13.0, -9.0, 0.0);
		glRotated(15.0f, 1.0f, 0.0f, 0.0f);
		glScaled(0.6, 0.6, 0.6); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		glRotated(RotationAngle * 10, 0.0f, 1.0f, 0.0f);
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawJupiter() {
		planet.clear();
		planet.setTextureFromBMP("data/jupiter.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 0.5, 0.0f, 1.0f, 0.0f);
		glTranslated(17.0, -9.0, 0.0);
		glRotated(90.0f, 1.0f, 0.0f, 0.0f);
		glScaled(1.8, 1.8, 1.8); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		glRotated(RotationAngle * 20, 0.0f, 0.0f, 1.0f);
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawSaturn() {
		// Vẽ Sao Saturn
		planet.clear();
		planet.setTextureFromBMP("data/staturn.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 0.9, 0.0f, 1.0f, 0.0f);
		glTranslated(23.0, -9.0, 0.0);
		glRotated(115.0f, 1.0f, 0.0f, 0.0f);
		glScaled(1.6, 1.6, 1.6); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		glRotated(RotationAngle * 15, 0.0f, 0.0f, 1.0f);
		gluSphere(mapping, 1, 100, 100);


		const int numEllipses = 3;
		double ellipseRadii[numEllipses] = { 2.5, 3.0, 3.5 }; // Bán kính theo hai trục x và z
		double ellipseHeight = 0.0; // Tọa độ y của các vòng xuyến

		glColor3d(1.0, 1.0, 1.0); // Màu sắc của các vòng xuyến

		for (int i = 0; i < numEllipses; i++) {
			double radiusX = ellipseRadii[i] * 0.5; // Thu nhỏ bán kính xuống một nửa
			double radiusZ = ellipseRadii[i] * 0.5; // Thu nhỏ bán kính xuống một nửa

			glBegin(GL_LINE_LOOP); // Bắt đầu vẽ các đường thẳng kết nối các điểm
			for (double angle = 0.0; angle < 2 * PI; angle += 0.1) {
				double x = radiusX * sin(angle);
				double z = ellipseHeight; // Vẽ các điểm theo hình bầu dục nằm ngang
				double y = radiusZ * cos(angle);

				glVertex3d(x, y, z); // Vẽ một điểm trên vòng xuyến
			}
			
			glEnd(); // Kết thúc vẽ các đường thẳng kết nối các điểm
		}

		glPopMatrix();
	}

	void drawUranus() {
		planet.clear();
		planet.setTextureFromBMP("data/uranus.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 2, 0.0f, 1.0f, 0.0f);
		glTranslated(28.5, -9.0, 0.0);
		glRotated(90.0f, 1.0f, 0.0f, 0.0f);
		glScaled(1.5, 1.5, 1.5); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		glRotated(RotationAngle * 10, 0.0f, 0.0f, 1.0f);
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void drawNeptune() {
		planet.clear();
		planet.setTextureFromBMP("data/neptune.bmp");

		GLUquadric* mapping = gluNewQuadric();
		gluQuadricTexture(mapping, GL_TRUE);

		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glRotatef(g_angle_year * 3, 0.0f, 1.0f, 0.0f);
		glTranslated(32.5, -9.0, 0.0);
		glRotated(90.0f, 1.0f, 0.0f, 0.0f);
		glScaled(0.8, 0.8, 0.8); // Kích thước Mặt Trời (giả định gấp đôi kích thước Trái Đất)
		glRotated(RotationAngle * 20, 0.0f, 0.0f, 1.0f);
		gluSphere(mapping, 1, 100, 100);
		glPopMatrix();
	}

	void handleResize(int width, int height) {
		if (height == 0) height = 1;
		const float ar = (float)width / (float)height;
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, ar, 0.1f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void idle1() {
		// Tính toán góc quay mới của Mặt Trời và Trái Đất

		RotationAngle += 1.0; // Điều chỉnh tốc độ quay của Trái Đất
		if (RotationAngle >= 360.0) {
			RotationAngle -= 360.0;
		}

		Sleep(83);
		gl_angle_moon = (gl_angle_moon + 13);
		if (gl_angle_moon >= 360) {
			gl_angle_moon = 0;
		}
		g_angle_year = (g_angle_year + 1);
		if (g_angle_year >= 360) {
			g_angle_year = 0;
		}
		// Yêu cầu vẽ lại cửa sổ OpenGL
		glutPostRedisplay();
	}

	void renderScene1(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(x, -1.0f, z,
			x + lx, height_view, z + lz,
			0.0f, 1.0f, 0.0f);

		glEnable(GL_TEXTURE_2D);
		draw(&sky, sky_t);
		draw(&skyTop, skyTop_t);
		draw(&grass, grass_t);
		drawEarth();
		drawMoon();
		drawSun();
		drawMercury();
		drawVenus();
		drawMars();
		drawJupiter();
		drawSaturn();
		drawUranus();
		drawNeptune();

		glutSwapBuffers();
		glFlush();
	}

	void processKeys1(unsigned char key, int xx, int yy) {
		switch (key) {
		case '>':
			speed += 0.1;
			break;
		case '<':
			speed -= 0.1;
			break;
		case 'w':
			if (heightAngle < PI / 2) {
				heightAngle += 0.1;
				height_view = sin(heightAngle) - 1;
			}
			break;
		case 's':
			if (heightAngle > (-PI / 2)) {
				heightAngle -= 0.1;
				height_view = sin(heightAngle) - 1;
			}
			break;
		case 'a':
			angle -= 0.02f;
			lx = cos(angle);
			lz = sin(angle);
			break;
		case 'd':
			angle += 0.02f;
			lx = cos(angle);
			lz = sin(angle);
			break;

		
		default:
			break;
		}
		glutPostRedisplay();
	}

	void processSpecialKeys1(int key, int xx, int yy) {
		float fraction = speed;
		switch (key) {
		case GLUT_KEY_LEFT:
			x += lz * fraction;
			z -= lx * fraction;
			break;
		case GLUT_KEY_RIGHT:
			x -= lz * fraction;
			z += lx * fraction;
			break;
		case GLUT_KEY_UP:
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN:
			x -= lx * fraction;
			z -= lz * fraction;
			break;

		}
		glutPostRedisplay();
	}

	void initRendering() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		lx = cos(angle);
		lz = sin(angle);

		makeSky();
		makeSkyTop();
		makeGrass();
	}

	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 5.0f };
	const GLfloat light_diffuse[] = { 5.0f, 5.0f, 5.0f, 5.0f };
	const GLfloat light_specular[] = { 5.0f, 5.0f, 5.0f, 5.0f };
	const GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };

}

int SolarSystem(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("SolarSystem");
	SolarSystem123::initRendering();
	glutReshapeFunc(SolarSystem123::handleResize);
	glutIdleFunc(SolarSystem123::idle1);
	glEnable(GL_DEPTH_TEST);
	glutKeyboardFunc(SolarSystem123::processKeys1);
	glutSpecialFunc(SolarSystem123::processSpecialKeys1);
	glutDisplayFunc(SolarSystem123::renderScene1);


	glEnable(GL_TEXTURE_2D);

	glutMainLoop();
	return 0;
}
