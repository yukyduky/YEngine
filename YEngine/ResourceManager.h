#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resource.h"
#include <unordered_map>

class ResourceManager
{
private:
	std::unordered_map<size_t, Resource*> resourceMap;

	std::wstring convertStrToWStr(std::string str);
	bool createObject(std::string filename, RESOURCETYPE type, size_t ID);
	bool createTexture(std::string filename, RESOURCETYPE type, size_t ID);
public:
	bool createResource(std::string filename, RESOURCETYPE type, size_t ID);
	bool reloadResource(size_t ID);
	bool isResourceLoaded(size_t ID);
	bool getResourceData(VertexData& data, size_t ID);
	bool getResourceData(TextureData& data, size_t ID);
	
};

#endif // RESOURCEMANAGER_H
