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
	bool createVertexBuffer(ID3D11Buffer ** gVertexBuffer, void* v, int& stride, int& offset, int numVertices);
	bool createIndexBuffer(ID3D11Buffer ** gIndexBuffer, void * data, int & numIndices);
	bool createBuffers(ID3D11Buffer** vBuffer, ID3D11Buffer** iBuffer, void* vertices, void* indices, int numVertices, int numIndices, int stride, int offset);
	bool loadVertexDataFromFile(const char* filename, VertexData& data);
	bool loadObjFile(const char* filename, VertexData& data);

	bool load(std::string filename, RESOURCETYPE::TYPE type);
public:
	Geometry(std::string filename, RESOURCETYPE::TYPE type);
	virtual ~Geometry() {}
	void unload() override;
	bool reload() override;
	const VertexData& getData() const;
};

#endif // OBJECT_H
