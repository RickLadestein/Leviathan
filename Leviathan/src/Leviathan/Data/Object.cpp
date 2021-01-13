#include "Object.h"

unsigned long current_object_id = 0;

Object::Object()
{
	this->uuid = current_object_id + 1;
	current_object_id += 1;
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
