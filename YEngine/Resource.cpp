#include "Resource.h"



bool Resource::isLoaded()
{
	return m_Loaded;
}

RESOURCETYPE Resource::getType()
{
	return m_Type;
}
