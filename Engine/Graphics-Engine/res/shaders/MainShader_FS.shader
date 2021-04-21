#version 330 core

//Light types:
const int Directional = 0;
const int Point       = 1;
const int Spot        = 2;

struct Light
{
	int type;

	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 FragmentPosition;
in vec3 Normal;
in vec2 TextureCoordinates;

out vec4 FragColor;

//Object
uniform vec3 color;

//Light source
uniform bool lightSourceActive = false;
uniform Light light;
uniform Material material;

//Camera
uniform vec3 viewPosition;

//Texture
uniform bool textureActive;
uniform sampler2D textureData;

void main()
{
	vec3 objectColor;
	if (textureActive) objectColor = vec3(texture(textureData, TextureCoordinates));
	else objectColor = color;

	//Ambient
	//-------
	vec3 ambient = light.ambient * material.ambient;
	//-------
	
	vec3 lightSourceDirection;
	switch (light.type)
	{
	case Directional:
		lightSourceDirection = -light.direction;
		break;
	case Point:
	case Spot:
		lightSourceDirection = normalize(light.position - FragmentPosition);
		break;
	}

	vec3 nNormal = normalize(Normal);

	//Diffuse
	//-------
	vec3 diffuse;
	if (lightSourceActive)
	{
		float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);

		diffuse = light.diffuse * (material.specular * diffuseImpact);
	}
	else diffuse = vec3(0.0f, 0.0f, 0.0f);
	//-------

	//Specular
	//-------
	vec3 specular;
	if (lightSourceActive)
	{
		vec3 viewDirection = normalize(viewPosition - FragmentPosition);
		vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	
		float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
		specular = light.specular * (material.specular * specularImpact);
	}
	else specular = vec3(0.0f, 0.0f, 0.0f);

	vec3 lighting = vec3(ambient + diffuse + specular);
	FragColor = vec4(objectColor * lighting, 1.0f);
	//-------
}