#version 150

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;

uniform mat4 center;
uniform float aperture;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;

void main()
{	
	// send texture
	texCoordVarying = texcoord;

	vec4 modifiedPosition = position;

	modifiedPosition.xy -= 0.5;
	modifiedPosition.xy *= aperture * 2.0;
	modifiedPosition.xy += center[3].xy / center[3].w;

	gl_Position = modelViewProjectionMatrix * modifiedPosition;
}