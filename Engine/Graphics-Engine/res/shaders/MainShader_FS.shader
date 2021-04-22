#version 330 core

//Light types:
const int Directional = 0;
const int Point = 1;
const int Spot = 2;

struct Light
{
	int type;

	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float innerCutOff;
	float outerCutOff;
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

	if (!lightSourceActive)
	{
		FragColor = vec4(objectColor * ambient, 1.0f);
		return;
	}

	vec3 lightSourceDirection;
	if (light.type == Directional) lightSourceDirection = -light.direction;
	else lightSourceDirection = normalize(light.position - FragmentPosition);

	vec3 nNormal = normalize(Normal);

	//Diffuse
	//-------
	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * (material.specular * diffuseImpact);
	//-------

	//Specular
	//-------
	vec3 viewDirection = normalize(viewPosition - FragmentPosition);
	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);

	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * (material.specular * specularImpact);
	//-------

	//Point light
	//-------
	if (light.type == Point)
	{
		float distance = length(light.position - FragmentPosition);
		float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}
	//-------

	//Spotlight
	//-------
	if (light.type == Spot)
	{
		float theta = dot(lightSourceDirection, -light.direction);
		float epsilon = light.innerCutOff - light.outerCutOff;
		float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

		diffuse *= intensity;
		specular *= intensity;
	}
	//-------

	vec3 lighting = vec3(ambient + diffuse + specular);
	FragColor = vec4(objectColor * lighting, 1.0f);
}