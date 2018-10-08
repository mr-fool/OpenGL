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
	vec4 color;
	float lum;


    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	if (colorState == 1) { // normal color
		// don't do a single thing you big silly
	}
	if (colorState == 2) { // b&w variant 1
		lum = (color.x * 0.333) + (color.y * 0.333) + (color.z * 0.333);
		color.x = lum;
		color.y = lum;
		color.z = lum;
	}
	if (colorState == 3) { // b&w variant 2
		lum = (color.x * 0.299) + (color.y * 0.587) + (color.z * 0.114); // you're the best around nothins gonna ever keep you down
		color.x = lum;
		color.y = lum;
		color.z = lum;
	}
	if (colorState == 4) { // b&w variant 3
		lum = (color.x * 0.213) + (color.y * 0.715) + (color.z * 0.072);
		color.x = lum;
		color.y = lum;
		color.z = lum;
	}
	vec3 col = mix(vec3(0.2), texture(imageTexture, uv).xyz,  vec3(texture(imageTexture, uv).a)); 
	FragmentColour = vec4(col, 1.0);
}
