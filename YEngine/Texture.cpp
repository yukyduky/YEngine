#include "Texture.h"



bool Texture::load(const wchar_t * filename, RESOURCETYPE type, size_t ID)
{
	bool success = this->loadTexture(&this->data.SRV, &this->data.texture, filename);
	if (success) {
		this->loaded = true;
		this->ID = ID;
		this->type = type;
		this->filename = filename;
	}
	return success;
}

void Texture::unload()
{
	this->data.SRV->Release();
	this->data.texture->Release();
	this->loaded = false;
}

bool Texture::reload()
{
	return this->loaded = this->loadTexture(&this->data.SRV, &this->data.texture, filename);
}
