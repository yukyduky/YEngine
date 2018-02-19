#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"

class Texture : public Resource
{
private:
	TextureData data;
	std::wstring filename;
	bool loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename);
	bool load(std::wstring filename, RESOURCETYPE type);
public:
	Texture(std::wstring filename, RESOURCETYPE type);
	virtual void unload() override;
	virtual bool reload() override;
	TextureData getData();
};

#endif // TEXTURE_H
