#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swaps++;
            }
        }
    }

    cout << "Sorted:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    cout << "Swaps: " << swaps << "\n";
    return 0;
}
