//
//  RenderedGameObject.cpp
//  Assignment02
//
//  Created by Benjamin Visness on 9/26/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "RenderedGameObject.h"
#include "Scene.h"

int getNumberOfFaces(const SMikkTSpaceContext* pContext) {
	RenderedGameObject* obj = (RenderedGameObject*)pContext->m_pUserData;
	return obj->getNumberOfVertices() / 3;
}

int getNumVerticesOfFace(const SMikkTSpaceContext* pContext, int iFace) {
	return 3;
}

void getVertexPosition(const SMikkTSpaceContext* pContext, float fvPosOut[], const int iFace, const int iVert) {
	RenderedGameObject* obj = (RenderedGameObject*)pContext->m_pUserData;
	Vector4 position = obj->getVertices()[(iFace * 3) + iVert];
	fvPosOut[0] = position.x;
	fvPosOut[1] = position.y;
	fvPosOut[2] = position.z;
}

void getVertexNormal(const SMikkTSpaceContext* pContext, float fvNormOut[], const int iFace, const int iVert) {
	RenderedGameObject* obj = (RenderedGameObject*)pContext->m_pUserData;
	Vector3 normal = obj->getVertexNormals()[(iFace * 3) + iVert];
	fvNormOut[0] = normal.x;
	fvNormOut[1] = normal.y;
	fvNormOut[2] = normal.z;
}

void getVertexTexCoord(const SMikkTSpaceContext* pContext, float fvTexcOut[], const int iFace, const int iVert) {
	RenderedGameObject* obj = (RenderedGameObject*)pContext->m_pUserData;
	Vector2 texCoord = obj->getVertexUVs()[(iFace * 3) + iVert];
	fvTexcOut[0] = texCoord.x;
	fvTexcOut[1] = texCoord.y;
}

void setTSpaceBasic(const SMikkTSpaceContext* pContext, const float fvTangent[], const float fSign, const int iFace, const int iVert) {
	RenderedGameObject* obj = (RenderedGameObject*)pContext->m_pUserData;
	Vector3 tangent = Vector3(fvTangent[0], fvTangent[1], fvTangent[2]);
	obj->setVertexTangent((iFace * 3) + iVert, tangent, fSign);
}

void RenderedGameObject::customInitGameObject() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(VBO_COUNT, vbo);

	GLMiddleman::ObjectInfo object = GLMiddleman::ObjectInfo();
	object.vao = vao;
	object.vbo = vbo;
	object.numberOfVertices = getNumberOfVertices();
	object.vertices = getVertices();
	object.vertexNormals = getVertexNormals();
	object.vertexTangents = getVertexTangents();
	object.vertexBitangentSigns = getVertexBitangentSigns();
	object.vertexUVs = getVertexUVs();
	object.vertexColors = getVertexColors();
	object.material = material;

	// Process normals to get tangents
	mikkTInterface.m_getNumFaces = getNumberOfFaces;
	mikkTInterface.m_getNumVerticesOfFace = getNumVerticesOfFace;
	mikkTInterface.m_getPosition = getVertexPosition;
	mikkTInterface.m_getNormal = getVertexNormal;
	mikkTInterface.m_getTexCoord = getVertexTexCoord;
	mikkTInterface.m_setTSpaceBasic = setTSpaceBasic;
	mikkTContext.m_pInterface = &mikkTInterface;
	mikkTContext.m_pUserData = this;
	genTangSpaceDefault(&mikkTContext);

	scene->middleman->bufferObject(object);
}

GLuint RenderedGameObject::getVAO() {
	return vao;
}

void RenderedGameObject::drawGameObject() {
	mat4 mv = getModelViewMatrix();

	scene->middleman->updateModelViewMatrix(mv);
	glBindVertexArray(vao);
	scene->middleman->updateMaterialUniforms(material);
	glDrawArrays(GL_TRIANGLES, 0, getNumberOfVertices());
}
