#include <sqlite3.h>
#include <vector>
#include "sql.h"

#define DATABASE_CREATE 0
#define DATABASE_MODIFY 1
#define DATABASE_REMOVE 2

class DatabaseHandler
{
public:

public:
	DatabaseHandler();
	DatabaseHandler(string);
	~DatabaseHandler();

	bool perform_action(const int&, Fundraiser* = nullptr, Person* = nullptr,
		Payment* = nullptr);

	vector<Fundraiser*> get_all_fundraisers();
	vector<Person*> get_all_persons(Fundraiser*);
	vector<Payment*> get_all_payments(Person*, Fundraiser*);

private:
	sqlite3* db;
	string filename;

private:
	bool open_db();
	bool create_main_fundraiser_table();
};
