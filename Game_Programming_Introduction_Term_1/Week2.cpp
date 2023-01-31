#include <iostream>

using namespace std;

int main()
{
	int num1;
	int num2;
	int num3;


	cout << "This program will find the sum and the average of 3 numbers that you input." << endl;

	cout << "Please enter the first number:";
	cin >> num1;

	cout << "Now enter the second number:";
	cin >> num2;

	cout << "Finall, the third number please:";
	cin >> num3;

	int sum = num1 + num2 + num3;
	int avg = sum / 3;

	cout << "The sum of all three numbers is: " << sum << endl;

	cout << "The average of all three numbers is: " << avg << endl;

}
