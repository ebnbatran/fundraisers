#include <iostream>
#include <iomanip>
using namespace std;

#include "fundraiser.h"

class SQL
{
public:
	static string create_fundraiser_main_table();
	
	static string create_fundraiser(Fundraiser*);
	static string modify_fundraiser(Fundraiser*);
	static string remove_fundraiser(Fundraiser*);

	static string create_person(Person*, Fundraiser*);
	static string modify_person(Person*, Fundraiser*);
	static string remove_person(Person*, Fundraiser*);

	static string create_payment(Payment*, Person*, Fundraiser*);
	static string modify_payment(Payment*, Person*, Fundraiser*);
	static string remove_payment(Payment*, Person*, Fundraiser*);
};