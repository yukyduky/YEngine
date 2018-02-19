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
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	Factory that creates the desired resource type. The resource can be retrieved using the ID.
	*/
	bool createResource(std::string filename, RESOURCETYPE type, size_t ID);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	Reloads the resource with the given ID. Reloading is for loading a resource that has already been loaded before and has since been unloaded.
	It will attempt to load the resource using the filename given when it was loaded the first time.
	*/
	bool reloadResource(size_t ID);
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	Unloads the resource with the given ID. Unloading is for releasing the resources used, back to the system.
	*/
	void unloadResource(size_t ID);
	bool isResourceLoaded(size_t ID);
	bool getResourceData(VertexData& data, size_t ID);
	bool getResourceData(TextureData& data, size_t ID);
	
};

#endif // RESOURCEMANAGER_H
