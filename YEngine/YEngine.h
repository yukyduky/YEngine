#pragma once
#ifndef API_H
#define API_H

#include "IResourceManager.h"

enum class RENDERER {
	DEFERRED, FORWARD
};

namespace YEngine
{
	void init(RENDERER rendererType, HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed);
	void render();
	void cleanup();

	IResourceManager* getResourceManager();
}

#endif // API_H
