#pragma once
#ifndef RENDEROPTIMIZER_H
#define RENDEROPTIMIZER_H

#include <list>
#include <array>

class GraphicsComponent;

class RenderOptimizer
{
private:
	std::array<std::array<std::list<GraphicsComponent*>, RESOURCEOBJECT::SIZE>, RESOURCEGRAPHIC::SIZE> allGraphics_;
public:
	void init();
	void render();
	void addGraphics(GraphicsComponent* graphics_);
};

#endif // !RENDEROPTIMIZER_H
