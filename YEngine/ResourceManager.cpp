#include "ResourceManager.h"
#include "Geometry.h"
#include "Texture.h"


std::wstring ResourceManager::convertStrToWStr(std::string str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

bool ResourceManager::createObject(std::string filename, RESOURCETYPE type, size_t ID)
{
	this->resourceMap.insert(this->resourceMap.end(), std::pair<size_t, Resource*>(ID, new Geometry(filename, type)));
	return this->resourceMap[ID]->isLoaded();
}

bool ResourceManager::createTexture(std::string filename, RESOURCETYPE type, size_t ID)
{
	std::wstring wfilename = this->convertStrToWStr(filename);
	this->resourceMap.insert(this->resourceMap.end(), std::pair<size_t, Resource*>(ID, new Texture(wfilename, type)));
	return this->resourceMap[ID]->isLoaded();
}

bool ResourceManager::createResource(std::string filename, RESOURCETYPE type, size_t ID)
{
	bool loaded = false;
	switch (type)
	{
	case RESOURCETYPE::TEXTURE:
		loaded = this->createTexture(filename, type, ID);
		break;
	case RESOURCETYPE::OBJECT:
		loaded = this->createObject(filename, type, ID);
		break;
	case RESOURCETYPE::FONT:
		break;
	case RESOURCETYPE::SOUND:
		break;
	}
	return loaded;
}

bool ResourceManager::reloadResource(size_t ID)
{
	return this->resourceMap[ID]->reload();
}

void ResourceManager::unloadResource(size_t ID)
{
	this->resourceMap[ID]->unload();
}

bool ResourceManager::isResourceLoaded(size_t ID)
{
	return this->resourceMap[ID]->isLoaded();
}

bool ResourceManager::getResourceData(VertexData & data, size_t ID)
{
	bool success = false;
	if (this->resourceMap[ID]->getType() == RESOURCETYPE::OBJECT) {
		success = true;
		data = static_cast<Geometry*>(this->resourceMap[ID])->getData();
	}
	return success;
}

bool ResourceManager::getResourceData(TextureData & data, size_t ID)
{
	bool success = false;
	if (this->resourceMap[ID]->getType() == RESOURCETYPE::TEXTURE) {
		success = true;
		data = static_cast<Texture*>(this->resourceMap[ID])->getData();
	}
	return success;
}

void ResourceManager::cleanup()
{
	for (auto &i : this->resourceMap) {
		i.second->unload();
		delete i.second;
	}
}
