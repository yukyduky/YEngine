#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <d3d11.h>
#include "SimpleMath.h"
#include <string>

using namespace DirectX::SimpleMath;

enum class RESOURCE { TEXTURE, OBJECT, FONT, SOUND };

class Renderer;

struct ObjectData 
{
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

struct VertexData 
{
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

struct TextureData 
{
	ID3D11ShaderResourceView* SRV;
	ID3D11Resource* texture;
};

struct RenderData 
{
	VertexData vData;
	TextureData texData;
	RenderData() {}
	RenderData(VertexData vData, TextureData texData) : vData(vData), texData(texData) {}
};

class Resource
{
private:
	
protected:
	bool m_Loaded;
	RESOURCE m_Type;

public:
	virtual ~Resource() {}
	virtual void unload() = 0;
	virtual bool reload(Renderer* renderer) = 0;
	bool isLoaded();

	virtual RESOURCE getType();
};

#endif // RESOURCE_H
