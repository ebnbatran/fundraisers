#include "data_gatherer.h"

DataGatherer::DataGatherer()
{
	// Do nothing
}

DataGatherer::~DataGatherer()
{
	// Do nothing
}

string DataGatherer::get_selection(const int& position, Fundraiser* fundraiser, Person* person, Payment* payment)
{
	string selection, choice;

	switch (position)
	{
	case GATHERER_NONE:
		selection = "Enter your selection: ";
		break;

	case GATHERER_FUNDRAISER:
		selection = fundraiser->title;
		selection += "> Enter your selection: ";
		break;

	case GATHERER_PERSON:
		selection = fundraiser->title;
		selection += "> ";
		selection += person->name;
		selection += "> Enter your selection: ";
		break;

	case GATHERER_PAYMENT:
		selection = fundraiser->title;
		selection += "> ";
		selection += person->name;
		selection += "> ";
		selection += payment->date;
		selection += "> Enter your selection: ";
		break;

	default:
		selection = "";
	}

	cout << selection;
	cin >> choice;

	return choice;
}

bool DataGatherer::confirm_delete()
{
	cout << endl << endl;

	cout << "Are you sure you want to delete this record (y/n)?: ";
	string choice;
	cin >> choice;

	return choice == "y" || choice == "Y";
}

Fundraiser* DataGatherer::get_fundraiser_data()
{
	string id, title, amount, count, end_date;
	char a[100];

	cout << "Enter fundraiser's data: " << endl << endl;

	cout << "ID: "; cin >> id;
	cout << "Title: "; cin.ignore(); cin.getline(a, 100); title = a;
	cout << "Amount: "; cin >> amount;
	cout << "Count of Participants: "; cin >> count;
	cout << "End Date (dd-mm-yyyy): "; cin >> end_date;

	Fundraiser* fundraiser = new Fundraiser(id, title, amount, count, end_date);

	return fundraiser;
}

Person* DataGatherer::get_person_data()
{
	string id, name, method;
	char a[100];

	cout << "Enter person's data: " << endl << endl;

	cout << "ID: "; cin >> id;
	cout << "Name: "; cin.ignore(); cin.getline(a, 100); name = a;
	cout << "Method of Payment: "; cin >> method;

	Person* person = new Person(id, name, method);

	return person;
}

Payment* DataGatherer::get_payment_data()
{
	string id, amount, date;

	cout << "Enter payment's data: " << endl << endl;

	cout << "ID: "; cin >> id;
	cout << "Amount: "; cin >> amount;
	cout << "Date: "; cin >> date;

	Payment* payment = new Payment(id, amount, date);

	return payment;
}
