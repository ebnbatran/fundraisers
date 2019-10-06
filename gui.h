#include "data_gatherer.h"

#define GUI_CREATE 0
#define GUI_MODIFY 1
#define GUI_DELETE 2

#define TW 20
#define NW 10

class GUI
{
public:
	GUI();
	~GUI();

	static void welcome();

	static void fundraiser_options();
	static void display_fundraisers(vector<Fundraiser*>);

	static void person_options();
	static void display_persons(vector<Person*>);

	static void payment_options();
	static void display_payments(vector<Payment*>);
	static void payment_details();

	static void error(const int&, Fundraiser* = nullptr, Person* = nullptr,
		Payment* = nullptr);

private:
	static constexpr int FIELD_WIDTH = 15;
};
