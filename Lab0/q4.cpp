#include <iostream>
using namespace std;

int fibonacci(int A) {
    if (A <= 1)
        return A;
    return fibonacci(A - 1) + fibonacci(A - 2);
}

int main() {
    int A = 7;
    cout << "Fibonacci Number: " << fibonacci(A) << endl;
    return 0;
}
