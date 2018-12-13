// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUV;

// output to be interpolated between vertices and passed to the fragment stage
out vec2 uv;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main()
{
	vec4 wPos = M * vec4(VertexPosition, 1.0f);
	gl_Position = P * V * wPos;	
	
    // assign vertex position without modification
	// gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);

    // assign output colour to be interpolated
    // uv = VertexUV;
}
