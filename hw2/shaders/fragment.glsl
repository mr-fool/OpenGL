// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

//#define P(X,Y) texture(imageTexture, (uv+vec2(X,Y))).xyz
#define P(X,Y) mix(vec3(0.2), texture(imageTexture, (uv+vec2(X,Y))).xyz, vec3(texture(imageTexture, uv+vec2(X,Y)).a) )

// interpolated colour received from vertex stage
in vec2 uv;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2DRect imageTexture;

//greyscale
uniform int colorState;

//sobel
uniform int edgeState;

vec3 apply3x3Kernel(float kernel[9], vec2 uv)
{
    return kernel[0] * P(-1,1) + kernel[1] * P(0,1) + kernel[2] * P(1,1) +
        kernel[3] * P(-1,0) + kernel[4] * P(0,0) + kernel[5] * P(1,0) +
        kernel[6] * P(-1,-1) + kernel[7] * P(0,-1) + kernel[8] * P(1,-1);
}

//Gaussian Blur
float gBlur(int x, int y, float o) {
	return (1/(2*3.141592653589793238462643383*o*o))*pow(2.718281828459045235360287471, -((x*x)+(y*y))/(2*o*o)); //cant use M_PI import for some reason
}

void main(void)
{
	float lum;

	vec3 col = mix(vec3(0.2), texture(imageTexture, uv).xyz,  vec3(texture(imageTexture, uv).a)); 
	//vec4 color = mix(vec4(0.2), texture(imageTexture, uv).xyz,  vec4(texture(imageTexture, uv).a));

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
		//vec3 lum1 = vec3(1.0)/3.0;
		//col = vec3(dot(lum1, col));
		FragmentColour = vec4(col, 1.0);
	}
	else if (colorState == 3) { 
		lum = (col.x * 0.299) + (col.y * 0.587) + (col.z * 0.114); // you're the best around nothins gonna ever keep you down
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	else if (colorState == 4) {
		lum = (col.x * 0.213) + (col.y * 0.715) + (col.z * 0.072);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	else if (colorState == 5) {
		lum = (1 - col.x) + (1 - col.y) + (1 - col.z);
		col.x = lum;
		col.y = lum;
		col.z = lum;
		FragmentColour = vec4(col, 1.0);
	}
	else if (colorState == 6) {
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

	//color = texture(imageTexture, uv);
	if (edgeState == 1) { //no effect
		FragmentColour = vec4(col, 1.0);
	}
	/*if (edgeState == 2) {
		color = vec4(0.0);
		
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				color += texture(imageTexture, (uv + vec2((i-1)/1024, (j-1)/1024))) * vSobel[i][j];
			}
		}
		color = abs(color); // stay positive 
		color.a = 0.3;
		FragmentColour = color;
	}*/
	col = apply3x3Kernel(dx, uv);
	FragmentColour = vec4(abs(col),1.0);
}
