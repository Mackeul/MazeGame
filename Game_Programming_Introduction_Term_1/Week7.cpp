#include <iostream>

using namespace std;

int main()
{
	// Part 1.
	int a;
	cout << "Please enter a value for A:";
	cin >> a;

	int b;
	cout << "Please enter a value for B:";
	cin >> b;

	int* ptrA = &a;
	int* ptrB = &b;

	cout << "A:" << a << endl;
	cout << "B:" << b << endl;
	cout << "ptrA:" << *ptrA << endl;
	cout << "ptrB:" << *ptrB << endl;

	//Part 2.
	int numChars;
	cout << "Enter max. number of chars to input:";
	cin >> numChars;
	char* input = new char[numChars];
	cout << "Character variable of size " << numChars << " allocated." << endl;;
	cout << "Please type in some characters now:";
	cin >> input;
	cout << "Value stored in input variable is: ";
	for (int i = 0; i < numChars; i++) {
		cout << input[i];
	}
	cout << endl << "If some of your characters are missing, it is because you typed more than " << numChars << " characters and they could not be stored." << endl;

}

