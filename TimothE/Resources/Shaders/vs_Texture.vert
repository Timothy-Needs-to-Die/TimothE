#version 430 core

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
};

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_LightLevel;
layout(location = 4) in float a_TexIndex;
layout(location = 5) in float a_TilingFactor;
layout(location = 6) in int a_EntityID;

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat int LightLevel;
layout (location = 4) out flat float v_TexIndex;
layout (location = 5) out flat int v_EntityID;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	Output.TilingFactor = a_TilingFactor;
	v_TexIndex = a_TexIndex;
	v_EntityID = a_EntityID;
	LightLevel = a_LightLevel;

	gl_Position = view * vec4(a_Position, 1.0);
}