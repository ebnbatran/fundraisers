#include "fundraiser.h"

Fundraiser::Fundraiser()
{
	id = "";
	title = "";
	amount = "";
	count = "";
	end_date = "";
}

Fundraiser::Fundraiser(string id, string title, string amount, string count, string end_date)
{
	this->id = id;
	this->title = title;
	this->amount = amount;
	this->count = count;
	this->end_date = end_date;
}

Fundraiser::~Fundraiser()
{
	// Do nothing
}
