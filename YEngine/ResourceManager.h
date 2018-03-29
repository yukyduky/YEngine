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
		bool createObject(std::string filename, RESOURCE type, size_t& ID);
		bool createTexture(std::string filename, RESOURCE type, size_t& ID);
	public:
		ResourceManager();
		void init(Renderer*& renderer);
		bool createResource(std::string filename, RESOURCE type, size_t& ID) override;
		bool reloadResource(size_t ID) override;
		void unloadResource(size_t ID) override;
		void removeResource(size_t ID) override;
		bool isResourceLoaded(size_t ID) override;
		void cleanup() override;

		bool getResourceData(VertexData& data, size_t ID) override;
		bool getResourceData(TextureData& data, size_t ID) override;
	};
}

#endif // RESOURCEMANAGER_H
