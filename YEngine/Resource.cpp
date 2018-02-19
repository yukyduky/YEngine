#include "Resource.h"



bool Resource::isLoaded()
{
	return this->loaded;
}

RESOURCETYPE Resource::getType()
{
	return this->type;
}
