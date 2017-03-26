#version 400 core

#define MAX_LIGHTS 10

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    sampler2D texture_diffuse;
	sampler2D texture_specular;
	vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
in vec4 FragPosLightSpace;

out vec4 color;

uniform vec3 viewPos;
uniform int dirLightCount;
uniform int pointLightCount;
uniform DirLight dirLights[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];
uniform Material material;
uniform sampler2D shadowMap;
uniform bool hasTexture;
uniform uint lightingModel;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace);
float CalcPhongSpecular(vec3 lightDir, vec3 viewDir, vec3 normal);
float CalcBlinnSpecular(vec3 lightDir, vec3 viewDir, vec3 normal);
float CalcDiffuse(vec3 lightDir, vec3 viewDir, vec3 normal);

const uint PHONG = 1;
const uint BLINN_PHONG = 2;

void main()
{
	// Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result;

    // Phase 1: Directional lighting
	for(int i = 0; i < dirLightCount; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    // Phase 2: Point lights
    for(int i = 0; i < pointLightCount; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // Phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    
    color = vec4(result, 1.0);
	//color = mix(texture(material.texture_diffuse1, TexCoord), texture(material.texture_specular1, TexCoord), 0.5);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = CalcDiffuse(lightDir, viewDir, normal);
    // Specular shading
	float spec = 0.0;
	if(lightingModel == PHONG)
	{
		spec = CalcPhongSpecular(lightDir, viewDir, normal);
	}
	else if(lightingModel == BLINN_PHONG)
	{
		spec = CalcBlinnSpecular(lightDir, viewDir, normal);
	}
    // Combine results
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	if(hasTexture)
	{
		ambient  = light.ambient  * vec3(texture(material.texture_diffuse, TexCoord));
		diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse, TexCoord));
		specular = light.specular * spec * vec3(texture(material.texture_specular, TexCoord));
	}
	else
	{
		ambient  = light.ambient  * material.ambient;
		diffuse  = light.diffuse  * diff * material.diffuse;
		specular = light.specular * spec * material.specular;
	}
    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
	float diff = CalcDiffuse(lightDir, viewDir, normal);
    // Specular shading
	float spec = 0.0;
	if(lightingModel == PHONG)
	{
		spec = CalcPhongSpecular(lightDir, viewDir, normal);
	}
	else if(lightingModel == BLINN_PHONG)
	{
		spec = CalcBlinnSpecular(lightDir, viewDir, normal);
	}
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Combine results
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	if(hasTexture)
	{
		ambient  = light.ambient  * vec3(texture(material.texture_diffuse, TexCoord));
		diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse, TexCoord));
		specular = light.specular * spec * vec3(texture(material.texture_specular, TexCoord));
	}
	else
	{
		ambient  = light.ambient  * material.ambient;
		diffuse  = light.diffuse  * diff * material.diffuse;
		specular = light.specular * spec * material.specular;
	}
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

float CalcPhongSpecular(vec3 lightDir, vec3 viewDir, vec3 normal)
{
	vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return spec;
}

float CalcBlinnSpecular(vec3 lightDir, vec3 viewDir, vec3 normal)
{
	vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	return spec;
}

float CalcDiffuse(vec3 lightDir, vec3 viewDir, vec3 normal)
{
	float diff = max(dot(normal, lightDir), 0.0);
	return diff;
}