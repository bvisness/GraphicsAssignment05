//
//  Sphere.h
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment03__Sphere__
#define __Assignment03__Sphere__

#include "RenderedGameObject.h"
#include "GLMiddleman.h"

class Sphere: public RenderedGameObject {
private:
    void initSphere(float radius, int subdiv);
    Vector4 sphereColor;
    int numVertsSphere;
    Vector4* sphereVerts = nullptr;
    Vector3* sphereNormals = nullptr;
	Vector3* sphereTangents = nullptr;
	GLfloat* sphereBitangentSigns = nullptr;
	Vector2* sphereUVs = nullptr;
    Vector4* sphereColors = nullptr;
protected:
    int getNumberOfVertices();
    Vector4* getVertices();
    Vector3* getVertexNormals();
	Vector3* getVertexTangents();
	GLfloat* getVertexBitangentSigns();
	Vector2* getVertexUVs();
    Vector4* getVertexColors();
	void setVertexTangent(int vIndex, Vector3 tangent, int fSign);
public:
	Sphere(float radius, int subdiv, Vector4 color) : RenderedGameObject() {
        sphereColor = color;
        initSphere(radius, subdiv);
    }
};

#endif /* defined(__Assignment03__Sphere__) */
