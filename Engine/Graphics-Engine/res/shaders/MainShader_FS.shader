#version 330 core

const int MAX_POINT_LIGHT_AMOUNT = 4;
const int MAX_SPOTLIGHT_AMOUNT = 4;

struct DirectionalLight
{
	bool null;
	bool on;

	vec3 direction;

	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	bool null;
	bool on;

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
	bool on;

	vec3 position;
	vec3 direction;

	vec3 diffuse;
	vec3 specular;

	float innerCutOff;
	float outerCutOff;
};


struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;
	float alpha;

	bool diffuseTexturesActive;
	sampler2D diffuseTexture0;
	sampler2D diffuseTexture1;
	sampler2D diffuseTexture2;
	sampler2D diffuseTexture3;

	bool specularTexturesActive;
	sampler2D specularTexture0;
	sampler2D specularTexture1;
	sampler2D specularTexture2;
	sampler2D specularTexture3;
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
uniform bool spriteTextureActive;
uniform sampler2D textureData;

vec3 diffuseTexture;
vec3 specularTexture;

vec3 materialDiffuse;
vec3 materialSpecular;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 nNormal, vec3 viewDirection);
vec3 CalculateSpotlight(Spotlight light, vec3 nNormal, vec3 viewDirection);

void main()
{
	//DEBUG
	//-------
	//FragColor = vec4(material.diffuse, 1.0f);
	//return;
	//-------

	if (material.diffuseTexturesActive)
	{
		vec3 diffuseTexture0 = vec3(texture(material.diffuseTexture0, TextureCoordinates));
		vec3 diffuseTexture1 = vec3(texture(material.diffuseTexture1, TextureCoordinates));
		vec3 diffuseTexture2 = vec3(texture(material.diffuseTexture2, TextureCoordinates));
		vec3 diffuseTexture3 = vec3(texture(material.diffuseTexture3, TextureCoordinates));
		diffuseTexture = diffuseTexture0 + diffuseTexture1 + diffuseTexture2 + diffuseTexture3;
		
		materialDiffuse = diffuseTexture;
	}
	else materialDiffuse = material.diffuse;
	
	if (material.specularTexturesActive)
	{
		vec3 specularTexture0 = vec3(texture(material.specularTexture0, TextureCoordinates));
		vec3 specularTexture1 = vec3(texture(material.specularTexture1, TextureCoordinates));
		vec3 specularTexture2 = vec3(texture(material.specularTexture2, TextureCoordinates));
		vec3 specularTexture3 = vec3(texture(material.specularTexture3, TextureCoordinates));
		specularTexture = specularTexture0 + specularTexture1 + specularTexture2 + specularTexture3;
		
		materialSpecular = specularTexture;
	}
	else materialSpecular = material.specular;
	
	vec4 objectColor;
	if (spriteTextureActive) objectColor = texture(textureData, TextureCoordinates);
	else if (material.diffuseTexturesActive) objectColor = vec4(materialDiffuse, 1.0f);
	else objectColor = vec4(color, 1.0f);

	//Ambient
	//-------
	vec3 ambient = lightingAmbient * material.diffuse;
	if (material.diffuseTexturesActive) ambient *= diffuseTexture;
	//-------
	
	vec3 lighting = ambient;
	
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
	
	FragColor = objectColor * vec4(lighting, material.alpha);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null || !light.on) return vec3(0.0f);

	vec3 lightSourceDirection = -light.direction;

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;
	if (material.diffuseTexturesActive) diffuse *= materialDiffuse;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * material.specular * specularImpact;
	if (material.specularTexturesActive) specular *= materialSpecular;

	return (diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null || !light.on) return vec3(0.0f);

	vec3 lightSourceDirection = normalize(light.position - FragmentPosition);

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;
	if (material.diffuseTexturesActive) diffuse *= materialDiffuse;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * material.specular * specularImpact;
	if (material.specularTexturesActive) specular *= materialSpecular;

	float distance = length(light.position - FragmentPosition);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	diffuse *= attenuation;
	specular *= attenuation;

	return (diffuse + specular);
}

vec3 CalculateSpotlight(Spotlight light, vec3 nNormal, vec3 viewDirection)
{
	if (light.null || !light.on) return vec3(0.0f);

	vec3 lightSourceDirection = normalize(light.position - FragmentPosition);

	float diffuseImpact = max(dot(nNormal, lightSourceDirection), 0.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseImpact;
	if (material.diffuseTexturesActive) diffuse *= materialDiffuse;

	vec3 reflectDirection = reflect(-lightSourceDirection, nNormal);
	float specularImpact = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess * 128.0f);
	vec3 specular = light.specular * material.specular * specularImpact;
	if (material.specularTexturesActive) specular *= materialSpecular;

	float theta = dot(lightSourceDirection, -light.direction);
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
	
	diffuse *= intensity;
	specular *= intensity;

	return (diffuse + specular);
}