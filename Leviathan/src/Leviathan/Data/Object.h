#pragma once 
#include <string>


class Object {
public:
	Object();
	~Object();

	std::string GetHashCode();

	virtual std::string ToString();
private:
	size_t uuid;
};