#include "Entity.h"

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

boost::uuids::random_generator generator;

Entity::Entity()
{
    this->uuid = generator();
}

std::string Entity::GetUUID()
{
	std::stringstream ss;
	ss << uuid;
	return ss.str();
}
