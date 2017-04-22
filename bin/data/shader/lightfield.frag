#version 150

uniform sampler2D texture;
in vec2 texCoordVarying;
out vec4 outputColor;
 
void main()
{
	outputColor = vec4(1, 1, 1, 1);
	//outputColor = vec4(texture2D(texture, texCoordVarying).xyz, 1);
}