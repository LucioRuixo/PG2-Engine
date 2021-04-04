#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float ambientLightStrenth;
uniform vec3 ambientLightColor;
uniform sampler2D ourTexture;

void main() {
	//Vertex color
	//FragColor = vec4(ourColor, 1.0);

	//Vertex color affected by ambient light
	//FragColor = vec4(ourColor * lightColor, 1.0f);

	//Texture
	//FragColor = texture(ourTexture, TexCoord);

	//Texture affected by vertex color
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);

	//Texture affected by ambient light
	FragColor.x = texture(ourTexture, TexCoord).x * ambientLightColor.x * ambientLightStrenth;
	FragColor.y = texture(ourTexture, TexCoord).y * ambientLightColor.y * ambientLightStrenth;
	FragColor.z = texture(ourTexture, TexCoord).z * ambientLightColor.z * ambientLightStrenth;
	FragColor.w = 1.0f;

	//Texture affected by vertex color and ambient light
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0) * vec4(lightColor, 1.0);
}