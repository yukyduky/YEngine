#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Resource.h"

class Object : public Resource
{
private:
	VertexData data;
public:
	bool load(ObjectData objData, RESOURCETYPE type, size_t ID) override;
	void unload() override;
	bool reload() override;

	VertexData getRenderData();
};

#endif // OBJECT_H
