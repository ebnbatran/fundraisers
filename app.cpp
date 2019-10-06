#include "gui.h"


// Current Objects
vector<Fundraiser*> fundraisers;
Fundraiser* current_fundraiser = nullptr;

vector<Person*> persons;
Person* current_person = nullptr;

vector<Payment*> payments;
Payment* current_payment = nullptr;

// Current UI
bool fundraiser_ui = true;
bool person_ui = false;
bool payment_ui = false;
bool payment_detail_ui = false;


int main(int argc, char const *argv[])
{
	// Variables
	string choice;
	DatabaseHandler* db_handler = new DatabaseHandler("fundraisers.sqlite");

	// Welcome
	GUI::welcome();

	// Choose between UIs
	while (true)
	{
		if (fundraiser_ui)
		{
			// 1. Fundraiser options
			GUI::fundraiser_options();

			// Ask for selection
			choice = DataGatherer::get_selection(GATHERER_NONE);

			// Choose
			if (choice == "1")
			{
				// 1. Create fundraiser

				// Gather data
				current_fundraiser = DataGatherer::get_fundraiser_data();

				// Save to database
				bool success = db_handler->perform_action(DATABASE_CREATE,
					current_fundraiser);

				if (!success)
				{
					GUI::error(GUI_CREATE, current_fundraiser);
					continue;
				}

			} else if (choice == "2") {
				// 2. Select fundraiser
				fundraisers = db_handler->get_all_fundraisers();
				if (fundraisers.size() == 0) continue;

				GUI::display_fundraisers(fundraisers);

				// Ask for choice
				choice = DataGatherer::get_selection(GATHERER_NONE);

				// Set current fundraiser object
				int index = stoi(choice) - 1;
				current_fundraiser = fundraisers[index];

				// Switch to Persons UI
				fundraiser_ui = false;
				person_ui = true;

			} else {
				break;
			}


		} else if (person_ui) {
			// 2. Persons options
			GUI::person_options();

			// Ask for selection
			choice = DataGatherer::get_selection(GATHERER_FUNDRAISER,
				current_fundraiser);

			// Choose
			if (choice == "1")
			{
				// 1. Modify current fundraiser

				// Gather data
				current_fundraiser = DataGatherer::get_fundraiser_data();

				// Save to database
				bool success = db_handler->perform_action(DATABASE_MODIFY,
					current_fundraiser);

				if (!success)
				{
					GUI::error(GUI_MODIFY, current_fundraiser);
					continue;
				}

			} else if (choice == "2") {
				// 2. Delete current fundraiser

				// Confirm
				bool yes = DataGatherer::confirm_delete();

				// Delete from database and from current variables
				if (yes)
				{
					bool success = db_handler->perform_action(
						DATABASE_REMOVE, current_fundraiser);

					if (!success)
					{
						GUI::error(GUI_DELETE, current_fundraiser);
						continue;
					}

					for (int i = 0; i < fundraisers.size(); ++i)
					{
						if (fundraisers[i]->id == current_fundraiser->id)
						{
							fundraisers.erase(fundraisers.begin() + i);
							break;
						}
					}

					current_fundraiser = nullptr;

					// switch back to fundraisers UI
					fundraiser_ui = true;
					person_ui = false;
				}

				continue;

			} else if (choice == "3") {
				// 3. Create person

				// Gather data
				current_person = DataGatherer::get_person_data();

				// Save to database
				bool success = db_handler->perform_action(
					DATABASE_CREATE, current_fundraiser, current_person);

				if (!success)
				{
					GUI::error(GUI_CREATE, nullptr, current_person);
					continue;
				}

			} else if (choice == "4") {
				// 4. Select person
				persons = db_handler->get_all_persons(current_fundraiser);
				if (persons.size() == 0) continue;

				GUI::display_persons(persons);

				// Ask for choice
				choice = DataGatherer::get_selection(GATHERER_FUNDRAISER,
					current_fundraiser);

				// Switch to Payments UI
				int index = stoi(choice) - 1;
				current_person = persons[index];
				person_ui = false;
				payment_ui = true;

				continue;

			} else if (choice == "5") {
				fundraiser_ui = true;
				person_ui = false;

			} else {
				break;
			}

		} else if (payment_ui) {
			// 3. Payments options
			GUI::payment_options();

			// Ask for selection
			choice = DataGatherer::get_selection(GATHERER_PERSON,
				current_fundraiser, current_person);

			// Choose
			if (choice == "1")
			{
				// 1. Modify Person

				// Gather data
				current_person = DataGatherer::get_person_data();

				// Save to database
				bool success = db_handler->perform_action(DATABASE_MODIFY,
					current_fundraiser, current_person);

				if (!success)
				{
					GUI::error(GUI_MODIFY, nullptr, current_person);
					continue;
				}

			} else if (choice == "2") {
				// 2. Delete Person

				// Confirm
				bool yes = DataGatherer::confirm_delete();

				// Delete from database
				if (yes)
				{
					bool success = db_handler->perform_action(DATABASE_REMOVE,
						current_fundraiser, current_person);

					if (!success)
					{
						GUI::error(GUI_DELETE, nullptr, current_person);
						continue;
					}

					for (int i = 0; i < persons.size(); ++i)
					{
						if (persons[i]->id == current_person->id)
						{
							persons.erase(persons.begin() + i);
							break;
						}
					}

					current_person = nullptr;

					// switch back to persons UI
					person_ui = true;
					payment_ui = false;

					continue;
				}

			} else if (choice == "3") {
				// 3. Create Payment

				// Gather data
				current_payment = DataGatherer::get_payment_data();

				// Save to database
				bool success = db_handler->perform_action(DATABASE_CREATE,
					current_fundraiser, current_person, current_payment);

				if (!success)
				{
					GUI::error(GUI_CREATE, nullptr, nullptr, current_payment);
					continue;
				}

			} else if (choice == "4") {
				// 4. Select Payment
				payments = db_handler->get_all_payments(current_person,
					current_fundraiser);
				if (payments.size() == 0) continue;

				GUI::display_payments(payments);

				// Ask for choice
				choice = DataGatherer::get_selection(GATHERER_PERSON,
					current_fundraiser, current_person);

				// create current payment object
				int index = stoi(choice) - 1;
				current_payment = payments[index];

				// Switch for Payment Choices UI
				payment_ui = false;
				payment_detail_ui = true;

			} else if (choice == "5") {
				person_ui = true;
				payment_ui = false;

			} else {
				break;
			}

		} else if (payment_detail_ui) {
			// 4. Payments detail options
			GUI::payment_details();

			// Ask for selection
			choice = DataGatherer::get_selection(GATHERER_PAYMENT,
				current_fundraiser, current_person, current_payment);

			// Choose
			if (choice == "1")
			{
				// 1. Modify Payment

				// Gather data
				current_payment = DataGatherer::get_payment_data();

				// Save to database
				bool success = db_handler->perform_action(DATABASE_MODIFY,
					current_fundraiser, current_person, current_payment);

				if (!success)
				{
					GUI::error(GUI_MODIFY, nullptr, nullptr, current_payment);
					continue;
				}

			} else if (choice == "2") {
				// 2. Delete Payment

				// Confirm
				bool yes = DataGatherer::confirm_delete();

				// Delete from database
				if (yes)
				{
					bool success = db_handler->perform_action(
						DATABASE_REMOVE, current_fundraiser,
						current_person, current_payment);

					if (!success)
					{
						GUI::error(GUI_DELETE, nullptr, nullptr, current_payment);
						continue;
					}

					for (int i = 0; i < payments.size(); ++i)
					{
						if (payments[i]->id == current_payment->id)
						{
							payments.erase(payments.begin() + i);
							break;
						}
					}

					current_payment = nullptr;

					// switch back to persons UI
					payment_ui = true;
					payment_detail_ui = false;

					continue;
				}

			} else if (choice == "3") {
				payment_ui = true;
				payment_detail_ui = false;

			} else {
				break;
			}
		}
	}

	delete db_handler;

	return 0;
}
