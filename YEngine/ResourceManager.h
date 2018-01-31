#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <d3d11.h>
#include <SimpleMath.h>
#include <array>
#include <stdint.h>

enum class OBJECTTYPE { BLOCK };

enum class BUFFER { VERTEX, INDEX, CONSTANT };

enum class RESOURCEID { TEXQUAD };

using namespace DirectX::SimpleMath;

struct ObjectData {
	RESOURCEID ID;
	void* vertices;
	void* indices;
	size_t numVertices;
	size_t numIndices;
	size_t stride;
	size_t offset;
	size_t cbSize;

	ObjectData() {}
	ObjectData(RESOURCEID ID, void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset, size_t cbSize) :
		ID(ID), vertices(vertices), indices(indices), numVertices(numVertices), numIndices(numIndices), stride(stride), offset(offset), cbSize(cbSize) {}
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

	iBufferData() {}
	iBufferData(ObjectData data) : numIndices(data.numIndices) {}
	iBufferData(ID3D11Buffer* iBuffer, ObjectData data) : iBuffer(iBuffer), numIndices(data.numIndices) {}
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
	std::unordered_map<RESOURCEID, vBufferData> vertexBufferMap;
	std::unordered_map<RESOURCEID, iBufferData> indexBufferMap;
	std::unordered_map<RESOURCEID, cBufferData> constantBufferMap;
public:
	/*--------------- INFORMATION --------------- 
	1. Maps the data to the ID location
	2. Creates a vertex buffer, index buffer, and a constant buffer
	*/
	void addResource(ObjectData& data);
	/*--------------- INFORMATION ---------------
	1. Updates the index buffer with the given data
	*/
	void updateVertexBuffer(RESOURCEID ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the vertex buffer with the given data
	*/
	void updateIndexBuffer(RESOURCEID ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the constant buffer with the given data
	*/
	void updateConstantBuffer(RESOURCEID ID, void* pData);

	vBufferData& getVBufferData(RESOURCEID ID);
	iBufferData& getIBufferData(RESOURCEID ID);
	cBufferData& getCBufferData(RESOURCEID ID);
	void initTexQuad();
};

#endif // !RESOURCEMANAGER_H
