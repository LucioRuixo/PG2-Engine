#include "Model.h"

Model::Model(string _directory, vector<Mesh> _meshes) : Entity()
{
	directory = _directory;
	meshes = _meshes;

	material.diffuseTexturesActive = true;
	material.specularTexturesActive = true;
}

Model::~Model()
{
	meshes.clear();
}

string Model::getDirectory() { return directory; }

void Model::draw()
{
	setUniformValues();

	for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].draw(modelMatrix.model);
}