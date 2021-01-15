#pragma once
#include <sstream>
#include <string>

class Entity {
public:
	Entity();
	~Entity() = default;

	std::string GetUUID();
private:
};