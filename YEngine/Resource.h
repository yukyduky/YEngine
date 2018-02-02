#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

enum class RESOURCETYPE { TEXTURE, OBJECT, MODEL, SOUND };

struct ObjectData {
	void* vertices;
	void* indices;
	size_t numVertices;
	size_t numIndices;
	size_t numFaces;
	size_t stride;
	size_t offset;

	ObjectData() {}
	ObjectData(void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t numFaces, size_t stride, size_t offset) :
		vertices(vertices), indices(indices), numFaces(numFaces), stride(stride), offset(offset) {}
};

struct VertexData {
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	size_t numVertices;
	size_t numIndices;
	size_t numFaces;
	size_t stride;
	size_t offset;

	VertexData() {}
	VertexData(ID3D11Buffer* vBuffer, ID3D11Buffer* iBuffer, ObjectData data) :
		vBuffer(vBuffer), iBuffer(iBuffer), numVertices(data.numVertices), numIndices(data.numIndices), numFaces(data.numFaces), stride(data.stride), offset(data.offset) {}
	VertexData(ID3D11Buffer* vBuffer, ID3D11Buffer* iBuffer, size_t numVertices, size_t numIndices, size_t numFaces, size_t stride, size_t offset) :
		vBuffer(vBuffer), iBuffer(iBuffer), numVertices(numVertices), numIndices(numIndices), numFaces(numFaces), stride(stride), offset(offset) {}
};

struct TextureData {
	ID3D11ShaderResourceView* SRV;
	ID3D11Resource* texture;
};

struct RenderData {
	VertexData vData;
	TextureData texData;
	RenderData() {}
	RenderData(VertexData vData, TextureData texData) : vData(vData), texData(texData) {}
};

class Resource
{
private:
	bool createVertexBuffer(ID3D11Buffer ** gVertexBuffer, void* v, size_t& stride, size_t& offset, size_t numVertices);
	bool createIndexBuffer(ID3D11Buffer ** gIndexBuffer, void * data, size_t & numIndices);
protected:
	bool loaded;
	size_t ID;
	RESOURCETYPE type;

	bool createBuffers(ID3D11Buffer** vBuffer, ID3D11Buffer** iBuffer, void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset);
	bool loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, const char* filename);
public:
	virtual bool load(const char* modelFilename, const char* texFilename, RESOURCETYPE type, size_t ID);
	virtual bool load(ObjectData objData, RESOURCETYPE type, size_t ID);
	virtual void unload() = 0;
	virtual bool reload(void* vertices, void* indices) = 0;
	virtual bool isLoaded();

	virtual RESOURCETYPE getResourceType();
	virtual size_t getID();
};

#endif // RESOURCE_H
