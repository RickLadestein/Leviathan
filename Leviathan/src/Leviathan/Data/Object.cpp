#include "Object.h"
#include <mutex>
#include <iostream>
#include <typeinfo>
#include <sstream>  

size_t current_object_id = 0;
std::mutex guid_mutex = std::mutex();

size_t generateGuid();

Object::Object()
{
	this->uuid = generateGuid();
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

size_t generateGuid() {
	size_t tmp;
	guid_mutex.lock();
	current_object_id += 1;
	tmp = current_object_id;
	guid_mutex.unlock();
	return tmp;
}
