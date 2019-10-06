#include "sql.h"

string SQL::create_fundraiser_main_table()
{
	string script = "CREATE TABLE fundraisers (";
	script += "ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
	script += "Title TEXT NOT NULL, ";
	script += "Amount TEXT NOT NULL, ";
	script += "Count TEXT NOT NULL, ";
	script += "End_Date TEXT NOT NULL);";

	return script;
}

string SQL::create_fundraiser(Fundraiser* fundraiser)
{
	string script = "INSERT INTO fundraisers VALUES('";
	script += fundraiser->id;
	script += "', '";
	script += fundraiser->title;
	script += "', '";
	script += fundraiser->amount;
	script += "', '";
	script += fundraiser->count;
	script += "', '";
	script += fundraiser->end_date;
	script += "'); ";


	script += "CREATE TABLE persons_";
	script += fundraiser->id;
	script += "(ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
	script += "Name TEXT NOT NULL, ";
	script += "Method TEXT NOT NULL);";

	return script;
}

string SQL::modify_fundraiser(Fundraiser* fundraiser)
{
	string script = "UPDATE fundraisers SET ";
	script += "Title = '";
	script += fundraiser->title;
	script += "', Amount = '";
	script += fundraiser->amount;
	script += "', Count = '";
	script += fundraiser->count;
	script += "', End_Date = '";
	script += fundraiser->end_date;
	script += "' WHERE ID = '";
	script += fundraiser->id;
	script += "';";

	return script;
}

string SQL::remove_fundraiser(Fundraiser* fundraiser)
{
	string script = "DELETE FROM fundraisers WHERE ID = '";
	script += fundraiser->id;
	script += "'; ";

	script += "DROP TABLE persons_";
	script += fundraiser->id;
	script += "; ";

	return script;
}


string SQL::create_person(Person* person, Fundraiser* fundraiser)
{
	string script = "INSERT INTO persons_";
	script += fundraiser->id;
	script += " VALUES('";
	script += person->id;
	script += "', '";
	script += person->name;
	script += "', '";
	script += person->method;
	script += "'); ";

	script += "CREATE TABLE payments_";
	script += person->id;
	script += "_";
	script += fundraiser->id;
	script += "(ID TEXT PRIMARY KEY NOT NULL UNIQUE, ";
	script += "Amount TEXT NOT NULL, ";
	script += "Date TEXT NOT NULL);";

	return script;
}

string SQL::modify_person(Person* person, Fundraiser* fundraiser)
{
	string script = "UPDATE persons_";
	script += fundraiser->id;
	script += " SET Name = '";
	script += person->name;
	script += "', Method = '";
	script += person->method;
	script += "' WHERE ID = '";
	script += person->id;
	script += "';";

	return script;
}

string SQL::remove_person(Person* person, Fundraiser* fundraiser)
{
	string script = "DELETE FROM persons_";
	script += fundraiser->id;
	script += " WHERE ID = '";
	script += person->id;
	script += "'; ";

	script += "DROP TABLE payments_";
	script += person->id;
	script += "_";
	script += fundraiser->id;
	script += ";";

	return script;
}



string SQL::create_payment(Payment* payment, Person* person, Fundraiser* fundraiser)
{
	string script = "INSERT INTO payments_";
	script += person->id;
	script += "_";
	script += fundraiser->id;
	script += " VALUES('";
	script += payment->id;
	script += "', '";
	script += payment->amount;
	script += "', '";
	script += payment->date;
	script += "');";

	return script;
}

string SQL::modify_payment(Payment* payment, Person* person, Fundraiser* fundraiser)
{
	string script = "UPDATE payments_";
	script += person->id;
	script += "_";
	script += fundraiser->id;
	script += " SET Amount = '";
	script += payment->amount;
	script += "', Date = '";
	script += payment->date;
	script += "' WHERE ID = '";
	script += payment->id;
	script += "';";

	return script;
}

string SQL::remove_payment(Payment* payment, Person* person, Fundraiser* fundraiser)
{
	string script = "DELETE FROM payments_";
	script += person->id;
	script += "_";
	script += fundraiser->id;
	script += " WHERE ID = '";
	script += payment->id;
	script += "';";

	return script;
}
