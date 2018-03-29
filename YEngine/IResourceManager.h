#pragma once
#ifndef IRESOURCEMANAGER_H
#define IRESOURCEMANAGER_H

#include "Resource.h"

namespace YEngine
{
	class IResourceManager
	{
	public:
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
		virtual bool createResource(std::string filename, RESOURCETYPE::TYPE type, size_t& ID) = 0;
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
		virtual bool reloadResource(size_t ID) = 0;
		//***********************************************************
		// Method:    unloadResource
		// FullName:  ResourceManager::unloadResource
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: size_t ID
		// Description: Unloads the resource with the given ID. Unloading releases the memory used back to the system.
		//***********************************************************
		virtual void unloadResource(size_t ID) = 0;
		//***********************************************************
		// Method:    removeResource
		// FullName:  IResourceManager::removeResource
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: size_t ID
		// Description: Removes the resource completely and frees up the ID
		//***********************************************************
		virtual void removeResource(size_t ID) = 0;
		virtual bool isResourceLoaded(size_t ID) = 0;
		virtual void cleanup() = 0;
	};
}

#endif
