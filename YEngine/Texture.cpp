#include "Texture.h"
#include <WICTextureLoader.h>
#include "Locator.h"



bool Texture::loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename)
{
	bool success = true;
	HRESULT hr = DirectX::CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), filename.c_str(), texture, SRV);
	if (FAILED(hr)) {
		success = false;
		assert(FAILED(hr) && "Failed to create texture from file - Resource");
	}
	return success;
}

bool Texture::load(std::wstring filename, RESOURCETYPE type)
{
	bool success = this->loadTexture(&this->data.SRV, &this->data.texture, filename);
	if (success) {
		this->type = type;
		this->filename = filename;
	}
	return success;
}

Texture::Texture(std::wstring filename, RESOURCETYPE type)
{
	this->loaded = this->load(filename, type);
}

void Texture::unload()
{
	this->data.SRV->Release();
	this->data.texture->Release();
	this->loaded = false;
}

bool Texture::reload()
{
	if (!this->loaded) {
		this->loaded = this->loadTexture(&this->data.SRV, &this->data.texture, filename);
	}
	return this->loaded;
}

const TextureData& Texture::getData() const
{
	return this->data;
}
