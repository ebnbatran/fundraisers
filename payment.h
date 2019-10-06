#include <string>

using namespace std;

class Payment
{
public:
	string id;
	string amount;
	string date;

public:
	Payment();
	Payment(string, string, string);
	~Payment();
};