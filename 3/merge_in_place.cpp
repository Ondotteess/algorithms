#include <iostream>
#include <vector>
#include <string>

using namespace std;

void merge(vector<int>& array, int left_1, int right_1, int buffer_l, int buffer_r, int left_2, int right_2) { 
    int i = left_1, j = buffer_l, k = left_2;
    while (i <= right_1 && j <= buffer_r) {
        if (array[i] < array[j])  swap(array[i++], array[k]);
        else swap(array[j++], array[k]);
        k++;
    }
    
    while (i <= right_1) swap(array[i++], array[k++]);
    while (j <= buffer_r) swap(array[j++], array[k++]);
}

void merge_sort(vector<int>& array, int left_1, int right_1, int left_2, int right_2) {
    if (right_1 == left_1)  return;
  
    if (array.size() == 2) {
        if (array[0] > array[1]) swap(array[0], array[1]);
        return;
    }

    int mid = (left_1 + right_1) / 2;
    merge_sort(array, left_1, mid, left_2, right_2);
    merge_sort(array, mid + 1, right_1, left_2, right_2);
    merge(array, left_1, mid, mid + 1, right_1, left_2, right_2);
    int i = left_1, j = left_2;
    while (i <= right_1) swap(array[i++], array[j++]);
}

void sort(vector<int>& array, int left, int right, int buffer_l, int buffer_r) {
    if (left > right)  return;
    if (left == right) {
        int tmp = array[0];
        int i = 1;
        while (i < array.size() && tmp > array[i]) {
            array[i - 1] = array[i];
            i++;
        }
        array[i - 1] = tmp;
        return;
    }
    int mid = (left + right) / 2;
    bool fl = (mid - left + 1) > (right - (mid + 1) + 1);
    merge_sort(array, mid + 1, right, left, mid);

    int i = left, j = mid + 1;

    while (j <= right) swap(array[i++], array[j++]);

    if (fl) mid--;

    bool fl2 = (right - (mid + 1) + 1) > (mid - left + 1);
    merge(array, left, mid, buffer_l, buffer_r, mid + 1 + fl2, right);
    sort(array, left, mid + fl, mid + 1 + fl, buffer_r);
}

vector<int> sortArray(vector<int>& array) {
    int l = 0, r = array.size() - 2, buff = array.size() - 1;
    sort(array, l, r, buff, buff);
    return array;
}


int main(){
    vector<int> array2 = { -61698, -32249, 61173, 33772, -75481, 37317, -45253, -24448, 93096, 50610, 41413, 92439, -47067, -99751, -13164 };
    
    sortArray(array2);
    
    for (int x : array2) {
        cout << x << " ";
    }
}
