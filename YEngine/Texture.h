#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"

class Texture : public Resource
{
private:
	TextureData m_Data;
	std::wstring m_Filename;
	bool loadTexture(ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename);
	bool load(std::wstring filename, RESOURCETYPE type);
public:
	Texture(std::wstring filename, RESOURCETYPE type);
	virtual ~Texture() {}
	virtual void unload() override;
	virtual bool reload() override;
	const TextureData& getData() const;
};

#endif // TEXTURE_H
