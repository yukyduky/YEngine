#include "RenderOptimizer.h"
#include "GraphicsComponent.h"


void RenderOptimizer::init()
{
}

void RenderOptimizer::render()
{
}

void RenderOptimizer::addGraphics(GraphicsComponent * graphics_)
{
	RESOURCEGRAPHIC::ID texID = graphics_->getRenderTexID();
	RESOURCEOBJECT::ID objID = graphics_->getRenderObjID();
	this->allGraphics_[texID][objID].push_back(graphics_);
}
