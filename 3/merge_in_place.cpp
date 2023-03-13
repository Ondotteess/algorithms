#include <iostream>
#include <vector>

using namespace std;


void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            i++;
        }
        else {
            for (int l = j; l > i; l--) {
                swap(arr[l], arr[l - 1]);
            }
            i++;
            j++;
            mid++;
        }
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printArray(vector<int> arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
    cout << "\n";
}

int main() {
    vector<int> arr = { -2, 3, -5, 6234623, 67345, 4346, -56,73,4,-47,-68,  6,87, 46, 579, 55,21, -35,-4 ,7,45, -4572345 ,-46, 0, 0, 3, 78, -64, -3958, -6, 1, -6, -457 };
    int arr_size = arr.size();

    mergeSort(arr, 0, arr_size - 1);

    printArray(arr, arr_size);
    return 0;
}
