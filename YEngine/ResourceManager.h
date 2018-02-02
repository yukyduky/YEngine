#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <d3d11.h>
#include <SimpleMath.h>
#include <array>
#include <string>
#include <assimp\Importer.hpp>

enum class OBJECTTYPE { BLOCK };

enum class BUFFER { VERTEX, INDEX, CONSTANT };

namespace RESOURCEGRAPHIC {
	enum ID { SIZE };
}

namespace RESOURCEOBJECT {
	enum ID { TEXQUAD, SIZE };
}

using namespace DirectX::SimpleMath;

struct ObjectData {
	RESOURCEOBJECT::ID ID;
	void* vertices;
	void* indices;
	size_t numVertices;
	size_t numIndices;
	size_t stride;
	size_t offset;
	size_t numFaces;
	size_t cbSize;

	ObjectData() {}
	ObjectData(RESOURCEOBJECT::ID ID, void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset, size_t numFaces, size_t cbSize) :
		ID(ID), vertices(vertices), indices(indices), numVertices(numVertices), numIndices(numIndices), stride(stride), offset(offset), numFaces(numFaces), cbSize(cbSize) {}
};

struct vBufferData
{
	ID3D11Buffer* vBuffer;
	size_t numVertices;
	size_t stride;
	size_t offset;

	vBufferData() {}
	vBufferData(ObjectData data) : numVertices(data.numVertices), stride(data.stride), offset(data.offset) {}
	vBufferData(ID3D11Buffer* vBuffer, ObjectData data) : vBuffer(vBuffer), numVertices(data.numVertices), stride(data.stride), offset(data.offset) {}
};
struct iBufferData
{
	ID3D11Buffer* iBuffer;
	size_t numIndices;
	size_t numFaces;

	iBufferData() {}
	iBufferData(ObjectData data) : numIndices(data.numIndices), numFaces(data.numFaces) {}
	iBufferData(ID3D11Buffer* iBuffer, ObjectData data) : iBuffer(iBuffer), numIndices(data.numIndices), numFaces(data.numFaces) {}
};
struct cBufferData
{
	ID3D11Buffer* cBuffer;
	size_t cbSize;

	cBufferData() {}
	cBufferData(ObjectData data) : cbSize(data.cbSize) {}
	cBufferData(ID3D11Buffer* cBuffer, ObjectData data) : cBuffer(cBuffer), cbSize(data.cbSize) {}
};

class ResourceManager
{
private:
	Assimp::Importer importer;

	std::unordered_map<RESOURCEGRAPHIC::ID, ID3D11ShaderResourceView*> texSRVMap;
	std::unordered_map<RESOURCEOBJECT::ID, vBufferData> vertexBufferMap;
	std::unordered_map<RESOURCEOBJECT::ID, iBufferData> indexBufferMap;
	std::unordered_map<RESOURCEOBJECT::ID, cBufferData> constantBufferMap;

	/*--------------- INFORMATION ---------------
	1. Maps the data to the ID location
	2. Creates a vertex buffer, index buffer, and a constant buffer
	*/
	void addObjectData(ObjectData& data);
public:
	void loadModel(RESOURCEGRAPHIC::ID texID, RESOURCEOBJECT::ID objID, std::string filename, std::wstring textureName);
	void loadTexture(RESOURCEGRAPHIC::ID ID, std::wstring filename);
	/*--------------- INFORMATION ---------------
	1. Updates the index buffer with the given data
	*/
	void updateVertexBuffer(RESOURCEOBJECT::ID ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the vertex buffer with the given data
	*/
	void updateIndexBuffer(RESOURCEOBJECT::ID ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the constant buffer with the given data
	*/
	void updateConstantBuffer(RESOURCEOBJECT::ID ID, void* pData);

	vBufferData& getVBufferData(RESOURCEOBJECT::ID ID);
	iBufferData& getIBufferData(RESOURCEOBJECT::ID ID);
	cBufferData& getCBufferData(RESOURCEOBJECT::ID ID);
	void initTexQuad();
};

#endif // !RESOURCEMANAGER_H
