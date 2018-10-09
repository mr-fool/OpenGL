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

//sobel
uniform int edgeState;

void main(void)
{
	float lum;

	vec3 col = mix(vec3(0.2), texture(imageTexture, uv).xyz,  vec3(texture(imageTexture, uv).a)); 
	vec4 color = vec4(col,1.0);

    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	if (colorState == 1) { // normal color
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 2) { 
		lum = (col.x * 0.333) + (col.y * 0.333) + (col.z * 0.333);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 3) { 
		lum = (col.x * 0.299) + (col.y * 0.587) + (col.z * 0.114); // you're the best around nothins gonna ever keep you down
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 4) {
		lum = (col.x * 0.213) + (col.y * 0.715) + (col.z * 0.072);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 5) {
		lum = (1 - col.x) + (1 - col.y) + (1 - col.z);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	if (colorState == 6) {
		lum = (col.x *0.393) + (col.y* 0.769) + (col.z* 0.189);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	//FragmentColour = vec4(col, 1.0);

	//Edge Effects
	mat3 vSobel;
	mat3 hSobel;
	mat3 uSharp;

	// Vertical Sobel
	vSobel[0] = vec3(1,  0,  -1);
	vSobel[1] = vec3(2,  0,  -2);
	vSobel[2] = vec3(1,  0,  -1);

	// Horizontal Sobel
	hSobel[0] = vec3(-1, -2, -1);
	hSobel[1] = vec3( 0,  0,  0);
	hSobel[2] = vec3( 1,  2,  1);

	// Unsharp Mask
	uSharp[0] = vec3( 0, -1,  0);
	uSharp[1] = vec3(-1,  5, -1);
	uSharp[2] = vec3( 0, -1,  0);

	color = texture(imageTexture, uv);
	if (edgeState == 1) { //no effect
		FragmentColour = vec4(col, 1.0);
	}
	if (edgeState == 2) {
		color = vec4(0.0);
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				color += texture(imageTexture, (uv + vec2((i-1)/1024, (j-1)/1024))) * vSobel[i][j];
			}
		}
		color = abs(color); // stay positive 
		FragmentColour = color;
	}

}
