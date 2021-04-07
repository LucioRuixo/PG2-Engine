#version 330 core

in vec3 FragmentPosition;
in vec3 Color;
in vec3 Normal;
in vec2 TextureCoordinates;

out vec4 FragColor;

uniform float ambientLightStrenth;
uniform vec3 ambientLightColor;

uniform bool textureActive;
uniform bool lightSourceActive = false;
uniform vec3 lightSourceColor;
uniform vec3 lightSourcePosition;

uniform sampler2D textureData;

void main()
{
	//Vertex color
	//FragColor = vec4(Color, 1.0);

	//Vertex color affected by ambient light
	//FragColor = vec4(Color * lightColor, 1.0f);

	//Texture
	//FragColor = texture(textureData, TextureCoordinates);

	//Texture affected by vertex color
	//FragColor = texture(textureData, TextureCoordinates) * vec4(Color, 1.0);

	//Texture affected by ambient lighting
	//FragColor.x = texture(textureData, TextureCoordinates).x * ambientLightColor.x * ambientLightStrenth;
	//FragColor.y = texture(textureData, TextureCoordinates).y * ambientLightColor.y * ambientLightStrenth;
	//FragColor.z = texture(textureData, TextureCoordinates).z * ambientLightColor.z * ambientLightStrenth;
	//FragColor.w = 1.0f;

	//Texture affected by vertex color and ambient light
	//FragColor = texture(textureData, TextureCoordinates) * vec4(Color, 1.0) * vec4(lightColor, 1.0);

	//Texture affected by ambient and diffuse lighting
	vec3 objectColor;
	if (textureActive)
	{
		objectColor.x = texture(textureData, TextureCoordinates).x;
		objectColor.y = texture(textureData, TextureCoordinates).y;
		objectColor.z = texture(textureData, TextureCoordinates).z;
	}
	else objectColor = Color;

	vec3 ambient = ambientLightColor * ambientLightStrenth;
	
	vec3 diffuse;
	if (lightSourceActive)
	{
		vec3 nNormal = normalize(Normal);
		vec3 lightSourceDirection = normalize(lightSourcePosition - FragmentPosition);
		float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0);
		diffuse = diffuseImpact * lightSourceColor;
	}
	else diffuse = vec3(0.0, 0.0, 0.0);

	FragColor.x = objectColor.x * (ambient.x + diffuse.x);
	FragColor.y = objectColor.y * (ambient.y + diffuse.y);
	FragColor.z = objectColor.z * (ambient.z + diffuse.z);
	FragColor.w = 1.0f;
}