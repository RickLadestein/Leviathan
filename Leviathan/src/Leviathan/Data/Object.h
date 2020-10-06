#pragma once
#include <typeinfo>
#include <string>
#include <sstream>
#include <boost/uuid/uuid.hpp>           


class Object {
public:
	Object();
	~Object();

	std::string GetHashCode();

	virtual std::string ToString();
protected:
	boost::uuids::uuid uuid;
};