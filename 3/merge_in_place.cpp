#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> arr, int idx_left, int size_left, int idx_right, int size_right, int idx_res) {
    int i = 0, j = 0, k = 0;
    while ((i < size_left) && (j < size_right)) {
        if (arr[idx_left + i] <= arr[idx_right + j]) { swap(arr[idx_res + k], arr[idx_left + i]); k++; i++; }
        else { swap(arr[idx_res + k], arr[idx_right + j]); k++; j++; }
    
    
    }  
    while (i < size_left) { swap(arr[idx_res + k], arr[idx_left + i]); k++; i++; }
    while (j < size_right) { swap(arr[idx_res + k], arr[idx_right + j]); k++; j++; }
    return;
}

void merge_sort_in_place(vector<int> arr, int idx_left, int len, int idx_buffer) {
    if (len == 1) return;
    int middle = len / 2;
    
    merge_sort_in_place(arr, idx_left, middle, idx_buffer);
    merge_sort_in_place(arr, idx_left + middle, len - middle, idx_buffer);
    
    merge(arr, idx_left, middle, idx_left + middle ,len - middle, idx_buffer);

    for (int i = 0; i < len; i++) swap(arr[i], arr[idx_buffer + i]);
}

vector<int> sort_array(vector<int> arr, int idx_left, int len) {
    int unsorted = len / 2;
    merge_sort_in_place(arr, idx_left + unsorted, len - unsorted, idx_left);
    while (unsorted != 1) {
        int middle = unsorted / 2;
        merge_sort_in_place(arr, idx_left, middle, idx_left + middle);
        merge(arr, idx_left, middle, idx_left + unsorted, len - unsorted, idx_left + middle);
        unsorted = middle;
    }
    for (int i = 0; (arr[i] > arr[i + 1] && i + 1 < len); swap(arr[i++], arr[i]));

    return arr;
}

int main() {
    vector<int> arr = { 8656, 7630, -8776, 8730, -3234, -4692, 8018, -6175 };
    cout << "Original array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    arr = sort_array(arr, 0, arr.size());

    cout << "Sorted array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

  
    return 0;
}
