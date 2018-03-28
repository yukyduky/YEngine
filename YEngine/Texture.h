#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"

class Texture : public Resource
{
private:
	TextureData m_Data;
	std::wstring m_Filename;
	bool loadTexture(Renderer* renderer, ID3D11ShaderResourceView** SRV, ID3D11Resource** texture, std::wstring filename);
	bool load(Renderer* renderer, std::wstring filename, RESOURCETYPE::TYPE type);
public:
	Texture(Renderer* renderer, std::wstring filename, RESOURCETYPE::TYPE type);
	virtual ~Texture() {}
	virtual void unload() override;
	virtual bool reload(Renderer* renderer) override;
	const TextureData& getData() const;
};

#endif // TEXTURE_H
