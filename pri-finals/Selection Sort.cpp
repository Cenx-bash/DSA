#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int comparisons = 0, swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(a[i], a[minIdx]);
            swaps++;
        }
    }

    cout << "Sorted:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    cout << "Comparisons: " << comparisons << "\n";
    cout << "Swaps: " << swaps << "\n";
    return 0;
}
