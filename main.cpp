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

Scene* scene;

Sphere* earth;

Camera* mainCam;

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

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
		exit(0);
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
	Texture2D* earthDiffuseTex = new Texture2D(earthDiffuseImage->getInfo());

	Image* earthSpecImage = new Image("images/EarthSpec.png");
	Texture2D* earthSpecTex = new Texture2D(earthSpecImage->getInfo());

	earth = new Sphere(2, 64, Vector4(1, 1, 1, 1));
	earth->material.diffuseTexture = earthDiffuseTex;
	earth->material.specTexture = earthSpecTex;
	scene->addGameObject(earth);

	mainCam = new Camera();
	mainCam->position.z = 30;
	mainCam->setFOV(10);
	mainCam->setTarget(earth);
	scene->addGameObject(mainCam);

	Light* light = new Light();
	light->type = LIGHT_DIRECTIONAL;
	light->rotation = Vector3(0, 120, 0);
	light->color = Vector4(1, 1, 1, 1);
	scene->addLight(light);
	scene->addGameObject(light);
    
    scene->setActiveCamera(mainCam);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    createObjects();
	scene->init();
    
	glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height){
	ww= width;
	wh = height;
    
    scene->setAspectRatio((float)width, (float)height);
	
	glViewport(0, 0, width, height);
}

void timer(GLint v) {
	earth->rotation.y += 0.3;

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif
    glutCreateWindow("OpenGL 3.2");

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 60);

    glutMainLoop();
    return 0;
}
