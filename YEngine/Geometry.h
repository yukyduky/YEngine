#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Resource.h"
#include <assimp/Importer.hpp>

class Geometry : public Resource
{
private:
	VertexData m_Data;
	std::string m_Filename;
	bool createVertexBuffer(Renderer* renderer, ID3D11Buffer ** buffer, void* data, size_t& stride, size_t& offset, size_t numVertices);
	bool createIndexBuffer(Renderer* renderer, ID3D11Buffer** buffer, void * data, size_t& numIndices);
	bool createBuffers(Renderer* renderer, ID3D11Buffer** vBuffer, ID3D11Buffer** iBuffer, void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset);
	bool loadVertexDataFromFile(Renderer* renderer, const char* filename, VertexData& data);
	bool loadObjFile(Renderer* renderer, const char* filename, VertexData& data);

	bool load(Renderer* renderer, std::string filename, RESOURCETYPE::TYPE type);
public:
	Geometry(Renderer* renderer, std::string filename, RESOURCETYPE::TYPE type);
	virtual ~Geometry() {}
	void unload() override;
	bool reload(Renderer* renderer) override;
	const VertexData& getData() const;
};

#endif // OBJECT_H
