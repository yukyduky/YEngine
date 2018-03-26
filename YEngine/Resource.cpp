#include "Resource.h"



bool Resource::isLoaded()
{
	return m_Loaded;
}

RESOURCETYPE::TYPE Resource::getType()
{
	return m_Type;
}
