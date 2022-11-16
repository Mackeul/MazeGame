
#include <iostream>

using namespace std;

int Power(int, int);

int main()
{
	int number;
	int exp=3;

	cout << "Enter a number to calculate its value cubed:";
	cin >> number;

	cout << number << " to the power of " << exp << " is: " << Power(number, exp) << endl;
}

int Power(int base, int exponent) {

	if (exponent == 1)
		return base;

	if (exponent == 0)
		return 1;

	return base * Power(base, exponent - 1);
}