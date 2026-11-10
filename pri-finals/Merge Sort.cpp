#include <iostream>
#include <vector>
using namespace std;

int comparisons = 0, movements = 0;

void mergeSort(vector<int>& a, int l, int r) { // sorts [l, r)
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m, r);

    vector<int> tmp;
    int i = l, j = m;
    while (i < m && j < r) {
        comparisons++;
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else tmp.push_back(a[j++]);
        movements++;
    }
    while (i < m) { tmp.push_back(a[i++]); movements++; }
    while (j < r) { tmp.push_back(a[j++]); movements++; }
    for (int k = 0; k < (int)tmp.size(); k++) a[l + k] = tmp[k];
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    mergeSort(a, 0, n);

    cout << "Sorted:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    cout << "Comparisons: " << comparisons << "\n";
    cout << "Movements: " << movements << "\n";
    return 0;
}
