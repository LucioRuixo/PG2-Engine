#include "Mesh.h"

Mesh::Mesh(Renderer* _renderer, vector<Vertex> _vertices, vector<unsigned int> _indices, vector<Texture> _textures)
{
	renderer = _renderer;
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	setupMesh();
}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
	textures.clear();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureCoordinates));

	glBindVertexArray(0);
}

vector<Vertex> Mesh::getVertices() { return vertices; }

vector<unsigned int> Mesh::getIndices() { return indices; }

vector<Texture> Mesh::getTextures() { return textures; }

void Mesh::draw(mat4 model)
{
	unsigned int uniformLocation = 0;

	//Texture
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "spriteTextureActive");
	glUniform1i(uniformLocation, 0);
	
	//Color
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "color");
	glUniform3f(uniformLocation, 1.0f, 1.0f, 1.0f);
	
	//Material
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexturesOn");
	glUniform1i(uniformLocation, 1);
	
	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexturesOn");
	glUniform1i(uniformLocation, 1);
	
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuse");
	//glUniform3f(uniformLocation, material.diffuse.r, material.diffuse.g, material.diffuse.b);
	//
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specular");
	//glUniform3f(uniformLocation, material.specular.r, material.specular.g, material.specular.b);
	//
	//uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.shininess");
	//glUniform1f(uniformLocation, material.shininess);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.diffuseTexturesOn");
	glUniform1i(uniformLocation, 1);

	uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "material.specularTexturesOn");
	glUniform1i(uniformLocation, 1);

	unsigned int diffuseNumber = 0;
	unsigned int specularNumber = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		string number;
		string name = textures[i].type;

		if (name == "diffuseTexture")
		{
			if (diffuseNumber >= MAX_TEXTURE_AMOUNT_PER_TYPE) continue;
			else number = to_string(diffuseNumber++);
		}
		else if (name == "specularTexture")
		{
			if (specularNumber >= MAX_TEXTURE_AMOUNT_PER_TYPE) continue;
			else number = to_string(specularNumber++);
		}

		uniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), ("material." + name + number).c_str());
		glUniform1i(uniformLocation, i);

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	//// draw mesh
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	renderer->setModel(renderer->getShaderProgram(ShaderType::Main), model);
	renderer->drawElements(vao, vbo, ebo, indices.size());
}