#version 130

uniform sampler2D texture0;
in vec2 projectedtexCoordVarying;
in vec2 texCoordVarying;
in float overlap;
out vec4 outputColor;

void main()
{
	if(projectedtexCoordVarying.x < 0 || projectedtexCoordVarying.x > 1 || projectedtexCoordVarying.y < 0 || projectedtexCoordVarying.y > 1)
	{
		discard;
	}

	//outputColor = vec4(1, 1, 1, 1);

	// generate radial aperture blend mask
	vec2 centerTex = (texCoordVarying - 0.5) * 2; //[-1,1]
	float falloff = length(centerTex);
	falloff = pow(falloff, 0.25);
	float alpha = clamp(1.0 - falloff, 0,1);

	// generate simple overlap
	//float alpha = 1.0 / overlap;

	outputColor = vec4(texture(texture0, projectedtexCoordVarying).xyz, alpha);
	//outputColor = vec4(projectedtexCoordVarying.x, projectedtexCoordVarying.y, 0, 1);
	//outputColor = vec4(alpha, alpha, alpha, alpha);
}