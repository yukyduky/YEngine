#include "Resource.h"



bool Resource::isLoaded()
{
	return m_Loaded;
}

RESOURCE Resource::getType()
{
	return m_Type;
}
