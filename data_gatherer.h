#include <iostream>
#include "database_handler.h"

#define GATHERER_NONE 0
#define GATHERER_FUNDRAISER 1
#define GATHERER_PERSON 2
#define GATHERER_PAYMENT 3

class DataGatherer
{
public:
	DataGatherer();
	~DataGatherer();
	static string get_selection(const int&, Fundraiser* = nullptr,
		Person* = nullptr, Payment* = nullptr);

	static bool confirm_delete();
	static Fundraiser* get_fundraiser_data();
	static Person* get_person_data();
	static Payment* get_payment_data();
};
