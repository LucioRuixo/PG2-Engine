#include "Plane.h"

//T = top
//B = bottom
//L = left
//R = right
vec2 TL = vec2(-0.5f, 0.5f);
vec2 TR = vec2(0.5f, 0.5f);
vec2 BL = vec2(-0.5f, -0.5f);
vec2 BR = vec2(0.5f, -0.5f);
vec2 boundsMin = BL;
vec2 boundsMax = TR;

unsigned int Plane::vao = 0;
unsigned int Plane::vbo = 0;
unsigned int Plane::ebo = 0;

float Plane::vertices[] =
{
	//Position           //Normal             //UV       
	//--------------									 
	//With TBLR							      
	TL.x, TL.y, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
	TR.x, TR.y, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	BR.x, BR.y, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
	BL.x, BL.y, 0.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f
	//--------------									 
};

unsigned int Plane::indices[] =
{
	0, 1, 3,   //1st triangle
	1, 2, 3    //2nd triangle
};

void Plane::initializeRenderingObjects()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, PLANE_VERTEX_COMPONENTS * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, PLANE_INDICES * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//Position
	unsigned int positionAttributeLocation = glGetAttribLocation(renderer->getShaderProgram(ShaderType::Main), "aPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//Normal
	unsigned int normalAttributeLocation = glGetAttribLocation(renderer->getShaderProgram(ShaderType::Main), "aNormal");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texture coordinates
	unsigned int textureUniformLocation = glGetUniformLocation(renderer->getShaderProgram(ShaderType::Main), "textureData");
	glUniform1i(textureUniformLocation, 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

Plane::Plane() : Entity() {}

Plane::Plane(vec3 _normal) : Entity()
{
	//transform->setPosition(position.x, position.y, position.z);
	//transform->setRotation(-90.0f, 0.0f, 0.0f);
	//
	//// TODO: rotar en base a la normal
	////cout << "----------" << endl;
	////Pitch
	////----------
	//float forwardX = transform->getForward().y == 0.0f & transform->getForward().z == 0.0f ? 1.0f : 0.0f;
	//vec3 forward = normalize(vec3(forwardX, transform->getForward().y, transform->getForward().z));
	//
	//float pitchX = normal.y == 0.0f && normal.z == 0.0f ? 1.0f : 0.0f;
	//vec3 pitchNormal = normalize(vec3(pitchX, normal.y, normal.z));
	//
	//float pitch = angle(forward, pitchNormal);
	//if (transform->getForward().y < normal.y) pitch *= -1.0f;
	//
	//float pitchEuler = pitch * (180.0f / glm::pi<float>());
	//if (pitchEuler == 360.0f) pitchEuler = 0.0f;
	//
	//transform->rotate(pitchEuler, 0.0f, 0.0f);
	////----------
	//
	////Yaw
	////----------
	//float forwardY = transform->getForward().x == 0.0f & transform->getForward().z == 0.0f ? 1.0f : 0.0f;
	//forward = normalize(vec3(transform->getForward().x, forwardY, transform->getForward().z));
	//
	//float yawY = normal.x == 0.0f & normal.z == 0.0f ? 1.0f : 0.0f;
	//vec3 yawNormal = normalize(vec3(normal.x, yawY, normal.z));
	//
	////cout << "yaw forward: " << forward.x << ", " << forward.y << ", " << forward.z << endl;
	////cout << "yaw normal: " << normal.x << ", " << yawY << ", " << normal.z << endl;
	////cout << endl;
	//float yaw = angle(forward, yawNormal);
	//if (transform->getForward().x > normal.x) yaw *= -1.0f;
	//
	//float yawEuler = yaw * (180.0f / glm::pi<float>());
	//if (yawEuler == 360.0f) yawEuler = 0.0f;
	//
	//transform->rotate(0.0f, yawEuler, 0.0f);
	////----------
	//
	////Roll
	////----------
	//float rightZ = transform->getRight().x == 0.0f & transform->getRight().y == 0.0f ? 1.0f : 0.0f;
	//vec3 right = normalize(vec3(transform->getRight().x, transform->getRight().y, rightZ));
	//
	//vec3 normalPerp;
	//if (normal == vec3(0.0f, 1.0f, 0.0f)) normalPerp = vec3(1.0f, 0.0f, 0.0f);
	//else
	//{
	//	normalPerp = cross(vec3(0.0f, 1.0f, 0.0f), normal);
	//	normalPerp.z = 0.0f;
	//	normalPerp = normalize(normalPerp);
	//}
	//
	//float roll = angle(right, normalPerp);
	//if (transform->getRight().y < normal.y) roll *= -1.0f;
	//
	//float rollEuler = roll * (180.0f / glm::pi<float>());
	//if (rollEuler == 360.0f) rollEuler = 0.0f;
	//
	////transform->rotate(0.0f, 0.0f, rollEuler);
	//
	////cout << "normal: " << normal.x << ", " << normal.y << ", " << normal.z << endl;
	////cout << "normal perp: " << normalPerp.x << ", " << normalPerp.y << ", " << normalPerp.z << endl;
	////cout << "forward: " << transform->getForward().x << ", " << transform->getForward().y << ", " << transform->getForward().z << endl;
	////cout << "right: " << transform->getRight().x << ", " << transform->getRight().y << ", " << transform->getRight().z << endl;
	////----------
	//
	////cout << endl;
	////cout << "pitch: " << pitchEuler << endl;
	////cout << "yaw: " << yawEuler << endl;
	////cout << "roll: " << rollEuler << endl;
	////cout << "----------" << endl;
	//
	////transform->rotate(pitchEuler, yawEuler, rollEuler);
	////transform->rotate(pitchEuler, yawEuler, 0.0f);
}

//Plane::Plane(vec3 _color) : Entity(_color) {}

Plane::Plane(Material _material) : Entity(_material) {}

Plane::Plane(vec3 _color, Material _material) : Entity(_color, _material) {}

Plane::~Plane() {}

vec3 Plane::getNormal() { return transform->getForward(); }

float Plane::distanceToPoint(vec3 point)
{
	vec3 normal = getNormal();
	return dot(point - transform->getPosition(), normal) / length(normal);
}

bool Plane::sameSide(vec3 a, vec3 b)
{
	bool onPositiveSide = (distanceToPoint(a) >= 0) && (distanceToPoint(b) >= 0);
	bool onNegativeSide = (distanceToPoint(a) <= 0) && (distanceToPoint(b) <= 0);
	return onPositiveSide || onNegativeSide;
}

bool Plane::sameSide(vec3 a, vec3 b[])
{
	for (int i = 0; i < b->length(); i++)
	{
		bool onPositiveSide = (distanceToPoint(a) >= 0) && (distanceToPoint(b[i]) >= 0);
		bool onNegativeSide = (distanceToPoint(a) <= 0) && (distanceToPoint(b[i]) <= 0);
		if (onPositiveSide || onNegativeSide) return true;
	}
	
	return false;
}

void Plane::draw()
{
	setUniformValues();
	renderer->setModel(renderer->getShaderProgram(shader), transform->getGlobalModel());
	renderer->drawElements(vao, vbo, ebo, PLANE_INDICES);

	Entity::draw();
}