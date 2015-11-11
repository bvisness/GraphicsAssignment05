//
//  Scene.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/1/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__Scene__
#define __Assignment03__Scene__

#include <vector>

#include "GameObject.h"
#include "GLMiddleman.h"
#include "Camera.h"
#include "Light.h"

/**
 * The entire scene to be displayed.
 */
class Scene {
protected:
    std::vector<GameObject*> gameObjects = std::vector<GameObject*>();
	std::vector<Light*> lights = std::vector<Light*>();
    Camera* activeCamera = nullptr;
    bool initialized = false;
public:
    GLMiddleman* middleman = nullptr;

	Vector4 ambientLightColor = Vector4(0.1, 0.1, 0.1, 1);

    Scene();
    Scene(GLMiddleman* newMiddleman);
    
    void addGameObject(GameObject* obj);
	void addLight(Light* light);
    void init();
    void draw();
    
    Camera* getActiveCamera();
    void setActiveCamera(Camera* cam);
    
    GLfloat aspect = 1;
    void setAspectRatio(GLfloat aspect);
    void setAspectRatio(GLfloat width, GLfloat height);
    
    /**
     * Take the projection matrix from the active
     * camera and ship it over to the graphics card.
     */
    void updateProjectionMatrix();
};

#endif /* defined(__Assignment03__Scene__) */
