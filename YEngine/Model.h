#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Resource.h"
#include <assimp/Importer.hpp>

class Model : public Resource
{
private:
	const aiScene* scene;
	const char* modelFilename;
	const char* texFilename;
	RenderData data;

	bool loadModel(const char* modelFilename, const char* texFilename);
public:
	bool load(const char* modelFilename, const char* texFilename, RESOURCETYPE type, size_t ID) override;
	void unload() override;
	bool reload(void* vertices, void* indices) override;

};

#endif // MODEL_H
