#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <d3d11.h>
#include <array>
#include <stdint.h>

enum class OBJECTTYPE { BLOCK };

enum class BUFFER { VERTEX, INDEX, CONSTANT };

struct ObjectData {
	void* vertices;
	void* indices;
	size_t numVertices;
	size_t numIndices;
	size_t stride;
	size_t offset;
	size_t cbSize;

	ObjectData() {}
	ObjectData(void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset, size_t cbSize) : 
		vertices(vertices), indices(indices), numVertices(numVertices), numIndices(numIndices), stride(stride), offset(offset), cbSize(cbSize) {}
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
	std::unordered_map<size_t, vBufferData> vertexBufferMap;
	std::unordered_map<size_t, iBufferData> indexBufferMap;
	std::unordered_map<size_t, cBufferData> constantBufferMap;
public:
	/*--------------- INFORMATION --------------- 
	1. Maps the data to the ID location
	2. Creates a vertex buffer, index buffer, and a constant buffer
	*/
	void addResource(size_t ID, ObjectData& data);
	/*--------------- INFORMATION ---------------
	1. Updates the index buffer with the given data
	*/
	void updateVertexBuffer(size_t ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the vertex buffer with the given data
	*/
	void updateIndexBuffer(size_t ID, void* pData);
	/*--------------- INFORMATION ---------------
	1. Updates the constant buffer with the given data
	*/
	void updateConstant(size_t ID, void* pData);

	vBufferData& getVBufferData(size_t ID);
	iBufferData& getIBufferData(size_t ID);		
	cBufferData& getCBufferData(size_t ID);
};

#endif // !RESOURCEMANAGER_H
