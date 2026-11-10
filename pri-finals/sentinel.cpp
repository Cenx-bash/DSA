#include <iostream>

using namespace std;

int main(){
        int N,X;
        cin >> N;
        
        int A[101];
        
        for(int i =0; i < N; i++){
            cin >> A[i];
        }
        
        cin >> X;
        
        A[N] = X;
        
        int i = 0;
        int comparisons = 0;
        
        while(true){
            comparisons++;
            
            if(A[i] == X){
                break;
                
            }
            
            i++;
        }
        
        if(i < N){
            cout << "Position: " << i + 1 << endl;
            cout << "Comparisons: " << comparisons;
        }else{
            cout << "NOT FOUND Comparisons: " << endl;
            cout << "Comparisons: " << comparisons;
        }
        return 0;
}

// version 2


#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, X;
    cin >> N;

    vector<int> A(N + 1);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    cin >> X;

    A[N] = X;

    int i = 0;
    int comparisons = 0;

    
    while (A[i] != X) {
        comparisons++;
        i++;
    }

    comparisons++; 

    if (i < N) {
        cout << "Position: " << i + 1 << endl;
        cout << "Comparisons: " << comparisons << endl;
    } else {
        cout << "NOT FOUND" << endl;
        cout << "Comparisons: " << comparisons << endl;
    }

    return 0;
}

