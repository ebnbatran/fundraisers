#include "gui.h"

GUI::GUI()
{
	// Do nothing
}

GUI::~GUI()
{
	// Do nothing
}

void GUI::welcome()
{
	cout << "Welcome to Fundraisers Money Project C++" << endl;
	cout << "By Ebrahim Batran";
}


void GUI::fundraiser_options()
{
	cout << endl << endl;
	cout << "1) Create New Fundraiser" << endl;
	cout << "2) Select Fundraiser" << endl << endl;
}

void GUI::display_fundraisers(vector<Fundraiser*> fundraisers)
{
	cout << endl << endl;
	cout << "   ";
	cout << setw(NW) << left << "ID"; 
	cout << setw(TW) << left << "TITLE"; 
	cout << setw(NW) << left << "AMOUNT"; 
	cout << setw(NW) << left << "COUNT"; 
	cout << setw(TW) << left << "END DATE"; 
	cout << endl;

	for (int i = 0; i < fundraisers.size(); ++i)
	{
		Fundraiser* current = fundraisers[i];

		cout << i + 1 << ") ";
		cout << setw(NW) << left << current->id;
		cout << setw(TW) << left << current->title;
		cout << setw(NW) << left << current->amount;
		cout << setw(NW) << left << current->count;
		cout << setw(TW) << left << current->end_date << endl;
	}

	cout << endl << endl;
}


void GUI::person_options()
{
	cout << endl << endl;
	cout << "1) Modify Fundraiser" << endl;
	cout << "2) Delete Fundraiser" << endl;
	cout << endl;
	cout << "3) Add New Person" << endl;
	cout << "4) Select Person" << endl;
	cout << endl;
	cout << "5) Back" << endl << endl;
}

void GUI::display_persons(vector<Person*> persons)
{
	cout << endl << endl;
	cout << "   ";
	cout << setw(NW) << left << "ID"; 
	cout << setw(TW) << left << "NAME"; 
	cout << setw(TW) << left << "METHOD OF PAYMENT"; 
	cout << endl;

	for (int i = 0; i < persons.size(); ++i)
	{
		Person* current = persons[i];

		cout << i + 1 << ") ";
		cout << setw(NW) << left << current->id;
		cout << setw(TW) << left << current->name;
		cout << setw(TW) << left << current->method << endl;
	}

	cout << endl << endl;
}


void GUI::payment_options()
{
	cout << endl << endl;
	cout << "1) Modify Person" << endl;
	cout << "2) Delete Person" << endl;
	cout << endl;
	cout << "3) Add New Payment" << endl;
	cout << "4) Select Payment" << endl;
	cout << endl;
	cout << "5) Back" << endl << endl;
}

void GUI::display_payments(vector<Payment*> payments)
{
	cout << endl << endl;
	cout << "   ";
	cout << setw(NW) << left << "ID";
	cout << setw(NW) << left << "AMOUNT"; 
	cout << setw(TW) << left << "DATE"; 
	cout << endl;

	for (int i = 0; i < payments.size(); ++i)
	{
		Payment* current = payments[i];

		cout << i + 1 << ") ";
		cout << setw(NW) << left << current->id;
		cout << setw(NW) << left << current->amount;
		cout << setw(TW) << left << current->date << endl;
	}

	cout << endl << endl;
}

void GUI::payment_details()
{
	cout << endl << endl;
	cout << "1) Modify Payment" << endl;
	cout << "2) Delete Payment" << endl;
	cout << endl;
	cout << "3) Back" << endl << endl;
}

void GUI::error(const int& choice, Fundraiser* fundraiser, Person* person, Payment* payment)
{
	cerr << endl << endl;
	cerr << "## ERROR: Failed to ";

	switch (choice)
	{
	case GUI_CREATE:
		cerr << "create: ";
		break;
	case GUI_MODIFY:
		cerr << "modify: ";
		break;
	case GUI_DELETE:
		cerr << "delete: ";
		break;
	}

	if (fundraiser)
		cerr << fundraiser->title;
	else if (person)
		cerr << person->name;
	else if (payment)
		cerr << "#" << payment->id << " at " << payment->date;

	cerr << " !" << endl;
	cerr << endl << endl;
}
