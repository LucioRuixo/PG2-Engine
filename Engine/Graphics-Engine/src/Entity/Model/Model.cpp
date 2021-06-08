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
	cout << "importing model from " << path << endl;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR (Assimp): " << importer.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	
	processNode(scene, scene->mRootNode);
	cout << "model loaded from " << path << endl;
}

void Model::processNode(const aiScene* scene, aiNode* node)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(scene, mesh));
	}

	cout << "processing node " << node->mName.C_Str() << endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(scene, node->mChildren[i]);
	}
	cout << "successfully processed node " << node->mName.C_Str() << " and all its children" << endl;
}

Mesh Model::processMesh(const aiScene* scene, aiMesh* mesh)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3 vector3Aux;

		vector3Aux.x = mesh->mVertices[i].x;
		vector3Aux.y = mesh->mVertices[i].y;
		vector3Aux.z = mesh->mVertices[i].z;
		vertex.Position = vector3Aux;

		vector3Aux.x = mesh->mNormals[i].x;
		vector3Aux.y = mesh->mNormals[i].y;
		vector3Aux.z = mesh->mNormals[i].z;
		vertex.Normal = vector3Aux;

		if (mesh->mTextureCoords[0])
		{
			vec2 vector2Aux;
			vector2Aux.x = mesh->mTextureCoords[0][i].x;
			vector2Aux.y = mesh->mTextureCoords[0][i].y;
			vertex.TextureCoordinates = vector2Aux;
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
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(renderer, vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString relativePath;
		material->GetTexture(type, i, &relativePath);

		string sRelativePath = relativePath.C_Str();
		string path = directory + '/' + sRelativePath;

		Texture texture;
		texture.id = textureManager->createTextureFromFile(path.c_str(), sRelativePath).id;
		texture.type = typeName;

		textures.push_back(texture);
	}
	return textures;
}

void Model::draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].draw(modelMatrix.model);
}