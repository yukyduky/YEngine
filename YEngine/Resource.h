#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <d3d11.h>
#include "SimpleMath.h"
#include <string>

using namespace DirectX::SimpleMath;

namespace RESOURCETYPE {
	enum TYPE { TEXTURE, OBJECT, FONT, SOUND, SIZE };
}

#define RESOURCE_TEXTURE   1
#define RESOURCE_OBJECT    2
#define RESOURCE_FONT      4
#define RESOURCE_SOUND     8

class Renderer;

struct ObjectData 
{
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

struct VertexData 
{
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
	RESOURCETYPE::TYPE m_Type;

public:
	virtual ~Resource() {}
	virtual void unload() = 0;
	virtual bool reload(Renderer* renderer) = 0;
	bool isLoaded();

	virtual RESOURCETYPE::TYPE getType();
};

#endif // RESOURCE_H
