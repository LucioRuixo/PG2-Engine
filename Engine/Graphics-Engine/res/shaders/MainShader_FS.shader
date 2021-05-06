#version 330 core

const int MAX_POINT_LIGHT_AMOUNT = 4;
const int MAX_SPOTLIGHT_AMOUNT = 4;

struct DirectionalLight
{
	bool null;

	vec3 direction;

	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	bool null;

	vec3 position;

	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Spotlight
{
	bool null;

	vec3 position;
	vec3 direction;

	vec3 diffuse;
	vec3 specular;

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

//Light
uniform vec3 lightingAmbient;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHT_AMOUNT];
uniform Spotlight spotlights[MAX_SPOTLIGHT_AMOUNT];

uniform Material material;

//Camera
uniform vec3 viewPosition;

//Texture
uniform bool textureActive;
uniform sampler2D textureData;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 nNormal, vec3 viewDirection);
vec3 CalculateSpotlight(Spotlight light, vec3 nNormal, vec3 viewDirection);

void main()
{
	vec3 objectColor;
	if (textureActive) objectColor = vec3(texture(textureData, TextureCoordinates));
	else objectColor = color;

	//Ambient
	//-------
	vec3 ambient = lightingAmbient * material.ambient;
	//-------

	vec3 lighting = ambient;

	//Testing
	//-------
	///FragColor = vec4(objectColor * lighting, 1.0f);
	///return;
	//-------

	//if (!lightSourceActive)
	//{
	//	FragColor = vec4(objectColor * ambient, 1.0f);
	//	return;
	//}

	//vec3 lightSourceDirection;
	//if (light.type == Directional) lightSourceDirection = -light.direction;
	//else lightSourceDirection = normalize(light.position - FragmentPosition);

	vec3 nNormal = normalize(Normal);
	vec3 viewDirection = normalize(viewPosition - FragmentPosition);

	//Directional Light
	//-------
	lighting += CalculateDirectionalLight(directionalLight, nNormal, viewDirection);
	//-------

	//Point Lights
	//-------
	for (int i = 0; i < MAX_POINT_LIGHT_AMOUNT; i++) lighting += CalculatePointLight(pointLights[i], nNormal, viewDirection);
	//-------

	//Spotlights
	//-------
	for (int i = 0; i < MAX_SPOTLIGHT_AMOUNT; i++) lighting += CalculateSpotlight(spotlights[i], nNormal, viewDirection);
	//-------

	////Diffuse
	////-------
	//float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	//vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;
	////-------

	////Specular
	////-------
	//vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	//
	//float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	//vec3 specular = light.specular * (material.specular * specularImpact);
	////-------

	////Point light
	////-------
	//if (light.type == Point)
	//{
	//	float distance = length(light.position - FragmentPosition);
	//	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	//
	//	//ambient *= attenuation;
	//	diffuse *= attenuation;
	//	specular *= attenuation;
	//}
	////-------
	//
	////Spotlight
	////-------
	//if (light.type == Spot)
	//{
	//	float theta = dot(lightSourceDirection, -light.direction);
	//	float epsilon = light.innerCutOff - light.outerCutOff;
	//	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
	//
	//	diffuse *= intensity;
	//	specular *= intensity;
	//}
	////-------

	FragColor = vec4(objectColor * lighting, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null) return vec3(0.0f);

	vec3 lightSourceDirection = -light.direction;

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * (material.specular * specularImpact);

	return (diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null) return vec3(0.0f);

	vec3 lightSourceDirection = normalize(light.position - FragmentPosition);

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * (material.specular * specularImpact);

	float distance = length(light.position - FragmentPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;

	return (diffuse + specular);
}

vec3 CalculateSpotlight(Spotlight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null) return vec3(0.0f);

	vec3 lightSourceDirection = normalize(light.position - FragmentPosition);

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * (material.specular * specularImpact);

	float theta = dot(lightSourceDirection, -light.direction);
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
	
	diffuse *= intensity;
	specular *= intensity;

	return (diffuse + specular);
}