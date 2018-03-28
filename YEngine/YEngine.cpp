#include "YEngine.h"
#include "Renderer.h"
#include "DeferredRenderer.h"
#include "ResourceManager.h"

namespace YEngine
{
	Renderer* m_Renderer = nullptr;
	ResourceManager m_RM;
}

void YEngine::init(RENDERER rendererType, HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed)
{
	switch (rendererType)
	{
	case RENDERER::DEFERRED:
		m_Renderer = new DeferredRenderer();
		break;
	case RENDERER::FORWARD:
		break;
	}
	m_Renderer->init(hInstance, CmdShow, width, height, windowed);

	m_RM.init(m_Renderer);
}

void YEngine::render()
{
	m_Renderer->render();
}

void YEngine::cleanup()
{
}

IResourceManager* YEngine::getResourceManager()
{
	return &m_RM;
}
