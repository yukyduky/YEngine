#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Resource.h"

class Texture : public Resource
{
private:
	TextureData data;
	const wchar_t* filename;
public:
	virtual bool load(const wchar_t* filename, RESOURCETYPE type, size_t ID) override;
	virtual void unload() override;
	virtual bool reload() override;
};

#endif // TEXTURE_H
