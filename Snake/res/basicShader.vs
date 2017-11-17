#version 330

layout(location = 0) in vec3 position;

uniform mat4 transform;
uniform vec3 color;

out vec4 output_color;

void main()
{
	output_color = vec4(color, 1.0);
	gl_Position = transform * vec4(position, 1.0);
}