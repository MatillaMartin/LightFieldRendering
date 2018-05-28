#version 130

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;

uniform mat4 pck;
uniform mat4 mfd;

uniform vec3 origin;
uniform vec3 center;
uniform float aperture;
uniform vec3 focalPoint;
uniform vec3 focalNormal;
uniform float baseline;

in vec4 position;
in vec2 texcoord;

out vec2 projectedtexCoordVarying;
out vec2 texCoordVarying;
out float overlap;

vec3 projectToPlane(vec3 point, vec3 origin, vec3 planePoint, vec3 planeNormal)
{
	vec3 n = planeNormal;
	vec3 w = planePoint - origin;
	vec3 u = normalize(origin - point);
	float length = dot( planeNormal, w ) / dot( planeNormal , u );
	return origin + (length * u);
}

void main()
{	
	// send texture
	texCoordVarying = texcoord;
	// send overlap
	overlap = aperture;

	vec4 modifiedPosition = position;
	vec4 focalPlane = position;

	// place in center, with aperture
	modifiedPosition.xy -= 0.5;
	modifiedPosition.xy *= aperture * baseline;
	modifiedPosition.xy += center.xy;

	// push back to focal plane
	focalPlane.xyz = projectToPlane(modifiedPosition.xyz, origin, focalPoint, focalNormal);

	// project to lightfield camera plane
	vec4 cameraPlane = mfd * focalPlane;

	// get screen coord from camera plane pixels
	vec3 cameraScreen = cameraPlane.xyz / cameraPlane.w;
	cameraScreen.x = (cameraScreen.x + 1) / 2;
	cameraScreen.y = (1 - cameraScreen.y) / 2;

	projectedtexCoordVarying = cameraScreen.xy;

	gl_Position = modelViewProjectionMatrix * modifiedPosition;
}