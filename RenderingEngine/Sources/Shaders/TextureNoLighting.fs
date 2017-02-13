#version 330 core
in vec2 TexCoord;

out vec4 color;

struct Material {
    sampler2D diffuse;
}; 
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec4 objectColor;
uniform Material material;

void main()
{
	//color = mix(texture(texture0, TexCoord), texture(texture1, vec2(TexCoord.x, 1.0 - TexCoord.y)), 0.2);
	color = texture(material.diffuse, TexCoord);
}