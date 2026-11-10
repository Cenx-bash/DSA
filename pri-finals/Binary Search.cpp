#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int x;
    cin >> x;

    int lo = 0, hi = n - 1, comparisons = 0, pos = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        comparisons++;
        if (a[mid] == x) {
            pos = mid + 1;
            break;
        } else if (a[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    if (pos != -1) cout << "Position: " << pos << "\n";
    else cout << "NOT FOUND\n";
    cout << "Comparisons: " << comparisons << "\n";
    return 0;
}
