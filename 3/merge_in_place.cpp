#include <iostream>
using namespace std;

void merge(int arr[], int start, int mid, int end) {
    int start2 = mid + 1;
    if (arr[mid] <= arr[start2]) {
        return;
    }
    while (start <= mid && start2 <= end) {
        if (arr[start] <= arr[start2]) {
            start++;
        } else {
            int value = arr[start2];
            int index = start2;

            while (index != start) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;
            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << A[i];
    cout << "\n";
}

int main() {
    int arr[] = { -2, 3, -5, 6234623, 67345, 4346, -56,73,4,-47,-68,  6,87, 46, 579, 55,21, -35,-4 ,7,45, -4572345 ,-46, 0, 0, 3, 78, -64, -3958, -6, 1, -6, -457 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, arr_size - 1);

    printArray(arr, arr_size);
    return 0;
}
