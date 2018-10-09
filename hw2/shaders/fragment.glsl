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
	vec3 color;
	float lum;

	vec3 col = mix(vec3(0.2), texture(imageTexture, uv).xyz,  vec3(texture(imageTexture, uv).a)); 
    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	if (colorState == 1) { // normal color
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 2) { // b&w variant 1
		lum = (col.x * 0.333) + (col.y * 0.333) + (col.z * 0.333);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 3) { // b&w variant 2
		lum = (col.x * 0.299) + (col.y * 0.587) + (col.z * 0.114); // you're the best around nothins gonna ever keep you down
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 4) { // b&w variant 3
		lum = (col.x * 0.213) + (col.y * 0.715) + (col.z * 0.072);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	//FragmentColour = vec4(col, 1.0);
}
