#include "Object.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

boost::uuids::random_generator generator;

Object::Object()
{
	this->uuid = generator();
}

Object::~Object()
{
	//this->Dispose();
}

std::string Object::GetHashCode()
{
	std::stringstream ss;
	ss << uuid;
	return ss.str();
}

std::string Object::ToString()
{
	return typeid(this).name();
}
