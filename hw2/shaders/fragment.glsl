// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec2 uv;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2DRect imageTexture;

//greyscale
uniform int colorState;
void main(void)
{

	vec3 col = mix(vec3(0.2), texture(imageTexture, uv).xyz,  vec3(texture(imageTexture, uv).a)); 
	FragmentColour = vec4(col, 1.0);
}
