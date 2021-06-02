#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Tools/Includes.h"
#include "../Entity.h"
#include "Renderer/Renderer.h"
#include "TextureManager/TextureManager.h"
#include "Mesh/Mesh.h"

using namespace std;
using namespace Assimp;

class GENGINE_API Model : public Entity
{
	string directory;

	vector<Mesh> meshes;

	void loadModel(string path);
	void processNode(const aiScene* scene, aiNode* node);
	Mesh processMesh(const aiScene* scene, aiMesh* mesh);
	vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName);
public:
	Model(const char* path, Renderer* _renderer);

	void draw();
};

#endif // !MODEL_H