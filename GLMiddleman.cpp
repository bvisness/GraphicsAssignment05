//
//  GLMiddleman.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/29/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include <string>

#include "GLMiddleman.h"

GLfloat* floatArrayWithValue(int size, GLfloat value) {
    GLfloat* result = new GLfloat[size];
    for (int i = 0; i < size; i++) {
        result[i] = value;
    }
    return result;
}

GLMiddleman::GLMiddleman() {
    program = InitShader("vshader-phongshading.glsl", "fshader-phongshading.glsl");
    glUseProgram(program);
    
    //grab pointers for our uniforms
    model_view = glGetUniformLocation(program, "uModelView");
    projection = glGetUniformLocation(program, "uProjection");
    uAmbientLight = glGetUniformLocation(program, "uAmbientLight");
    uLightType = glGetUniformLocation(program, "uLightType");
    uLightColor = glGetUniformLocation(program, "uLightColor");
    uLightPosition = glGetUniformLocation(program, "uLightPosition");
    uLightDirection = glGetUniformLocation(program, "uLightDirection");
	uLightSpotAngleCos = glGetUniformLocation(program, "uLightSpotAngleCos");
}

void GLMiddleman::updateProjectionMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(projection, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::updateModelViewMatrix(mat4 newMatrix) {
    glUniformMatrix4fv(model_view, 1, GL_TRUE, newMatrix);
}

void GLMiddleman::bufferObject(ObjectInfo object) {
	if (object.vao == UINT_MAX) {
		warnWithMessage("In GLMiddleman::bufferObject(): VAO was not set, object not buffered.");
		return;
	}
	if (object.vbo == nullptr) {
		warnWithMessage("In GLMiddleman::bufferObject(): VBO was not set, object not buffered.");
		return;
	}
	if (object.numberOfVertices > 0) {
		if (object.vertices == nullptr) {
			warnWithMessage("In GLMiddleman::bufferObject(): numberOfVertices was nonzero and vertices was not set, object not buffered.");
			return;
		}
		if (object.vertexNormals == nullptr) {
			warnWithMessage("In GLMiddleman::bufferObject(): numberOfVertices was nonzero and vertexNormals was not set, object not buffered.");
			return;
		}
	}

	glBindVertexArray(object.vao);

	int k = 0;

	{
		// Vertex positions
		int dataCount = 4;	
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * (sizeof(GLfloat)* dataCount), object.vertices, GL_STATIC_DRAW);
		vPosition = glGetAttribLocation(program, "vPosition");
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;

	{
		// Vertex normal vectors
		int dataCount = 3;
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * (sizeof(GLfloat)* dataCount), object.vertexNormals, GL_STATIC_DRAW);
		vNormal = glGetAttribLocation(program, "vNormal");
		glEnableVertexAttribArray(vNormal);
		glVertexAttribPointer(vNormal, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;

	{
		// Vertex ambient colors
		int dataCount = 4;
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * (sizeof(GLfloat)* dataCount), object.vertexColors, GL_STATIC_DRAW);
		vAmbientDiffuseColor = glGetAttribLocation(program, "vAmbientDiffuseColor");
		glEnableVertexAttribArray(vAmbientDiffuseColor);
		glVertexAttribPointer(vAmbientDiffuseColor, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;

	{
		// Vertex diffuse amount
		int dataCount = 1;
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * sizeof(GLfloat), floatArrayWithValue(object.numberOfVertices, object.material.diffuseAmount), GL_STATIC_DRAW);
		vDiffuseAmount = glGetAttribLocation(program, "vDiffuseAmount");
		glEnableVertexAttribArray(vDiffuseAmount);
		glVertexAttribPointer(vDiffuseAmount, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;

	{
		// Vertex specular amount
		int dataCount = 1;
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * sizeof(GLfloat), floatArrayWithValue(object.numberOfVertices, object.material.specularAmount), GL_STATIC_DRAW);
		vSpecularAmount = glGetAttribLocation(program, "vSpecularAmount");
		glEnableVertexAttribArray(vSpecularAmount);
		glVertexAttribPointer(vSpecularAmount, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;

	{
		// Vertex specular exponents
		int dataCount = 1;
		glBindBuffer(GL_ARRAY_BUFFER, object.vbo[k]);
		glBufferData(GL_ARRAY_BUFFER, object.numberOfVertices * sizeof(GLfloat), floatArrayWithValue(object.numberOfVertices, object.material.specularExponent), GL_STATIC_DRAW);
		vSpecularExponent = glGetAttribLocation(program, "vSpecularExponent");
		glEnableVertexAttribArray(vSpecularExponent);
		glVertexAttribPointer(vSpecularExponent, dataCount, GL_FLOAT, GL_FALSE, 0, 0);
	}
	k++;
}

int GLMiddleman::getLightId() {
	if (numRegisteredLights >= MAX_LIGHTS) {
		warnWithMessage("Maximum of " + std::to_string(MAX_LIGHTS) + " lights reached. Results may be unexpected.");
		return 0;
	}

	int id = numRegisteredLights;
	numRegisteredLights++;
	return id;
}

void GLMiddleman::bufferLights() {
	glUniform4fv(uLightPosition, MAX_LIGHTS, (const GLfloat*)lightPositions);
	glUniform4fv(uLightDirection, MAX_LIGHTS, (const GLfloat*)lightDirections);
	glUniform1fv(uLightSpotAngleCos, MAX_LIGHTS, (const GLfloat*)lightSpotAngleCosines);
	glUniform4fv(uLightColor, MAX_LIGHTS, (const GLfloat*)lightColors);
	glUniform1iv(uLightType, MAX_LIGHTS, (const GLint*)lightTypes);
}
