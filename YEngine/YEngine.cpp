#include "YEngine.h"
#include "Renderer.h"
#include "DeferredRenderer.h"
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"
#include "PositionalComponent.h"
#include "CollisionComponent.h"
#include "LightComponent.h"
#include "PhysicsComponent.h"

namespace YEngine
{
	Renderer* m_Renderer = nullptr;
	ResourceManager m_RM;
	ComponentManager m_CM;

	
	void init(RENDERER rendererType, HINSTANCE hInstance, int CmdShow, size_t width, size_t height, bool windowed)
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

		GraphicsComponent::registerComponent(new GraphicsComponent(), sizeof(GraphicsComponent), "Graphics", 10);
		//CameraComponent::registerComponent(new CameraComponent(), sizeof(CameraComponent), "Camera", 10);
		//PositionalComponent::registerComponent(new PositionalComponent(), sizeof(PositionalComponent), "Position", 10);
		//CollisionComponent::registerComponent(new CollisionComponent(), sizeof(CollisionComponent), "Collision", 10);
		//LightComponent::registerComponent(new LightComponent(), sizeof(LightComponent), "Light", 10);
		//PhysicsComponent::registerComponent(new PhysicsComponent(), sizeof(PhysicsComponent), "Physics", 10);
	}
	
	void render()
	{
		m_Renderer->render();
	}
	
	void cleanup()
	{
		m_Renderer->cleanup();
		delete m_Renderer;
		m_RM.cleanup();
		m_CM.cleanup();
	}
	
	IResourceManager* getResourceManager()
	{
		return &m_RM;
	}
	
	IComponentManager* getComponentManager()
	{
		return &m_CM;
	}
}
