#include "ResourceManager.h"
#include "Locator.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "WICTextureLoader.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

void ResourceManager::addObjectData(ObjectData & data)
{
	this->vertexBufferMap.insert(this->vertexBufferMap.end(), std::pair<RESOURCEOBJECT::ID, vBufferData>(data.ID, vBufferData(data)));
	this->indexBufferMap.insert(this->indexBufferMap.end(), std::pair<RESOURCEOBJECT::ID, iBufferData>(data.ID, iBufferData(data)));
	this->constantBufferMap.insert(this->constantBufferMap.end(), std::pair<RESOURCEOBJECT::ID, cBufferData>(data.ID, cBufferData(data)));

	Locator::getD3D()->createVertexBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.vertices, data.stride, data.offset, data.numVertices);
	Locator::getD3D()->createIndexBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.indices, data.numVertices);
	Locator::getD3D()->createConstantBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.cbSize);
}

void ResourceManager::loadModel(RESOURCEGRAPHIC::ID texID, RESOURCEOBJECT::ID objID, std::string modelName, std::wstring textureName)
{
	const aiScene* scene = importer.ReadFile(modelName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene) {
		MessageBox(0, "Model importer - Failed", "Error", MB_OK);
		_exit(0);
	}
	
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

	vBufferData vData;
	iBufferData iData;

	vData.numVertices = vertices.size();
	vData.stride = sizeof(Vertex);
	vData.offset = 0;
	iData.numIndices = indices.size();
	iData.numFaces = indices.size() / 3;

	ObjectData objData = ObjectData(objID, vertices.data(), indices.data(), vertices.size(), indices.size(), sizeof(Vertex), 0, indices.size() / 3, 0);

	this->addObjectData(objData);
	this->loadTexture(texID, textureName);
}

void ResourceManager::loadTexture(RESOURCEGRAPHIC::ID texID, std::wstring filename)
{
	const wchar_t* wcharFilename = filename.c_str();
	//HRESULT hr = CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), wcharFilename, nullptr, )

	/*	hr = CreateWICTextureFromFile(gDevice, L"Textures\\crate\\diffuse.png", nullptr, &gDiffuseMap, NULL);
	if (FAILED(hr))
	{
		MessageBox(0, "Create box diffuse texture from file - Failed", "Error", MB_OK);
		return false;
	}*/
}

void ResourceManager::updateVertexBuffer(RESOURCEOBJECT::ID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->vertexBufferMap.at(ID).vBuffer, pData, this->vertexBufferMap.at(ID).numVertices);
}

void ResourceManager::updateIndexBuffer(RESOURCEOBJECT::ID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->indexBufferMap.at(ID).iBuffer, pData, this->indexBufferMap.at(ID).numIndices);
}

void ResourceManager::updateConstantBuffer(RESOURCEOBJECT::ID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->constantBufferMap.at(ID).cBuffer, pData, this->constantBufferMap.at(ID).cbSize);
}

vBufferData & ResourceManager::getVBufferData(RESOURCEOBJECT::ID ID)
{
	return this->vertexBufferMap.at(ID);
}

iBufferData & ResourceManager::getIBufferData(RESOURCEOBJECT::ID ID)
{
	return this->indexBufferMap.at(ID);
}

cBufferData & ResourceManager::getCBufferData(RESOURCEOBJECT::ID ID)
{
	return this->constantBufferMap.at(ID);
}

void ResourceManager::initTexQuad()
{
	std::array<Vertex, 4> vertices;

	vertices[0].position = Vector3(0.0f, 1.0f, 0.0f);
	vertices[1].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[2].position = Vector3(1.0f, 1.0f, 0.0f);
	vertices[3].position = Vector3(1.0f, 0.0f, 0.0f);

	vertices[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[0].texCoords = Vector2(0.0f, 1.0f);
	vertices[1].texCoords = Vector2(0.0f, 0.0f);
	vertices[2].texCoords = Vector2(1.0f, 1.0f);
	vertices[3].texCoords = Vector2(1.0f, 0.0f);

	size_t indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	ObjectData data = ObjectData(RESOURCEOBJECT::ID::TEXQUAD, vertices.data(), indices, vertices.size(), 6, sizeof(Vertex), 0, 0);
	this->addResource(data);
}
