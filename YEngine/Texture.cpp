#include "Texture.h"
#include <WICTextureLoader.h>
#include "Renderer.h"
#include "Locator.h"



bool Texture::loadTexture(Renderer* renderer, ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename)
{
	return renderer->createResource(&m_Data.texture, &m_Data.SRV, filename);
}

bool Texture::load(Renderer* renderer, std::wstring filename, RESOURCETYPE::TYPE type)
{
	bool success = this->loadTexture(renderer, &m_Data.SRV, &m_Data.texture, filename);
	if (success) 
	{
		m_Type = type;
		m_Filename = filename;
	}
	return success;
}

Texture::Texture(Renderer* renderer, std::wstring filename, RESOURCETYPE::TYPE type)
{
	m_Loaded = this->load(renderer, filename, type);
}

void Texture::unload()
{
	if (m_Loaded) 
	{
		m_Loaded = false;
		m_Data.SRV->Release();
		m_Data.texture->Release();
	}
}

bool Texture::reload(Renderer* renderer)
{
	if (!m_Loaded) 
	{
		m_Loaded = this->loadTexture(renderer, &m_Data.SRV, &m_Data.texture, m_Filename);
	}
	return m_Loaded;
}

const TextureData& Texture::getData() const
{
	return m_Data;
}
