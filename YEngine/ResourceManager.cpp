#include "ResourceManager.h"
#include "Locator.h"



void ResourceManager::addResource(size_t ID, ObjectData & data)
{
	this->vertexBufferMap.insert(this->vertexBufferMap.end(), std::pair<size_t, vBufferData>(ID, vBufferData(data)));
	this->indexBufferMap.insert(this->indexBufferMap.end(), std::pair<size_t, iBufferData>(ID, iBufferData(data)));
	this->constantBufferMap.insert(this->constantBufferMap.end(), std::pair<size_t, cBufferData>(ID, cBufferData(data)));

	Locator::getD3D()->createVertexBuffer(&this->vertexBufferMap.at(ID).vBuffer, data.vertices, data.stride, data.offset, data.numVertices);
	Locator::getD3D()->createIndexBuffer(&this->vertexBufferMap.at(ID).vBuffer, data.indices, data.numVertices);
	Locator::getD3D()->createConstantBuffer(&this->vertexBufferMap.at(ID).vBuffer, data.cbSize);
}

void ResourceManager::updateVertexBuffer(size_t ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->vertexBufferMap.at(ID).vBuffer, pData, this->vertexBufferMap.at(ID).numVertices);
}

void ResourceManager::updateIndexBuffer(size_t ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->indexBufferMap.at(ID).iBuffer, pData, this->indexBufferMap.at(ID).numIndices);
}

void ResourceManager::updateConstant(size_t ID, void * pData)
{
	Locator::getD3D()->mapBuffer(&this->constantBufferMap.at(ID).cBuffer, pData, this->constantBufferMap.at(ID).cbSize);
}

vBufferData & ResourceManager::getVBufferData(size_t ID)
{
	return this->vertexBufferMap.at(ID);
}

iBufferData & ResourceManager::getIBufferData(size_t ID)
{
	return this->indexBufferMap.at(ID);
}

cBufferData & ResourceManager::getCBufferData(size_t ID)
{
	return this->constantBufferMap.at(ID);
}

/*GraphicsComponent har bara en ID, bitmasken håller koll på vad för inställningar objektet har
Detta medför även att det går att sortera på vilken ID som objekten har för att rendera dom i grupper*/