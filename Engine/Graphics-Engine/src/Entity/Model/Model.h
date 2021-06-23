#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "Mesh/Mesh.h"

using namespace std;

class GENGINE_API Model : public Entity
{
	string directory;

	vector<Mesh> meshes;
public:
	Model(string _directory, vector<Mesh> _meshes);
	~Model();

	string getDirectory();

	void draw();
};

#endif // !MODEL_H