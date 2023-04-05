#include <iostream>
#include<vector>

using namespace std;

 bool isIdealPermutation(vector<int>& A) {
        for(int i = 0 ; i < A.size() ; i++){
            if(abs(A[i] - i) > 1)
                return false;
        }
        return true;
    }

int main() {
    vector<int> test_case1{ 1, 0, 2 };
    vector<int> test_case2{ 1, 2, 0 };
    cout << isIdealPermutation(test_case1) << endl; // Output: 1
    cout << isIdealPermutation(test_case2) << endl; // Output: 0
    return 0;
}
