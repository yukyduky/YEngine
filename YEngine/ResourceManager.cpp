#include "ResourceManager.h"
#include "Geometry.h"
#include "Texture.h"


namespace YEngine
{
	std::wstring ResourceManager::convertStrToWStr(std::string str)
	{
		std::wstring wstr(str.length(), L' ');
		std::copy(str.begin(), str.end(), wstr.begin());
		return wstr;
	}
	
	bool ResourceManager::createObject(std::string filename, RESOURCETYPE::TYPE type, size_t& ID)
	{
		ID = m_ResourceIDs.getNewID();
		m_ResourceMap.insert(m_ResourceMap.end(), std::pair<size_t, Resource*>(ID, new Geometry(m_Renderer, filename, type)));
		return m_ResourceMap[ID]->isLoaded();
	}
	
	bool ResourceManager::createTexture(std::string filename, RESOURCETYPE::TYPE type, size_t& ID)
	{
		std::wstring wfilename = this->convertStrToWStr(filename);
		ID = m_ResourceIDs.getNewID();
		m_ResourceMap.insert(m_ResourceMap.end(), std::pair<size_t, Resource*>(ID, new Texture(m_Renderer, wfilename, type)));
		return m_ResourceMap[ID]->isLoaded();
	}
	
	ResourceManager::ResourceManager()
	{
		m_Renderer = nullptr;
	}
	
	void ResourceManager::init(Renderer*& renderer)
	{
		m_Renderer = renderer;
	}
	
	bool ResourceManager::createResource(std::string filename, RESOURCETYPE::TYPE type, size_t& ID)
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
		return m_ResourceMap[ID]->reload(m_Renderer);
	}
	
	void ResourceManager::unloadResource(size_t ID)
	{
		m_ResourceMap[ID]->unload();
	}
	
	void ResourceManager::removeResource(size_t ID)
	{
		if (m_ResourceIDs.remove(ID))
		{
			m_ResourceMap[ID]->unload();
			m_ResourceMap.erase(ID);
		}
	}
	
	bool ResourceManager::isResourceLoaded(size_t ID)
	{
		return m_ResourceMap[ID]->isLoaded();
	}
	
	bool ResourceManager::getResourceData(VertexData & data, size_t ID)
	{
		bool success = false;
		if (m_ResourceMap[ID]->getType() == RESOURCETYPE::OBJECT) 
		{
			success = true;
			data = static_cast<Geometry*>(m_ResourceMap[ID])->getData();
		}
		return success;
	}
	
	bool ResourceManager::getResourceData(TextureData & data, size_t ID)
	{
		bool success = false;
		if (m_ResourceMap[ID]->getType() == RESOURCETYPE::TEXTURE) 
		{
			success = true;
			data = static_cast<Texture*>(m_ResourceMap[ID])->getData();
		}
		return success;
	}
	
	void ResourceManager::cleanup()
	{
		for (auto &i : m_ResourceMap) 
		{
			i.second->unload();
			delete i.second;
		}
		m_ResourceIDs.clear();
	}
}
