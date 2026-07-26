#include <iostream>
using namespace std;

int main() {
    void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

}