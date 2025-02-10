#include <iostream>
using namespace std;

int findSmallestMissing(int arr[], int start, int end) {
    if (start > end)
        return start;

    int mid = (start + end) / 2;
    if (arr[mid] == mid)
        return findSmallestMissing(arr, mid + 1, end);
    else
        return findSmallestMissing(arr, start, mid - 1);
}

int main() {
    int arr[] = {0, 1, 2, 3, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Smallest Missing Number: " << findSmallestMissing(arr, 0, n - 1) << endl;
    return 0;
}
