
#include <iostream>

using namespace std;

int main()
{
    int year;

    cout << "Leap year calculator.  Enter the current year to see if it is a leap year." << endl;
    cout << "Year:";
    cin >> year;

    // Rules for leap year:
    // Year divisible by 4, except if divisible by 100 unless divisible by 400.

    bool leapYear = false;

    if (year % 4 == 0) {
        cout << "Year is divisible by 4." << endl;
        if (year % 100 == 0) {
            cout << "Year is divisible by 100." << endl;
            if (year % 400 == 0) {
                cout << "Year is divisible by 400." << endl;
                leapYear = true;
            }
            else {
                cout << "Year is NOT divisible by 400." << endl;
            }
        }
        else {
            cout << "Year is NOT divisible by 100." << endl;
            leapYear = true;
        }
    }
    else {
        cout << "Year is NOT divisible by 4." << endl;
    }

    cout << "Therefore, ";
    if (leapYear)
        cout << year << " IS a leap year." << endl;
    else
        cout << year << " is NOT a leap year." << endl;

}

