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

#include <stdio.h>

//store window width and height
int ww = 1000, wh = 700;

//our modelview and perspective matrices
mat4 mv, p;

Scene* scene;

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
	/*exit when the escape key is pressed*/
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

	mainCam = new Camera();
	scene->addGameObject(mainCam);
    
    scene->setActiveCamera(mainCam);
}

void init() {
    /*select clearing (background) color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    createObjects();
	scene->init();
    
    //Only draw the things in the front layer
	glEnable(GL_DEPTH_TEST);
}

//reshape will be called at least once when the window is created,
//so we can handle projection matrix work here
void reshape(int width, int height){
	ww= width;
	wh = height;
	//field of view angle, aspect ratio, closest distance from camera to object, largest distance from camera to object
    
    //send over projection matrix to vertex shader
    scene->setAspectRatio((float)width, (float)height);
	
	glViewport(0, 0, width, height);
}

void timer(GLint v) {
    glutPostRedisplay();
	glutTimerFunc(1000 / v, timer, v);
}

int main(int argc, char **argv)
{
    /*set up window for display*/
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
