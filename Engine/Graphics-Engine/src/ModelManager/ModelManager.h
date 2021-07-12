#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Tools/Includes.h"
#include "Entity/Model/Model.h"
#include "Entity/Model/ModelNode/ModelNode.h"
#include "TextureManager/TextureManager.h"

using namespace std;
using namespace Assimp;

class GENGINE_API ModelManager
{
	int currentNodeLayer = 0;

	string importingDirectory;

	vector<Model*> models;

	Renderer* renderer;
	TextureManager* textureManager;

	ModelNode* processNode(const aiScene* scene, aiNode* node);
	Mesh* processMesh(const aiScene* scene, aiMesh* mesh);
	vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName);
	Material loadMaterialColors(aiMaterial* meshMaterial);
public:
	ModelManager(TextureManager* _textureManager);
	~ModelManager();

	Model* importModel(string path);
};

#endif // !MODEL_MANAGER_H