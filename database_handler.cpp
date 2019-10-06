#include "database_handler.h"

DatabaseHandler::DatabaseHandler()
{
	db = nullptr;
	filename = "";
}

DatabaseHandler::DatabaseHandler(string filename)
{
	this->filename = filename;
	this->open_db();
}

DatabaseHandler::~DatabaseHandler()
{
	sqlite3_close(db);
}

bool DatabaseHandler::open_db()
{
	int rc = sqlite3_open(filename.c_str(), &db);
	
	if (rc) return false;

	string sql = "SELECT * FROM fundraisers;";
	rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
	
	if (rc) 
		if(!create_main_fundraiser_table())
			return false;

	return true;
}

bool DatabaseHandler::create_main_fundraiser_table()
{
	if (!db) return false;
	
	string sql = SQL::create_fundraiser_main_table();

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);

	if (rc) return false;
	
	return true;
}

bool DatabaseHandler::perform_action(const int& action, Fundraiser* fundraiser, Person* person, Payment* payment)
{
	if (!db) return false;
	string sql;

	bool is_fundraiser = fundraiser && !person && !payment;
	bool is_person = fundraiser && person && !payment;
	bool is_payment = fundraiser && person && payment;

	switch (action)
	{
	case DATABASE_CREATE:
		if (is_fundraiser) {
			sql = SQL::create_fundraiser(fundraiser);
		} else if (is_person) {
			sql = SQL::create_person(person, fundraiser);
		} else if (is_payment) {
			sql = SQL::create_payment(payment, person, fundraiser);
		}

		break;

	case DATABASE_MODIFY:
		if (is_fundraiser) {
			sql = SQL::modify_fundraiser(fundraiser);
		} else if (is_person) {
			sql = SQL::modify_person(person, fundraiser);
		} else if (is_payment) {
			sql = SQL::modify_payment(payment, person, fundraiser);
		}

		break;

	case DATABASE_REMOVE:
		if (is_fundraiser) {
			sql = SQL::remove_fundraiser(fundraiser);
		} else if (is_person) {
			sql = SQL::remove_person(person, fundraiser);
		} else if (is_payment) {
			sql = SQL::remove_payment(payment, person, fundraiser);
		}

		break;

	default:
		cerr << "wrong constant" << endl;
		return false;
	}

	int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
	if (rc) 
	{
		cerr << "Failed command" << endl;
		return false;
	}

	return true;
}


vector<Fundraiser*> DatabaseHandler::get_all_fundraisers()
{
	string id, title, amount, count, end_date;
	string sql = "SELECT * FROM fundraisers;";
	sqlite3_stmt* st = nullptr;
	vector<Fundraiser*> vfund;

	int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
	
	if (rc != SQLITE_OK) return vfund;

	while(true)
	{
		rc = sqlite3_step(st);
		if (rc != SQLITE_ROW) break;

		id = (const char*)sqlite3_column_text(st, 0);
		title = (const char*)sqlite3_column_text(st, 1);
		amount = (const char*)sqlite3_column_text(st, 2);
		count = (const char*)sqlite3_column_text(st, 3);
		end_date = (const char*)sqlite3_column_text(st, 4);

		Fundraiser* fundraiser = new Fundraiser(id, title, amount, count, end_date);
		vfund.push_back(fundraiser);
	}

	sqlite3_finalize(st);

	return vfund;
}

vector<Person*> DatabaseHandler::get_all_persons(Fundraiser* fundraiser)
{
	string id, name, method;
	string sql = "SELECT * FROM persons_";
	sql += fundraiser->id;
	sql += ";";
	sqlite3_stmt* st = nullptr;
	vector<Person*> vperson;

	int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
	if (rc != SQLITE_OK) return vperson;

	while(true)
	{
		rc = sqlite3_step(st);
		if (rc != SQLITE_ROW) break;

		id = (const char*)sqlite3_column_text(st, 0);
		name = (const char*)sqlite3_column_text(st, 1);
		method = (const char*)sqlite3_column_text(st, 2);

		Person* person = new Person(id, name, method);
		vperson.push_back(person);
	}

	sqlite3_finalize(st);

	return vperson;
}

vector<Payment*> DatabaseHandler::get_all_payments(Person* person, Fundraiser* fundraiser)
{
	string id, amount, date;
	string sql = "SELECT * FROM payments_";
	sql += person->id;
	sql += "_";
	sql += fundraiser->id;
	sql += ";";
	sqlite3_stmt* st = nullptr;
	vector<Payment*> vpay;

	int rc = sqlite3_prepare_v3(db, sql.c_str(), sql.size(), 0, &st, nullptr);
	if (rc != SQLITE_OK) return vpay;

	while(true)
	{
		rc = sqlite3_step(st);
		if (rc != SQLITE_ROW) break;

		id = (const char*)sqlite3_column_text(st, 0);
		amount = (const char*)sqlite3_column_text(st, 1);
		date = (const char*)sqlite3_column_text(st, 2);

		Payment* payment = new Payment(id, amount, date);
		vpay.push_back(payment);
	}

	sqlite3_finalize(st);

	return vpay;
}
