#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 lightColor;
uniform sampler2D ourTexture;

void main() {
	//Vertex color
	//FragColor = vec4(ourColor, 1.0);

	//Vertex color affected by lighting
	//FragColor = vec4(ourColor * lightColor, 1.0f);

	//Texture
	//FragColor = texture(ourTexture, TexCoord);

	//Texture affected by vertex color
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);

	//Texture affected by lighting
	FragColor = texture(ourTexture, TexCoord) * vec4(lightColor, 1.0);

	//Texture affected by vertex color and lighting
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0) * vec4(lightColor, 1.0);
}