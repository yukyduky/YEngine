#include "YEngine.h"
#include "Renderer.h"
#include "DeferredRenderer.h"
#include "ResourceManager.h"
#include "ComponentManager.h"

namespace YEngine
{
	Renderer* m_Renderer = nullptr;
	ResourceManager m_RM;
	ComponentManager m_CM;
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
	m_CM.init();
}

void YEngine::render()
{
	m_Renderer->render();
}

void YEngine::cleanup()
{
	delete m_Renderer;
	m_RM.cleanup();
}

IResourceManager* YEngine::getResourceManager()
{
	return &m_RM;
}

IComponentManager* YEngine::getComponentManager()
{
	return &m_CM;
}
