#pragma once
#include "boost/uuid/uuid.hpp"
#include <sstream>
#include <string>

class Entity {
public:
	Entity();
	~Entity() = default;

	std::string GetUUID();
private:
	boost::uuids::uuid uuid;
};