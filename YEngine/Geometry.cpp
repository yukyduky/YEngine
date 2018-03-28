#include "Geometry.h"
#include <cassert>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Renderer.h"
#include "Locator.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;
};

bool Geometry::createVertexBuffer(Renderer* renderer, ID3D11Buffer** buffer, void* data, size_t& stride, size_t& offset, size_t numVertices)
{
	return renderer->createResource(buffer, data, stride, offset, numVertices);
}

bool Geometry::createIndexBuffer(Renderer* renderer, ID3D11Buffer** buffer, void * data, size_t& numIndices)
{
	return renderer->createResource(buffer, data, numIndices);
}

bool Geometry::createBuffers(Renderer* renderer, ID3D11Buffer** vBuffer, ID3D11Buffer** iBuffer, void* vertices, void* indices, size_t numVertices, size_t numIndices, size_t stride, size_t offset)
{
	bool allLoaded = false;
	bool vLoaded = false;
	bool iLoaded = false;

	vLoaded = this->createVertexBuffer(renderer, vBuffer, vertices, stride, offset, numVertices);

	iLoaded = this->createIndexBuffer(renderer, iBuffer, indices, numIndices);

	if (vLoaded && iLoaded) 
	{
		allLoaded = true;
	}
	else if (vLoaded) 
	{
		(*vBuffer)->Release();
	}
	else if (iLoaded) 
	{
		(*iBuffer)->Release();
	}

	return allLoaded;
}

bool Geometry::loadVertexDataFromFile(Renderer* renderer, const char* filename, VertexData& data)
{
	bool success = false;
	RawData rawData;
	std::vector<std::vector<std::vector<int>>> parsedDataSets;
	if (Locator::getConfigHandler()->loadRawData(rawData, filename))
	{
		for (auto &i : rawData.dataSets) 
		{
			std::vector<std::vector<int>> parsedDataRows;
			for (auto &k : i) 
			{
				std::vector<int> parsedData;
				for (auto &h : k) 
				{
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

		if (this->createBuffers(renderer, &vBuffer, &iBuffer, vertices, indices, numVertices, numIndices, stride, offset))
		{
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

bool Geometry::loadObjFile(Renderer* renderer, const char* filename, VertexData& data)
{
	bool success = false;
	RawData rawData;
	std::vector<std::vector<std::vector<int>>> parsedDataSets;
	if (Locator::getConfigHandler()->loadRawData(rawData, filename)) 
	{
		for (auto &i : rawData.dataSets) 
		{
			std::vector<std::vector<int>> parsedDataRows;
			for (auto &k : i) 
			{
				std::vector<int> parsedData;
				for (auto &h : k) 
				{
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

		if (this->createBuffers(renderer, &vBuffer, &iBuffer, vertices, indices, numVertices, numIndices, stride, offset))
		{
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

bool Geometry::load(Renderer* renderer, std::string filename, RESOURCETYPE::TYPE type)
{
	bool success = true;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene) 
	{
		std::string errorStr = importer.GetErrorString();
		assert(scene && "Resource (Model) - Failed to import model");
		success = false;
	}
	else {
		std::vector<Vertex> vertices;
		std::vector<int> indices;

		for (size_t i = 0; i < scene->mNumMeshes; i++) 
		{
			aiMesh* mesh = scene->mMeshes[i];

			for (size_t k = 0; k < mesh->mNumVertices; k++)
			{
				Vertex v;

				v.position.x = mesh->mVertices[k].x;
				v.position.y = mesh->mVertices[k].y;
				v.position.z = mesh->mVertices[k].z;

				v.normal.x = mesh->mNormals[k].x;
				v.normal.y = mesh->mNormals[k].y;
				v.normal.z = mesh->mNormals[k].z;

				if (mesh->HasTextureCoords(0)) 
				{
					v.texCoords.x = mesh->mTextureCoords[0][k].x;
					v.texCoords.y = mesh->mTextureCoords[0][k].y;
				}

				vertices.push_back(v);
			}
			
			for (size_t c = 0; c < mesh->mNumFaces; c++)
			{
				for (size_t e = 0; e < mesh->mFaces[c].mNumIndices; e++)
				{
					indices.push_back(mesh->mFaces[c].mIndices[e]);
				}
			}
		}

		ID3D11Buffer* vBuffer = nullptr;
		ID3D11Buffer* iBuffer = nullptr;

		if (this->createBuffers(renderer, &vBuffer, &iBuffer, vertices.data(), indices.data(), vertices.size(), indices.size(), sizeof(Vertex), 0))
		{
			m_Type = type;
			m_Filename = filename;
			m_Data = VertexData(vBuffer, iBuffer, vertices.size(), indices.size(), indices.size() / 3, sizeof(Vertex), 0);
		}
	}

	return success;
}

Geometry::Geometry(Renderer* renderer, std::string filename, RESOURCETYPE::TYPE type)
{
	m_Loaded = false;
	std::string ext = filename.substr(filename.find_last_of('.') + 1, filename.size() - filename.find_last_of('.'));

	if (ext == "obj")
	{
		m_Loaded = this->load(renderer, filename, type);
	}
	else if (ext == "yk")
	{

	}
}

void Geometry::unload()
{
	if (m_Loaded)
	{
		m_Data.vBuffer->Release();
		m_Data.iBuffer->Release();
		m_Loaded = false;
	}
}

bool Geometry::reload(Renderer* renderer)
{
	if (!m_Loaded)
	{
		m_Loaded = this->load(renderer, m_Filename, m_Type);
	}
	return m_Loaded;
}

const VertexData& Geometry::getData() const
{
	return m_Data;
}
