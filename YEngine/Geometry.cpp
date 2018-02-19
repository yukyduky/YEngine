#include "Geometry.h"
#include <cassert>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Locator.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

bool Geometry::createVertexBuffer(ID3D11Buffer ** gVertexBuffer, void * v, int & stride, int & offset, int numVertices)
{
	bool success = true;
	// Describe the vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	memset(&vertexBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = stride * numVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	// Set the vertex buffer data
	D3D11_SUBRESOURCE_DATA vertexData;
	memset(&vertexData, 0, sizeof(vertexData));
	vertexData.pSysMem = v;

	HRESULT hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, gVertexBuffer);
	if (FAILED(hr)) {
		assert(FAILED(hr) && "Resource - Failed to create vertex buffer");
		success = false;
	}
	return success;
}

bool Geometry::createIndexBuffer(ID3D11Buffer ** gIndexBuffer, void * data, int & numIndices)
{
	bool success = true;
	// Describe the index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	memset(&indexBufferDesc, 0, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * numIndices;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Set the index buffer data
	D3D11_SUBRESOURCE_DATA indexData;

	indexData.pSysMem = data;
	HRESULT hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&indexBufferDesc, &indexData, gIndexBuffer);
	if (FAILED(hr)) {
		assert(FAILED(hr) && "Resource - Failed to create index buffer");
		success = false;
	}
	return success;
}

bool Geometry::createBuffers(ID3D11Buffer ** vBuffer, ID3D11Buffer ** iBuffer, void * vertices, void * indices, int numVertices, int numIndices, int stride, int offset)
{
	bool allLoaded = false;
	bool vLoaded = false;
	bool iLoaded = false;

	vLoaded = this->createVertexBuffer(vBuffer, vertices, stride, offset, numVertices);

	iLoaded = this->createIndexBuffer(iBuffer, indices, numIndices);

	if (vLoaded && iLoaded) {
		allLoaded = true;
	}
	else if (vLoaded) {
		(*vBuffer)->Release();
	}
	else if (iLoaded) {
		(*iBuffer)->Release();
	}

	return allLoaded;
}

bool Geometry::loadVertexDataFromFile(const char* filename, VertexData& data)
{
	bool success = false;
	RawData rawData;
	std::vector<std::vector<std::vector<int>>> parsedDataSets;
	if (Locator::getConfigHandler()->loadRawData(rawData, filename)) {
		for (auto &i : rawData.dataSets) {
			std::vector<std::vector<int>> parsedDataRows;
			for (auto &k : i) {
				std::vector<int> parsedData;
				for (auto &h : k) {
					parsedData.push_back(atoi(h.c_str()));
				}
				parsedDataRows.push_back(parsedData);
			}
			parsedDataSets.push_back(parsedDataRows);
		}

		ID3D11Buffer* vBuffer;
		ID3D11Buffer* iBuffer;
		void* vertices = parsedDataSets[1].data();
		void* indices = parsedDataSets[2].data();
		int numVertices = parsedDataSets[1].size();
		int numIndices = parsedDataSets[2].size();
		int stride = static_cast<int>(parsedDataSets[0][0][0]);
		int offset = static_cast<int>(parsedDataSets[0][1][0]);

		if (this->createBuffers(&vBuffer, &iBuffer, vertices, indices, numVertices, numIndices, stride, offset)) {
			success = true;

			data.vBuffer = vBuffer;
			data.iBuffer = iBuffer;
			data.numVertices = numVertices;
			data.numIndices = numIndices;
			data.numFaces = numIndices / 3;
			data.stride = stride;
			data.offset = offset;
		}
	}
	return success;
}

bool Geometry::loadObjFile(const char* filename, VertexData& data)
{
	bool success = false;
	RawData rawData;
	std::vector<std::vector<std::vector<int>>> parsedDataSets;
	if (Locator::getConfigHandler()->loadRawData(rawData, filename)) {
		for (auto &i : rawData.dataSets) {
			std::vector<std::vector<int>> parsedDataRows;
			for (auto &k : i) {
				std::vector<int> parsedData;
				for (auto &h : k) {
					parsedData.push_back(atoi(h.c_str()));
				}
				parsedDataRows.push_back(parsedData);
			}
			parsedDataSets.push_back(parsedDataRows);
		}

		ID3D11Buffer* vBuffer;
		ID3D11Buffer* iBuffer;
		void* vertices = parsedDataSets[1].data();
		void* indices = parsedDataSets[2].data();
		int numVertices = parsedDataSets[1].size();
		int numIndices = parsedDataSets[2].size();
		int stride = static_cast<int>(parsedDataSets[0][0][0]);
		int offset = static_cast<int>(parsedDataSets[0][1][0]);

		if (this->createBuffers(&vBuffer, &iBuffer, vertices, indices, numVertices, numIndices, stride, offset)) {
			success = true;

			data.vBuffer = vBuffer;
			data.iBuffer = iBuffer;
			data.numVertices = numVertices;
			data.numIndices = numIndices;
			data.numFaces = numIndices / 3;
			data.stride = stride;
			data.offset = offset;
		}
	}
	return success;
}

bool Geometry::load(std::string filename, RESOURCETYPE type)
{
	bool success = true;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene) {
		assert(scene && "Resource (Model) - Failed to import model");
		success = false;
	}
	else {
		std::vector<Vertex> vertices;
		std::vector<int> indices;

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
			
			for (int c = 0; c < mesh->mNumFaces; c++) {
				for (int e = 0; e < mesh->mFaces[c].mNumIndices; e++) {
					indices.push_back(mesh->mFaces[c].mIndices[e]);
				}
			}
		}

		ID3D11Buffer* vBuffer = nullptr;
		ID3D11Buffer* iBuffer = nullptr;

		if (this->createBuffers(&vBuffer, &iBuffer, vertices.data(), indices.data(), vertices.size(), indices.size(), sizeof(Vertex), 0)) {
			this->type = type;
			this->data = VertexData(vBuffer, iBuffer, vertices.size(), indices.size(), indices.size() / 3, sizeof(Vertex), 0);
		}
	}

	return success;
}

Geometry::Geometry(std::string filename, RESOURCETYPE type)
{
	this->loaded = false;
	std::string ext = filename.substr(filename.find_last_of('.') + 1, filename.size() - filename.find_last_of('.'));

	if (ext == "obj") {
		this->loaded = this->load(filename, type);
	}
	else if (ext == "yk") {

	}
}

void Geometry::unload()
{
	this->data.vBuffer->Release();
	this->data.iBuffer->Release();
	this->loaded = false;
}

bool Geometry::reload()
{
	return false; // this->loaded = this->createBuffers(&this->data.vBuffer, &this->data.iBuffer, vertices, indices, this->data.numVertices, this->data.numIndices, this->data.stride, this->data.offset);
}

VertexData Geometry::getData()
{
	return this->data;
}
