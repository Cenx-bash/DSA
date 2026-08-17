#include <iostream>
#include <vector>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int r, c;
    cin >> r >> c;

    vector<vector<int>> matrixA(r, vector<int>(c));
    vector<vector<int>> matrixB(r, vector<int>(c));
    vector<vector<int>> matrixSum(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> matrixA[i][j];
        }
        for (int j = 0; j < c; j++) {
            cin >> matrixB[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrixSum[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << matrixSum[i][j];
            if (j < c - 1) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}

