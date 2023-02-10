#include <iostream>

using namespace std;

int main() {

	cout << "This program will find all factors of a number." << endl;

	cout << "Please enter a number:";
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		if (n % i == 0) {
			cout << i << " is a factor of " << n << "." << endl;
		}
	}
}