#include "Texture.h"
#include <WICTextureLoader.h>
#include "Locator.h"



bool Texture::loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename)
{
	bool success = true;
	HRESULT hr = DirectX::CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), filename.c_str(), texture, SRV);
	if (FAILED(hr)) 
	{
		success = false;
		assert(FAILED(hr) && "Failed to create texture from file - Resource");
	}
	return success;
}

bool Texture::load(std::wstring filename, RESOURCETYPE type)
{
	bool success = this->loadTexture(&m_Data.SRV, &m_Data.texture, filename);
	if (success) 
	{
		m_Type = type;
		m_Filename = filename;
	}
	return success;
}

Texture::Texture(std::wstring filename, RESOURCETYPE type)
{
	m_Loaded = this->load(filename, type);
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

bool Texture::reload()
{
	if (!m_Loaded) 
	{
		m_Loaded = this->loadTexture(&m_Data.SRV, &m_Data.texture, m_Filename);
	}
	return m_Loaded;
}

const TextureData& Texture::getData() const
{
	return m_Data;
}
