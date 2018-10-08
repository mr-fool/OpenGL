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

uniform vec2 offset; // x and y offset
uniform float theta; // angle of rotation

void main()
{
    // assign vertex position without modification
    gl_Position = vec4(VertexPosition.xy, 0.0, 1.0);
    
    //rotation
	mat2 rMatrix;
	rMatrix[0] = vec2(cos(theta), -sin(theta));
	rMatrix[1] = vec2(sin(theta), cos(theta));

	float x = (VertexPosition.x + offset.x); 
	float y = (VertexPosition.y + offset.y);
	vec2 pos = vec2(x, y) * rMatrix;
    // assign output colour to be interpolated
    uv = VertexUV;
}
