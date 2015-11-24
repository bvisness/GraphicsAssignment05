//
//  OpenGL 3.2 Template for Mac
//  Ben Visness
//

// Suppress GLUT deprecated warnings on Mac
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "VisnessGL.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "PLYGameObject.h"
#include <math.h>
#pragma comment(lib, "glew32.lib")
#pragma comment(lib,"ILUT.lib")
#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"ILU.lib")

#include <stdio.h>

//store window width and height
int ww = 1000, wh = 700;

int mouseX = 0;
int mouseY = 0;
int mouseXDelta = 0;
int mouseYDelta = 0;
bool mouseLeftPressed = false;
bool mouseRightPressed = false;

Scene* scene;

Sphere* earth;
Sphere* clouds;

Texture2D* earthDiffuseTex;
Texture2D* earthSpecTex;
Texture2D* earthNormalMap;
Texture2D* earthCloudsTex;

GameObject* cameraAnchor;
Camera* mainCam;

float cameraAnchorRotVelocity = 0;
float cameraAnchorRotFriction = 0.01;

void display(void)
{
    /*clear all pixels*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
#ifdef __APPLE__
		printf("%s\n", gluErrorString(error));
#else
//        printf("%s\n", glewErrorString(error));
#endif
	}

    scene->draw();

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		mouseLeftPressed = (state == GLUT_DOWN);
	}
	if (button == GLUT_RIGHT_BUTTON) {
		mouseRightPressed = (state == GLUT_DOWN);
	}
}

void mouseMove(int x, int y) {
	y = -y;
	mouseXDelta = x - mouseX;
	mouseYDelta = y - mouseY;
	mouseX = x;
	mouseY = y;

	if (mouseLeftPressed) {
		cameraAnchorRotVelocity = -mouseXDelta * 0.25;
		cameraAnchor->rotation.y += cameraAnchorRotVelocity;
	}
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
		exit(0);
    }

	if (key == 'd') {
		if (earth->material.diffuseTexture == nullptr) {
			earth->material.diffuseTexture = earthDiffuseTex;
		} else {
			earth->material.diffuseTexture = nullptr;
		}
	}
	if (key == 's') {
		if (earth->material.specTexture == nullptr) {
			earth->material.specTexture = earthSpecTex;
		} else {
			earth->material.specTexture = nullptr;
		}
	}
	if (key == 'n') {
		if (earth->material.normalMap == nullptr) {
			earth->material.normalMap = earthNormalMap;
		} else {
			earth->material.normalMap = nullptr;
		}
	}
	if (key == 'c') {
		clouds->visible = !clouds->visible;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
    
}

void special(int key, int x, int y) {
    
}

void specialUp(int key, int x, int y) {
    
}

void createObjects() {
    scene = new Scene();

	Image* earthDiffuseImage = new Image("images/earth.png");
	earthDiffuseTex = new Texture2D(earthDiffuseImage->getInfo());

	Image* earthSpecImage = new Image("images/EarthSpec.png");
	earthSpecTex = new Texture2D(earthSpecImage->getInfo());

	Image* earthNormImage = new Image("images/EarthNormal.png");
	earthNormalMap = new Texture2D(earthNormImage->getInfo());

	Image* earthCloudsImage = new Image("images/earthcloudmap.png");
	earthCloudsTex = new Texture2D(earthCloudsImage->getInfo());

	earth = new Sphere(2, 64, Vector4(1, 1, 1, 1));
	earth->material.diffuseTexture = earthDiffuseTex;
	earth->material.specTexture = earthSpecTex;
	earth->material.normalMap = earthNormalMap;
	earth->material.specularExponent = 500;
	scene->addGameObject(earth);

	clouds = new Sphere(2.01, 64, Vector4(1, 1, 1, 1));
	clouds->material.diffuseTexture = earthCloudsTex;
	scene->addGameObject(clouds);

	mainCam = new Camera();
	mainCam->position.z = 30;
	mainCam->setFOV(10);
	mainCam->setTarget(earth);
	scene->addGameObject(mainCam);

	cameraAnchor = new GameObject();
	cameraAnchor->addChild(mainCam);

	Light* light = new Light();
	light->type = LIGHT_DIRECTIONAL;
	light->rotation = Vector3(0, 120, 0);
	light->color = Vector4(1, 1, 0.9, 1);
	scene->addLight(light);
	scene->addGameObject(light);
    
	scene->ambientLightColor = Vector4(0.05, 0.05, 0.05, 1);
    scene->setActiveCamera(mainCam);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    createObjects();
	scene->init();
    
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void reshape(int width, int height){
	ww= width;
	wh = height;
    
    scene->setAspectRatio((float)width, (float)height);
	
	glViewport(0, 0, width, height);
}

void timer(GLint v) {
	earth->rotation.y += 0.2;
	clouds->rotation.y += 0.18;

	if (!mouseLeftPressed) {
		cameraAnchor->rotation.y += cameraAnchorRotVelocity;
		cameraAnchorRotVelocity *= 0.95;
	}

    glutPostRedisplay();
	glutTimerFunc(1000 / v, timer, v);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0); 
    glutInitWindowSize(ww, wh);
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#else
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
#endif
    glutCreateWindow("OpenGL 3.2");

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    
    init();

    glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 60);

    glutMainLoop();
    return 0;
}
