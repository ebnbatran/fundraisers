#include "person.h"

class Fundraiser
{
public:
	string id;
	string title;
	string amount;
	string count;
	string end_date;

public:
	Fundraiser();
	Fundraiser(string, string, string, string, string);
	~Fundraiser();
};
