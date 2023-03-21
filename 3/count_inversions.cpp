#include <iostream>
#include <vector>

using namespace std;

int local = 0;
int global = 0;


void merge(int left_1, int right_1, int left_2, int right_2, int result, vector<int>& array, int buffer[]) {

    int i = 0;
    int len_array = right_1 - left_1 + right_2 - left_2 + 2;

    while (left_1 <= right_1 && left_2 <= right_2) {
        if (array[left_1] <= array[left_2]) {
            buffer[i] = array[left_1++];
        }
        else {
            global += right_1 - left_1 + 1;
            buffer[i] = array[left_2++];
        }
        i++;
    }

    while (left_1 <= right_1) buffer[i++] = array[left_1++];

    while (left_2 <= right_2) buffer[i++] = array[left_2++];

    for (i = 0; i < len_array; i++) array[result + i] = buffer[i];
   
}

void merge_sort(int left, int right, vector<int>& array) {
    if (right - left == 0) return;
    
    else if (right - left == 1) {
        if (array[right] < array[left]) {
            swap(array[right], array[left]);
            global++;
            local++;
        }
        return;
    }

    int mid = (right + left) / 2;

    if (array[mid] > array[mid + 1]) local += 1;


    merge_sort(left, mid, array);
    merge_sort(mid + 1, right, array);

    int* buffer = new int[array.size()];
    merge(left, mid, mid + 1, right, left, array, buffer);
}


bool isIdealPermutation(vector<int>& nums) {
    if (nums.size() == 1) {
        return true;
    }

    merge_sort(0, nums.size() - 1, nums);

    return (global == local);
}
int main() {

    vector<int> array = { 1, 2, 4, 3, 5, 6, 7, 9, 8 };

    cout << isIdealPermutation(array);

}
