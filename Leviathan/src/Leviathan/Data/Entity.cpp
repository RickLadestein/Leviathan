#include "Entity.h"

Entity::Entity()
{
}

std::string Entity::GetUUID()
{
	std::stringstream ss;
	ss << 1;
	return ss.str();
}
