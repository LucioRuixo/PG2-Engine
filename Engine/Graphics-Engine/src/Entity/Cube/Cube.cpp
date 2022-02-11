#include "Cube.h"

vec3 cubeColor = vec3(1.0f, 0.75f, 0.1f);

unsigned int Cube::vao = 0;
unsigned int Cube::vbo = 0;
unsigned int Cube::ebo = 0;

int Cube::collisionVertexIndices[] = { 0, 1, 2, 4, 6, 7, 8, 10 };

float Cube::vertices[] =
{
	//Position              //Normal               //UV       
	//-----------------
	-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f, //0 ---
	 0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 1.0f, //1 +--
	 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f, //2 ++-
	 0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f, //3
	-0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 0.0f, //4 -+-
	-0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f, //5
							
	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f, //6 --+
	 0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 1.0f, //7 +-+
	 0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 0.0f, //8 +++
	 0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f, //9
	-0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 0.0f, //10 -++
	-0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
							
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
							
	-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,	   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f
	//-----------------
};

//float Cube::vertexPositions[] =
//{
//	-0.5f, -0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	-0.5f,  0.5f, -0.5f,
//
//	-0.5f, -0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f
//};

unsigned int Cube::indices[] =
{
	0, 1, 2,
	3, 4, 5,
	6, 7, 8,
	9, 10, 11,
	12, 13, 14,
	15, 16, 17,
	18, 19, 20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34, 35
};

void Cube::initializeRenderingData()
{
	if (!Entity::cubeRenderingDataInitialized)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, CUBE_VERTEX_COMPONENTS * sizeof(float), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, CUBE_INDICES * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		//Position
		unsigned int positionAttributeLocation = glGetAttribLocation(renderer->getShaderProgram(ShaderType::Main), "aPosition");
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//Normal
		unsigned int normalAttributeLocation = glGetAttribLocation(renderer->getShaderProgram(ShaderType::Main), "aNormal");
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//Texture coordinates
		//glUniform1i(glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "textureData"), 0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		for (int i = 0; i < CUBE_VERTICES; i++)
		{
			int xIndex = collisionVertexIndices[i] * VERTEX_LENGTH;
			vec3 position = vec3(vertices[xIndex], vertices[xIndex + 1], vertices[xIndex + 2]);
			cubeVertexPositions.push_back(position);
		}

		Entity::cubeRenderingDataInitialized = true;
	}
	else cout << "Can not initialize cube rendering data: data has already been initialized" << endl;
}

Cube::Cube(bool renderizable) : Entity(renderizable) {}

Cube::Cube(vec3 _color, bool renderizable) : Entity(_color, renderizable) {}

Cube::Cube(Material _material, bool renderizable) : Entity(_material, renderizable) {}

Cube::Cube(vec3 _color, Material _material, bool renderizable) : Entity(_color, _material, renderizable) {}

Cube::~Cube() {}

#pragma Collision Box
vector<vec3> Cube::getCollisionVertices() { return calculateCollisionVertices(cubeVertexPositions); }
#pragma endregion

void Cube::draw()
{
	setUniformValues();
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	renderer->drawElements(vao, vbo, ebo, CUBE_INDICES);

	Entity::draw();
}