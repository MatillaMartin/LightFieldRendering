#version 150

uniform sampler2D texture0;
in vec2 texCoordVarying;
out vec4 outputColor;
 
void main()
{
	//outputColor = vec4(1, 1, 1, 1);
	outputColor = vec4(texture(texture0, texCoordVarying).xyz, 1);
	//outputColor = vec4(texCoordVarying.x, texCoordVarying.y, 0,1);
}