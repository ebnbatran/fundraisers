#include "person.h"

Person::Person()
{
	id = "";
	name = "";
	method = "";
}

Person::Person(string id, string name, string method)
{
	this->id = id;
	this->name = name;
	this->method = method;
}

Person::~Person()
{
	// Do nothing
}