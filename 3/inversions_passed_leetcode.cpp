#include <iostream>
#include<vector>

using namespace std;

bool check_sequence(vector<int> A) {
    int i = 0;
    while (i < A.size() - 1) {
        if (A[i] > A[i + 1]) {
            if (((i == 0) || (A[i - 1] < A[i])) && ((A[i] != i + 1) || (A[i + 1] != A[i] - 1))) {
                return false;
            }
            i++;
        }
        i++;
    }
    return true;
}

int main() {
    vector<int> test_case1{ 1, 0, 2 };
    vector<int> test_case2{ 1, 2, 0 };
    cout << check_sequence(test_case1) << endl; // Output: 1
    cout << check_sequence(test_case2) << endl; // Output: 0
    return 0;
}
