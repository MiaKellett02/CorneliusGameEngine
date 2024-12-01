//Project includes.
#include "Component.h"
#include "Entity.h"

//Library includes.

Component::Component(Entity* a_ownerEntity)
{
	m_ownerEntity = a_ownerEntity;
}

Component::~Component()
{
}
