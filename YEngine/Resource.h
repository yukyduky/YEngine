#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <d3d11.h>
#include "SimpleMath.h"
#include <string>

using namespace DirectX::SimpleMath;

enum class RESOURCETYPE { TEXTURE, OBJECT, FONT, SOUND };

struct ObjectData {
	void* vertices;
	void* indices;
	int numVertices;
	int numIndices;
	int numFaces;
	int stride;
	int offset;

	ObjectData() {}
	ObjectData(void* vertices, void* indices, int numVertices, int numIndices, int numFaces, int stride, int offset) :
		vertices(vertices), indices(indices), numFaces(numFaces), stride(stride), offset(offset) {}
};

struct VertexData {
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;
	int numVertices;
	int numIndices;
	int numFaces;
	int stride;
	int offset;

	VertexData() {}
	VertexData(ID3D11Buffer* vBuffer, ID3D11Buffer* iBuffer, ObjectData data) :
		vBuffer(vBuffer), iBuffer(iBuffer), numVertices(data.numVertices), numIndices(data.numIndices), numFaces(data.numFaces), stride(data.stride), offset(data.offset) {}
	VertexData(ID3D11Buffer* vBuffer, ID3D11Buffer* iBuffer, int numVertices, int numIndices, int numFaces, int stride, int offset) :
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
	
protected:
	bool loaded;
	RESOURCETYPE type;

public:
	virtual ~Resource() {}
	virtual void unload() = 0;
	virtual bool reload() = 0;
	bool isLoaded();

	virtual RESOURCETYPE getType();
};

#endif // RESOURCE_H
