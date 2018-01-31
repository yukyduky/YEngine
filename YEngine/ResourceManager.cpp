#include "ResourceManager.h"
#include "Locator.h"



void ResourceManager::addResource(ObjectData & data)
{
	this->vertexBufferMap.insert(this->vertexBufferMap.end(), std::pair<RESOURCEID, vBufferData>(data.ID, vBufferData(data)));
	this->indexBufferMap.insert(this->indexBufferMap.end(), std::pair<RESOURCEID, iBufferData>(data.ID, iBufferData(data)));
	this->constantBufferMap.insert(this->constantBufferMap.end(), std::pair<RESOURCEID, cBufferData>(data.ID, cBufferData(data)));

	Locator::getD3D()->createVertexBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.vertices, data.stride, data.offset, data.numVertices);
	Locator::getD3D()->createIndexBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.indices, data.numVertices);
	Locator::getD3D()->createConstantBuffer(&this->vertexBufferMap.at(data.ID).vBuffer, data.cbSize);
}

void ResourceManager::updateVertexBuffer(RESOURCEID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->vertexBufferMap.at(ID).vBuffer, pData, this->vertexBufferMap.at(ID).numVertices);
}

void ResourceManager::updateIndexBuffer(RESOURCEID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->indexBufferMap.at(ID).iBuffer, pData, this->indexBufferMap.at(ID).numIndices);
}

void ResourceManager::updateConstantBuffer(RESOURCEID ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->constantBufferMap.at(ID).cBuffer, pData, this->constantBufferMap.at(ID).cbSize);
}

vBufferData & ResourceManager::getVBufferData(RESOURCEID ID)
{
	return this->vertexBufferMap.at(ID);
}

iBufferData & ResourceManager::getIBufferData(RESOURCEID ID)
{
	return this->indexBufferMap.at(ID);
}

cBufferData & ResourceManager::getCBufferData(RESOURCEID ID)
{
	return this->constantBufferMap.at(ID);
}

void ResourceManager::initTexQuad()
{
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoords;
	};

	std::array<Vertex, 4> vertices;

	vertices[0].position = Vector3(0.0f, 1.0f, 0.0f);
	vertices[1].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[2].position = Vector3(1.0f, 1.0f, 0.0f);
	vertices[3].position = Vector3(1.0f, 0.0f, 0.0f);

	vertices[0].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[1].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[2].normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[3].normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[0].texCoords = Vector2(0.0f, 1.0f);
	vertices[1].texCoords = Vector2(0.0f, 0.0f);
	vertices[2].texCoords = Vector2(1.0f, 1.0f);
	vertices[3].texCoords = Vector2(1.0f, 0.0f);

	size_t indices[] = {
		0, 1, 2,
		2, 1, 3,
	};

	ObjectData data = ObjectData(RESOURCEID::TEXQUAD, vertices.data(), indices, vertices.size(), 6, sizeof(Vertex), 0, 0);
	this->addResource(data);
}
