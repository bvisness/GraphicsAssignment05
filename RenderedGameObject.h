//
//  RenderedGameObject.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/26/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment04__RenderedGameObject__
#define __Assignment04__RenderedGameObject__

#include "mikktspace.h"

#include "VisnessUtil.h"
#include "VisnessGL.h"
#include "Material.h"
#include "GameObject.h"

#ifndef VBO_COUNT
#define VBO_COUNT 9 // position, normal vector, tangents, bitangent signs, uv, ambient and diffuse colors, diffuse amount, specular amount, specular exponent
#endif

class RenderedGameObject : public GameObject {
private:
	SMikkTSpaceContext mikkTContext;
	SMikkTSpaceInterface mikkTInterface;
protected:
	GLuint vao;
	GLuint vbo[VBO_COUNT];

	void drawGameObject();
	void customInitGameObject();
public:
	GLuint getVAO();
	Material material;

	virtual int getNumberOfVertices() = 0;
	virtual Vector4* getVertices() = 0;
	virtual Vector3* getVertexNormals() = 0;
	virtual Vector3* getVertexTangents() = 0;
	virtual GLfloat* getVertexBitangentSigns() = 0;
	virtual Vector2* getVertexUVs() = 0;
	virtual Vector4* getVertexColors() = 0;

	virtual void setVertexTangent(int vIndex, Vector3 tangent, int fSign) = 0;
};

#endif
