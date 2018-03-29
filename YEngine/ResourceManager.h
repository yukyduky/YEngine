#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "IResourceManager.h"
#include <unordered_map>
#include "Resource.h"
#include "Renderer.h"
#include "IDHandler.h"

namespace YEngine
{
	class ResourceManager : public IResourceManager
	{
	private:
		Renderer * m_Renderer;
	
		IDHandler m_ResourceIDs;
		std::unordered_map<size_t, Resource*> m_ResourceMap;
	
		std::wstring convertStrToWStr(std::string str);
		bool createObject(std::string filename, RESOURCETYPE::TYPE type, size_t& ID);
		bool createTexture(std::string filename, RESOURCETYPE::TYPE type, size_t& ID);
	public:
		ResourceManager();
		void init(Renderer*& renderer);
		//***********************************************************
		// Method:    createResource
		// FullName:  ResourceManager::createResource
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: std::string filename
		// Parameter: RESOURCETYPE type
		// Parameter: size_t ID
		// Description: Factory that creates the desired resource type. The resource can be retrieved using the ID.
		//***********************************************************
		bool createResource(std::string filename, RESOURCETYPE::TYPE type, size_t& ID) override;
		//***********************************************************
		// Method:    reloadResource
		// FullName:  ResourceManager::reloadResource
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: size_t ID
		// Description: Reloads the resource with the given ID. Reloading is for loading a resource that has already been loaded before and has since been unloaded.
		// It will attempt to load the resource using the filename given when it was loaded the first time.
		//***********************************************************
		bool reloadResource(size_t ID) override;
		//***********************************************************
		// Method:    unloadResource
		// FullName:  ResourceManager::unloadResource
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: size_t ID
		// Description: Unloads the resource with the given ID. Unloading is for releasing the resources used, back to the system.
		//***********************************************************
		void unloadResource(size_t ID) override;
		void removeResource(size_t ID) override;
		bool isResourceLoaded(size_t ID) override;
		bool getResourceData(VertexData& data, size_t ID);
		bool getResourceData(TextureData& data, size_t ID);
		void cleanup() override;
	};
}

#endif // RESOURCEMANAGER_H
