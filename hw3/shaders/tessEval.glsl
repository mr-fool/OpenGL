#version 410

layout(isolines) in;

in vec3 teColour[];

out vec3 color;

uniform int mode = 1;

void main()
{
	float u = gl_TessCoord.x;

	float b0 = 1.0-u;
	float b1 = u;
	if (mode == 1) {
		gl_Position = b0 * b0 * gl_in[0].gl_Position + 2 * b1 * b0 * gl_in[1].gl_Position + b1 * b1 * gl_in[2].gl_Position;
	}
	if (mode == 2) {
		gl_Position = b0 * b0 * b0 * gl_in[0].gl_Position + 3 * b0 * b0 * b1 * gl_in[1].gl_Position + 3 * b1 * b1 * b0 * gl_in[2].gl_Position + b1 * b1 * b1 * gl_in[3].gl_Position;
	}


}
