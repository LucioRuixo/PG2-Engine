#include "Model.h"

Model::Model(TextureManager* _textureManager, const char* path) : Entity()
{
	textureManager = _textureManager;

	loadModel(path);
}

Model::~Model()
{
	meshes.clear();
}

void Model::loadModel(string path)
{
	Importer importer;
	cout << "importing model from \"" << path << "\"" << endl;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate /*| aiProcess_FlipUVs*/);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR (Assimp): " << importer.GetErrorString() << endl << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	
	processNode(scene, scene->mRootNode);
	cout << "model loaded from \"" << path << "\"" << endl << endl;
}

void Model::processNode(const aiScene* scene, aiNode* node)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(scene, mesh));
	}

	cout << "processing node \"" << node->mName.C_Str() << "\"" << endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(scene, node->mChildren[i]);
	}
	cout << "node \"" << node->mName.C_Str() << "\" and all its children processed" << endl;
}

Mesh Model::processMesh(const aiScene* scene, aiMesh* mesh)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3 vec3Aux;

		vec3Aux.x = mesh->mVertices[i].x;
		vec3Aux.y = mesh->mVertices[i].y;
		vec3Aux.z = mesh->mVertices[i].z;
		vertex.Position = vec3Aux;

		vec3Aux.x = mesh->mNormals[i].x;
		vec3Aux.y = mesh->mNormals[i].y;
		vec3Aux.z = mesh->mNormals[i].z;
		vertex.Normal = vec3Aux;

		if (mesh->mTextureCoords[0])
		{
			vec2 vec2Aux;
			vec2Aux.x = mesh->mTextureCoords[0][i].x;
			vec2Aux.y = mesh->mTextureCoords[0][i].y;
			vertex.TextureCoordinates = vec2Aux;
		}
		else vertex.TextureCoordinates = vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuseTexture");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specularTexture");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(renderer, vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	unsigned int textureCount = material->GetTextureCount(type);
	cout << "mesh texture count of type \"" << typeName << "\": " << textureCount << endl;
	for (unsigned int i = 0; i < textureCount; i++)
	{
		aiString relativePath;
		material->GetTexture(type, i, &relativePath);

		string sRelativePath = relativePath.C_Str();
		string path = directory + '/' + sRelativePath;

		Texture texture;
		texture = textureManager->createTextureFromFile(path.c_str(), sRelativePath);
		texture.type = typeName;

		textures.push_back(texture);
	}
	return textures;
}

void Model::draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].draw(modelMatrix.model);
}