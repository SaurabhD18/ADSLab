#include <iostream>
using namespace std;

int sumOfDigits(int A) {
    if (A == 0)
        return 0;
    return (A % 10) + sumOfDigits(A / 10);
}

int main() {
    int A = 46;
    cout << "Sum of digits: " << sumOfDigits(A) << endl;
    return 0;
}
