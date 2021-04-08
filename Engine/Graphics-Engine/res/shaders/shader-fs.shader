#version 330 core

in vec3 FragmentPosition;
in vec3 Color;
in vec3 Normal;
in vec2 TextureCoordinates;

out vec4 FragColor;

uniform float ambientLightStrength;
uniform vec3 ambientLightColor;

uniform bool lightSourceActive = false;
uniform vec3 lightSourceColor;
uniform vec3 lightSourcePosition;

uniform float specularStrength;
uniform vec3 viewPosition;

uniform bool textureActive;
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
	//FragColor.x = texture(textureData, TextureCoordinates).x * ambientLightColor.x * ambientLightStrength;
	//FragColor.y = texture(textureData, TextureCoordinates).y * ambientLightColor.y * ambientLightStrength;
	//FragColor.z = texture(textureData, TextureCoordinates).z * ambientLightColor.z * ambientLightStrength;
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

	//Ambient
	vec3 ambient = ambientLightColor * ambientLightStrength;
	
	vec3 lightSourceDirection = normalize(lightSourcePosition - FragmentPosition);
	vec3 nNormal = normalize(Normal);

	//Diffuse
	vec3 diffuse;
	if (lightSourceActive)
	{
		float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
		diffuse = diffuseImpact * lightSourceColor;
	}
	else diffuse = vec3(0.0f, 0.0f, 0.0f);

	//Specular
	vec3 specular;
	if (lightSourceActive)
	{
		vec3 viewDirection = normalize(viewPosition - FragmentPosition);
		vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);

		float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
		specular = specularStrength * specularImpact * lightSourceColor;
	}
	else specular = vec3(0.0f, 0.0f, 0.0f);

	FragColor.x = objectColor.x * (/*ambient.x +*/ diffuse.x /*specular.x*/);
	FragColor.y = objectColor.y * (/*ambient.y +*/ diffuse.y /*specular.y*/);
	FragColor.z = objectColor.z * (/*ambient.z +*/ diffuse.z /*specular.z*/);
	FragColor.w = 1.0f;
}