#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <d3d11.h>
#include <SimpleMath.h>
#include "YEngine.h"

using namespace DirectX::SimpleMath;

namespace YEngine
{
	class Component
	{
	public:
		virtual ~Component() {}

		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void cleanup() = 0;
	};

	template<class Derived>
	class DerivedComponent : public Component
	{
	private:
		static std::bitset<BITMASK_SIZE> m_ComponentBitmask;
		static size_t m_ByteSize;
	public:
		virtual ~DerivedComponent() {}

		virtual void init() = 0;
		virtual void update(float dt) = 0;
		virtual void cleanup() = 0;

		static std::bitset<BITMASK_SIZE> getComponentBitmask();
		static size_t getByteSize();

		static void registerComponent(DerivedComponent<Derived>* derivedInstance, size_t byteSize, const char* componentName, size_t maxCapacity);
		static void unregisterComponent();
	};

	template<class Derived>
	inline std::bitset<BITMASK_SIZE> DerivedComponent<Derived>::getComponentBitmask()
	{
		return m_ComponentBitmask;
	}

	template<class Derived>
	inline size_t DerivedComponent<Derived>::getByteSize()
	{
		return m_ByteSize;
	}

	template<class Derived>
	inline void DerivedComponent<Derived>::registerComponent(DerivedComponent<Derived>* derivedInstance, size_t byteSize, const char* componentName, size_t maxCapacity)
	{
		m_ByteSize = byteSize;
		m_ComponentBitmask = YEngine::getComponentManager()->registerComponentType(derivedInstance, byteSize, componentName, maxCapacity);
	}

	template<class Derived>
	inline void DerivedComponent<Derived>::unregisterComponent()
	{
		YEngine::getComponentManager()->unregisterComponentType(m_ComponentBitmask);
	}

	template <class Derived> std::bitset<BITMASK_SIZE> DerivedComponent<Derived>::m_ComponentBitmask;
	template <class Derived> size_t DerivedComponent<Derived>::m_ByteSize;
}

#endif // COMPONENT_H
