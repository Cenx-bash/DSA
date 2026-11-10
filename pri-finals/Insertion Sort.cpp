#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int moves = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            moves++;
            j--;
        }
        a[j + 1] = key;
    }

    cout << "Sorted:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    cout << "Movements: " << moves << "\n";
    return 0;
}
