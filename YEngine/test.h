#pragma once
#ifndef TEST_H
#define TEST_H

// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
namespace MEngine
{
	class Component // Do NOT inherit from this type directly
	{
	public:
		virtual ~Component() { Destroy(); };

		virtual void Initialize() {};
		virtual void Destroy() {};
	};

	template <class Derived> // Inherit this type for component definitions; Example: class UsefullComponent : public ComponentBase<UsefullComponent>
	class ComponentBase : public Component
	{
	public:
		static void Register(const ComponentBase<Derived>& templateInstance, uint32_t maxCount = 10)
		{
			ByteSize = sizeof(Derived);
			ComponentMask = MEngineComponentManager::RegisterComponentType(templateInstance, ByteSize, maxCount, MUTILITY_STRINGIFY(Derived));
		}

		static bool Unregister()
		{
			if (ComponentMask != INVALID_MENGINE_COMPONENT_MASK)
			{
				if (MEngineComponentManager::UnregisterComponentType(ComponentMask))
				{
					IsRegistered = false;
					return true;
				}
			}
			return false;
		}

		static MEngineComponentMask GetComponentMask() { return ComponentMask; }
		static uint32_t GetByteSize() { return ByteSize; }

	private:
		static MEngineComponentMask ComponentMask;
		static uint32_t ByteSize;
	};
}

#endif
