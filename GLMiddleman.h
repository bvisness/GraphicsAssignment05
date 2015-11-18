//
//  GLMiddleman.h
//  Assignment02
//
//  Created by Benjamin Visness on 9/29/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#ifndef __Assignment02__GLMiddleman__
#define __Assignment02__GLMiddleman__

#include "VisnessGL.h"
#include "VisnessUtil.h"
#include "Material.h"

#ifndef MAX_LIGHTS
#define MAX_LIGHTS 10
#endif

#ifndef MAX_TEXTURES
#define MAX_TEXTURES 10
#endif

/**
 * A class that handles shipping data over to
 * the graphics card using OpenGL methods.
 */
class GLMiddleman {
private:
	int numRegisteredLights = 0;
public:
    GLMiddleman();
    GLuint program;
    GLuint model_view;
    GLuint projection;
    GLuint vPosition;
    GLuint vNormal;
	GLuint vTexCoord;
    GLuint vAmbientDiffuseColor;
    GLfloat vDiffuseAmount;
    GLfloat vSpecularAmount;
    GLfloat vSpecularExponent;
    GLuint uAmbientLight;
    GLuint uLightType;
    GLuint uLightColor;
    GLuint uLightPosition;
    GLuint uLightDirection;
	GLuint uLightSpotAngleCos;
	GLuint uTexture;

	Vector4 lightPositions[MAX_LIGHTS];
	Vector4 lightDirections[MAX_LIGHTS];
	Vector4 lightColors[MAX_LIGHTS];
	GLint lightTypes[MAX_LIGHTS];
	GLfloat lightSpotAngleCosines[MAX_LIGHTS];
	GLuint textureNames[MAX_TEXTURES];
    
    void updateProjectionMatrix(mat4 newMatrix);
    void updateModelViewMatrix(mat4 newMatrix);

	struct ObjectInfo {
		GLuint vao = UINT_MAX;
		GLuint* vbo = nullptr;
		int unsigned numberOfVertices = 0;
		Vector4* vertices = nullptr;
		Vector3* vertexNormals = nullptr;
		Vector2* vertexUVs = nullptr;
		Vector4* vertexColors = nullptr;
		Material material = Material();
	};

    void bufferObject(ObjectInfo object);

	int getLightId();
	void bufferLights();
};

#endif /* defined(__Assignment02__GLMiddleman__) */
