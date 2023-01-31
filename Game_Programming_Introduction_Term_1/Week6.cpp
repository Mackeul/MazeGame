#include <iostream>

using namespace std;

int Largest(int[], int);

int main()
{
    int test1[] = { 1,2,3,4,5,6 };
    cout << "Test 1 should be 6 and largest is:" << Largest(test1,6) << endl;

    int test2[] = { 45,-1,24,100,87,-108,99,1,87 };
    cout << "Test 2 should be 100 and largest is:" << Largest(test2,9) << endl;

}

int Largest(int anArray[], int arrLength) {

    int largest = anArray[0];

    for (int i = 1; i < arrLength; i++) {
        if (anArray[i] > largest) {
            largest = anArray[i];
        }
    }

    return largest;
}
