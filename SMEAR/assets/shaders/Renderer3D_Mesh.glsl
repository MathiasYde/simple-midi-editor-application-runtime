// Basic Texture Shader

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in float a_TexIndex;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
} u_CameraBuffer;

layout(std140, binding = 1) uniform Transform
{
	mat4 u_Transform;
} u_TransformBuffer;

struct VertexOutput
{
	vec2 TexCoord;
	float TexIndex;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.TexCoord = a_TexCoord;
	Output.TexIndex = a_TexIndex;

	gl_Position = u_CameraBuffer.u_ViewProjection * u_TransformBuffer.u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

struct VertexOutput
{
	vec2 TexCoord;
	float TexIndex;
};

layout (location = 0) in VertexOutput Input;

layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	switch(int(Input.TexIndex))
	{
		case  0: color = texture(u_Textures[ 0], Input.TexCoord); break;
		case  1: color = texture(u_Textures[ 1], Input.TexCoord); break;
		case  2: color = texture(u_Textures[ 2], Input.TexCoord); break;
		case  3: color = texture(u_Textures[ 3], Input.TexCoord); break;
		case  4: color = texture(u_Textures[ 4], Input.TexCoord); break;
		case  5: color = texture(u_Textures[ 5], Input.TexCoord); break;
		case  6: color = texture(u_Textures[ 6], Input.TexCoord); break;
		case  7: color = texture(u_Textures[ 7], Input.TexCoord); break;
		case  8: color = texture(u_Textures[ 8], Input.TexCoord); break;
		case  9: color = texture(u_Textures[ 9], Input.TexCoord); break;
		case 10: color = texture(u_Textures[10], Input.TexCoord); break;
		case 11: color = texture(u_Textures[11], Input.TexCoord); break;
		case 12: color = texture(u_Textures[12], Input.TexCoord); break;
		case 13: color = texture(u_Textures[13], Input.TexCoord); break;
		case 14: color = texture(u_Textures[14], Input.TexCoord); break;
		case 15: color = texture(u_Textures[15], Input.TexCoord); break;
		case 16: color = texture(u_Textures[16], Input.TexCoord); break;
		case 17: color = texture(u_Textures[17], Input.TexCoord); break;
		case 18: color = texture(u_Textures[18], Input.TexCoord); break;
		case 19: color = texture(u_Textures[19], Input.TexCoord); break;
		case 20: color = texture(u_Textures[20], Input.TexCoord); break;
		case 21: color = texture(u_Textures[21], Input.TexCoord); break;
		case 22: color = texture(u_Textures[22], Input.TexCoord); break;
		case 23: color = texture(u_Textures[23], Input.TexCoord); break;
		case 24: color = texture(u_Textures[24], Input.TexCoord); break;
		case 25: color = texture(u_Textures[25], Input.TexCoord); break;
		case 26: color = texture(u_Textures[26], Input.TexCoord); break;
		case 27: color = texture(u_Textures[27], Input.TexCoord); break;
		case 28: color = texture(u_Textures[28], Input.TexCoord); break;
		case 29: color = texture(u_Textures[29], Input.TexCoord); break;
		case 30: color = texture(u_Textures[30], Input.TexCoord); break;
		case 31: color = texture(u_Textures[31], Input.TexCoord); break;
	}
}
