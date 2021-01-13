#pragma once
#include <typeinfo>
#include <string>
#include <sstream>   


class Object {
public:
	Object();
	~Object();

	std::string GetHashCode();

	virtual std::string ToString();
protected:
	long uuid;
};