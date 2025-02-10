#include <iostream>
using namespace std;

void insert(int arr[], int &n, int x, int p) {
    if (p > n || p < 0) {
        cout << "Invalid position\n";
        return;
    }
    for (int i = n; i > p; i--)
        arr[i] = arr[i - 1];
    arr[p] = x;
    n++;
}

void search(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            cout << "Element found at index " << i << "\n";
            return;
        }
    }
    cout << "Element not found\n";
}

void deleteElement(int arr[], int &n, int p) {
    if (p >= n || p < 0) {
        cout << "Invalid position\n";
        return;
    }
    for (int i = p; i < n - 1; i++)
        arr[i] = arr[i + 1];
    n--;
}

int main() {
    int arr[100], n = 5;
    arr[0] = 10, arr[1] = 20, arr[2] = 30, arr[3] = 40, arr[4] = 50;

    insert(arr, n, 25, 2); // Insert
    search(arr, n, 25);    // Search
    deleteElement(arr, n, 2); // Delete
    return 0;
}
