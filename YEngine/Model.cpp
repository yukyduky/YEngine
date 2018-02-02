#include "Model.h"
#include <cassert>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>


struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

bool Model::loadModel(const char * modelFilename, const char* texFilename)
{
	bool success = true;

	Assimp::Importer importer;
	this->scene = importer.ReadFile(modelFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene) {
		assert(!scene && "Resource (Model) - Failed to import model");
		success = false;
	}
	else {
		std::vector<Vertex> vertices;
		std::vector<size_t> indices;

		for (int i = 0; i < scene->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[i];

			for (int k = 0; k < mesh->mNumVertices; k++) {
				Vertex v;

				v.position.x = mesh->mVertices[k].x;
				v.position.y = mesh->mVertices[k].y;
				v.position.z = mesh->mVertices[k].z;

				v.normal.x = mesh->mNormals[k].x;
				v.normal.y = mesh->mNormals[k].y;
				v.normal.z = mesh->mNormals[k].z;

				if (mesh->HasTextureCoords(0)) {
					v.texCoords.x = mesh->mTextureCoords[0][k].x;
					v.texCoords.y = mesh->mTextureCoords[0][k].y;
				}

				vertices.push_back(v);
			}

			for (size_t c = 0; c < mesh->mNumFaces; c++) {
				for (size_t e = 0; e < mesh->mFaces[c].mNumIndices; e++) {
					indices.push_back(mesh->mFaces[c].mIndices[e]);
				}
			}
		}
		
		ID3D11Buffer* vBuffer;
		ID3D11Buffer* iBuffer;

		success = this->createBuffers(&vBuffer, &iBuffer, vertices.data(), indices.data(), vertices.size(), indices.size(), sizeof(Vertex), 0);
		if (success) {
			this->loaded = true;
			this->data.vData = VertexData(vBuffer, iBuffer, vertices.size(), indices.size(), indices.size() / 3, sizeof(Vertex), 0);

			this->loadTexture(&this->data.texData.SRV, &this->data.texData.texture, texFilename);
		}
	}

	return success;
}

bool Model::load(const char* modelFilename, const char* texFilename, RESOURCETYPE type, size_t ID)
{
	this->loaded = this->loadModel(modelFilename, texFilename);

	return false;
}

void Model::unload()
{
	this->data.vData.vBuffer->Release();
	this->data.vData.iBuffer->Release();
	this->data.texData.SRV->Release();
	this->data.texData.texture->Release();
}

bool Model::reload(void * vertices, void * indices)
{
	return this->loaded = this->loadModel(this->modelFilename, this->texFilename);
}
