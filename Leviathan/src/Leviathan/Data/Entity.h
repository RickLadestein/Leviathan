#pragma once
#include <string>

class Entity {
public:
	Entity();
	~Entity() = default;

	std::string GetUUID();
	virtual std::string ToString();
private:
	size_t uuid;
};