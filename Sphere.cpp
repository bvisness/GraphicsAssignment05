//
//  Sphere.cpp
//  Assignment03
//
//  Created by Benjamin Visness on 10/12/15.
//  Copyright (c) 2015 Benjamin Visness. All rights reserved.
//

#include "Sphere.h"

void Sphere::initSphere(float radius, int subdiv) {
	int latitudeSteps = ceil(subdiv / 2.0);
	int longitudeSteps = subdiv;

    numVertsSphere = 2 * (3 * longitudeSteps) + 6 * longitudeSteps * (latitudeSteps - 2);
    
    sphereVerts = new Vector4[numVertsSphere];
    sphereNormals = new Vector3[numVertsSphere];
	sphereUVs = new Vector2[numVertsSphere];
    sphereColors = new Vector4[numVertsSphere];

	float latitudeStep = M_PI / latitudeSteps;
	float longitudeStep = 2 * M_PI / longitudeSteps;
    
    int k = 0;

	// Top cap
	for (int i = 0; i < longitudeSteps; i++) {
		float longitude = -M_PI + (i * longitudeStep);

		sphereVerts[k] = vec4(0, radius, 0, 1.0);
		sphereNormals[k] = vec3(0, 1, 0);
		k++;

		sphereVerts[k] = vec4(
			radius * sin(longitude) * cos((M_PI / 2) - latitudeStep),
			radius * sin((M_PI / 2) - latitudeStep),
			radius * cos(longitude) * cos((M_PI / 2) - latitudeStep),
			1.0
		);
		sphereNormals[k] = vec3(
			sin(longitude) * cos((M_PI / 2) - latitudeStep),
			sin((M_PI / 2) - latitudeStep),
			cos(longitude) * cos((M_PI / 2) - latitudeStep)
			);
		k++;

		sphereVerts[k] = vec4(
			radius * sin(longitude + longitudeStep) * cos((M_PI / 2) - latitudeStep),
			radius * sin((M_PI / 2) - latitudeStep),
			radius * cos(longitude + longitudeStep) * cos((M_PI / 2) - latitudeStep),
			1.0
		);
		sphereNormals[k] = vec3(
			sin(longitude + longitudeStep) * cos((M_PI / 2) - latitudeStep),
			sin((M_PI / 2) - latitudeStep),
			cos(longitude + longitudeStep) * cos((M_PI / 2) - latitudeStep)
		);
		k++;
	}

	// Body
    for (int i = 1; i < latitudeSteps - 1; i++) {
		float latitude = (-M_PI / 2) + (i * latitudeStep);

        for (float j = 0; j < longitudeSteps && k + 5 < numVertsSphere; j++) {
			float longitude = -M_PI + (j * longitudeStep);

            //triangle 1
			sphereVerts[k] = vec4(
				radius * sin(longitude) * cos(latitude),
				radius * sin(latitude),
				radius * cos(longitude) * cos(latitude),
				1.0
			);
            sphereNormals[k] = vec3(
				sin(longitude) * cos(latitude),
				sin(latitude),
				cos(longitude) * cos(latitude)
			);
            k++;
            
            sphereVerts[k] = vec4(
				radius * sin(longitude) * cos(latitude + latitudeStep),
				radius * sin(latitude + latitudeStep),
				radius * cos(longitude) * cos(latitude + latitudeStep),
				1.0
			);
            sphereNormals[k] = vec3(
				sin(longitude) * cos(latitude + latitudeStep),
				sin(latitude + latitudeStep),
				cos(longitude) * cos(latitude + latitudeStep)
			);
            k++;
            
            sphereVerts[k] = vec4(
				radius * sin(longitude + longitudeStep) * cos(latitude + latitudeStep),
				radius * sin(latitude + latitudeStep),
				radius * cos(longitude + longitudeStep) * cos(latitude + latitudeStep),
				1.0
			);
            sphereNormals[k] = vec3(
				sin(longitude + longitudeStep) * cos(latitude + latitudeStep),
				sin(latitude + latitudeStep),
				cos(longitude + longitudeStep) * cos(latitude + latitudeStep)
			);
            k++;
            
			//triangle 2
			sphereVerts[k] = vec4(
				radius * sin(longitude) * cos(latitude),
				radius * sin(latitude),
				radius * cos(longitude) * cos(latitude),
				1.0
				);
			sphereNormals[k] = vec3(
				sin(longitude) * cos(latitude),
				sin(latitude),
				cos(longitude) * cos(latitude)
				);
			k++;

			sphereVerts[k] = vec4(
				radius * sin(longitude + longitudeStep) * cos(latitude + latitudeStep),
				radius * sin(latitude + latitudeStep),
				radius * cos(longitude + longitudeStep) * cos(latitude + latitudeStep),
				1.0
				);
			sphereNormals[k] = vec3(
				sin(longitude + longitudeStep) * cos(latitude + latitudeStep),
				sin(latitude + latitudeStep),
				cos(longitude + longitudeStep) * cos(latitude + latitudeStep)
				);
			k++;

			sphereVerts[k] = vec4(
				radius * sin(longitude + longitudeStep) * cos(latitude),
				radius * sin(latitude),
				radius * cos(longitude + longitudeStep) * cos(latitude),
				1.0
				);
			sphereNormals[k] = vec3(
				sin(longitude + longitudeStep) * cos(latitude),
				sin(latitude),
				cos(longitude + longitudeStep) * cos(latitude)
				);
			k++;
        }
    }

	// Bottom cap
	for (int i = 0; i < longitudeSteps; i++) {
		float longitude = -M_PI + (i * longitudeStep);

		sphereVerts[k] = vec4(0, -radius, 0, 1.0);
		sphereNormals[k] = vec3(0, -1, 0);
		k++;

		sphereVerts[k] = vec4(
			radius * sin(longitude) * cos((-M_PI / 2) + latitudeStep),
			radius * sin((-M_PI / 2) + latitudeStep),
			radius * cos(longitude) * cos((-M_PI / 2) + latitudeStep),
			1.0
		);
		sphereNormals[k] = vec3(
			sin(longitude) * cos(-M_PI / 2 + latitudeStep),
			sin((-M_PI / 2) + latitudeStep),
			cos(longitude) * cos(-M_PI / 2 + latitudeStep)
		);
		k++;

		sphereVerts[k] = vec4(
			radius * sin(longitude + longitudeStep) * cos((-M_PI / 2) + latitudeStep),
			radius * sin((-M_PI / 2) + latitudeStep),
			radius * cos(longitude + longitudeStep) * cos((-M_PI / 2) + latitudeStep),
			1.0
		);
		sphereNormals[k] = vec3(
			sin(longitude + longitudeStep) * cos((-M_PI / 2) + latitudeStep),
			sin((-M_PI / 2) + latitudeStep),
			cos(longitude + longitudeStep) * cos((-M_PI / 2) + latitudeStep)
		);
		k++;
	}
    
    for (int i = 0; i < numVertsSphere; i++) {
        sphereColors[i] = sphereColor;
    }
}

int Sphere::getNumberOfVertices() {
    return numVertsSphere;
}

Vector4* Sphere::getVertices() {
    return sphereVerts;
}

Vector3* Sphere::getVertexNormals() {
    return sphereNormals;
}

Vector2* Sphere::getVertexUVs() {
	return sphereUVs;
}

Vector4* Sphere::getVertexColors() {
    return sphereColors;
}
