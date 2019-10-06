#include "payment.h"

Payment::Payment()
{
	id = "";
	amount = "";
	date = "";
}

Payment::Payment(string id, string amount, string date)
{
	this->id = id;
	this->amount = amount;
	this->date = date;
}

Payment::~Payment()
{
	// Do nothing
}