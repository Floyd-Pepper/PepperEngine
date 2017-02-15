#version 330 core
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Light light; 
uniform Material material;
uniform vec3 viewPos;

void main()
{
	// ambiant lighting
    vec3 ambient = material.ambient * light.ambient;
	//diffuse lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;
	// specular lighting
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specular * spec * light.specular;  
	//total lighting
	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
}