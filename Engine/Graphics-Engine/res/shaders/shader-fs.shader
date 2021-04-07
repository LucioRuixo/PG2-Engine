#version 330 core

in vec3 FragmentPosition;
in vec3 Color;
in vec3 Normal;
in vec2 TextureCoordinates;

out vec4 FragColor;

uniform float ambientLightStrenth;
uniform vec3 ambientLightColor;

uniform bool directionalLightActive = false;
uniform vec3 directionalLightColor;
uniform vec3 directionalLightPosition;

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

	//Texture affected by ambient light
	//FragColor.x = texture(textureData, TextureCoordinates).x * ambientLightColor.x * ambientLightStrenth;
	//FragColor.y = texture(textureData, TextureCoordinates).y * ambientLightColor.y * ambientLightStrenth;
	//FragColor.z = texture(textureData, TextureCoordinates).z * ambientLightColor.z * ambientLightStrenth;
	//FragColor.w = 1.0f;

	//Texture affected by vertex color and ambient light
	//FragColor = texture(textureData, TextureCoordinates) * vec4(Color, 1.0) * vec4(lightColor, 1.0);

	//Texture affected by ambient light and directional light
	vec3 ambient = ambientLightColor * ambientLightStrenth;
	
	vec3 diffuse;
	if (directionalLightActive)
	{
		vec3 nNormal = normalize(Normal);
		vec3 directionalLightDirection = normalize(directionalLightPosition - FragmentPosition);
		float diffuseImpact = max(dot(nNormal, directionalLightDirection), 0.0);
		diffuse = diffuseImpact * directionalLightColor;
	}
	else diffuse = vec3(0.0, 0.0, 0.0);

	//vec3 ambient = vec3(0.1f, 0.1f, 0.1f);
	//vec3 diffuse = vec3(0.5f, 0.5f, 0.5f);
	//FragRGB = vec3(texture(textureData, TextureCoordinates) * (ambient + diffuse));
	//FragColor = vec4(FragRGB, 1.0f);

	FragColor.x = texture(textureData, TextureCoordinates).x * (ambient.x + diffuse.x);
	FragColor.y = texture(textureData, TextureCoordinates).y * (ambient.y + diffuse.y);
	FragColor.z = texture(textureData, TextureCoordinates).z * (ambient.z + diffuse.z);
	FragColor.w = 1.0f;
}