#include <iostream>
#include <vector>
#include <string>

using namespace std;


void merge(vector<int>& array, int left_1, int right_1, int left_2, int right_2, int buffer_l, int buffer_r) {
    int i = left_1, j = left_2, k = buffer_l;
    while (i <= right_1 && j <= right_2) {
        if (array[i] < array[j])  swap(array[i++], array[k]);
        else swap(array[j++], array[k]);
        k++;
    }

    while (i <= right_1 ) swap(array[i++], array[k++]);
    while (j <= right_2 ) swap(array[j++], array[k++]);
}

void merge_sort(vector<int>& array, int left, int right, int buffer_l, int buffer_r) {
    if (right == left)  return;

    if (array.size() == 2) {
        if (array[0] > array[1]) swap(array[0], array[1]);
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(array, left, mid, buffer_l, buffer_r);
    merge_sort(array, mid + 1, right, buffer_l, buffer_r);
    merge(array, left, mid, mid + 1, right, buffer_l, buffer_r);

    int i = left, j = buffer_l;                                     //  swap buffer and [left, mid] after merge
    while (i <= right) swap(array[i++], array[j++]);                                                                                
} 

void sort(vector<int>& array, int left, int right, int buffer_l, int buffer_r) {
    if (left > right)  return;                              //  sorted

    if (left == right) {                                    //  sorted [1, -1]
        int tmp = array[0];                                 //  put array[0] in right position
        int i = 1;
        while (i < array.size() && tmp > array[i]) {
            array[i - 1] = array[i];
            i++;
        }
        array[i - 1] = tmp;
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(array, mid + 1, right, left, mid);           //  sort   [mid+1, right] 
                                                            //  buffer [left,    mid]
    int i = left, j = mid + 1;

    while (j <= right) swap(array[i++], array[j++]);        //  swap  [left, mid] , [mid + 1, right]

    bool left_greater = (mid - left + 1) > (right - (mid + 1) + 1);
    if (left_greater) mid--;                                //  if len([left, mid]) > len([mid + 1, right]) : mid--

    bool right_greater = (right - (mid + 1) + 1) > (mid - left + 1);
    merge(array, left, mid, buffer_l, buffer_r, mid + 1 + right_greater, right);  //  merge sorted [left, mid] and [buffer_l, buffer_r] 
                                                                                  //  use [mid + 1 + right_greater] as buffer
    sort(array, left, mid + left_greater, mid + 1 + left_greater, buffer_r);      //  recursion  [left, mid + left_greater]         as array
                                                                                  //             [mid + 1 + left_greater, buffer_r] as buffer
}

vector<int> sortArray(vector<int>& array) {
    int l = 0, r = array.size() - 2, buff = array.size() - 1;       //  buffer: array[-1]
    sort(array, l, r, buff, buff);                                  
    return array;
}


void generate_random_vector(vector<int>& vec, int max, int min) {
    srand(time(NULL));
    for (auto i = 0; i < vec.size(); i++) vec[i] = (rand() % max) + min;
  
}

bool is_correct_sort(vector<int>& vec) {
    for (auto i = 0; i < vec.size() - 2; i++) if (vec[i] > vec[i + 1]) return false;
    return true;

}

int main() {

    const size_t array_size = 100000;
    const int max =  200000;
    const int min = -100000;

    vector<int> array(array_size);
    generate_random_vector(array, max, min);

    cout << is_correct_sort(array) << endl;
    sortArray(array);
    cout << is_correct_sort(array) << endl;



    //for (int x : array) {
    //    cout << x << ' ';
    //}

}#include <iostream>
#include <vector>
#include <string>

using namespace std;


void merge(vector<int>& array, int left_1, int right_1, int left_2, int right_2, int buffer_l, int buffer_r) {
    int i = left_1, j = left_2, k = buffer_l;
    while (i <= right_1 && j <= right_2) {
        if (array[i] < array[j])  swap(array[i++], array[k]);
        else swap(array[j++], array[k]);
        k++;
    }

    while (i <= right_1 ) swap(array[i++], array[k++]);
    while (j <= right_2 ) swap(array[j++], array[k++]);
}

void merge_sort(vector<int>& array, int left, int right, int buffer_l, int buffer_r) {
    if (right == left)  return;

    if (array.size() == 2) {
        if (array[0] > array[1]) swap(array[0], array[1]);
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(array, left, mid, buffer_l, buffer_r);
    merge_sort(array, mid + 1, right, buffer_l, buffer_r);
    merge(array, left, mid, mid + 1, right, buffer_l, buffer_r);

    int i = left, j = buffer_l;                                     //  swap buffer and [left, mid] after merge
    while (i <= right) swap(array[i++], array[j++]);                                                                                
} 

void sort(vector<int>& array, int left, int right, int buffer_l, int buffer_r) {
    if (left > right)  return;                              //  sorted

    if (left == right) {                                    //  sorted [1, -1]
        int tmp = array[0];                                 //  put array[0] in right position
        int i = 1;
        while (i < array.size() && tmp > array[i]) {
            array[i - 1] = array[i];
            i++;
        }
        array[i - 1] = tmp;
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(array, mid + 1, right, left, mid);           //  sort   [mid+1, right] 
                                                            //  buffer [left,    mid]
    int i = left, j = mid + 1;

    while (j <= right) swap(array[i++], array[j++]);        //  swap  [left, mid] , [mid + 1, right]

    bool left_greater = (mid - left + 1) > (right - (mid + 1) + 1);
    if (left_greater) mid--;                                //  if len([left, mid]) > len([mid + 1, right]) : mid--

    bool right_greater = (right - (mid + 1) + 1) > (mid - left + 1);
    merge(array, left, mid, buffer_l, buffer_r, mid + 1 + right_greater, right);  //  merge sorted [left, mid] and [buffer_l, buffer_r] 
                                                                                  //  use [mid + 1 + right_greater] as buffer
    sort(array, left, mid + left_greater, mid + 1 + left_greater, buffer_r);      //  recursion  [left, mid + left_greater]         as array
                                                                                  //             [mid + 1 + left_greater, buffer_r] as buffer
}

vector<int> sortArray(vector<int>& array) {
    int l = 0, r = array.size() - 2, buff = array.size() - 1;       //  buffer: array[-1]
    sort(array, l, r, buff, buff);                                  
    return array;
}


void generate_random_vector(vector<int>& vec, int max, int min) {
    srand(time(NULL));
    for (auto i = 0; i < vec.size(); i++) vec[i] = (rand() % max) + min;
  
}

bool is_correct_sort(vector<int>& vec) {
    for (auto i = 0; i < vec.size() - 2; i++) if (vec[i] > vec[i + 1]) return false;
    return true;

}

int main() {

    const size_t array_size = 100000;
    const int max =  200000;
    const int min = -100000;

    vector<int> array(array_size);
    generate_random_vector(array, max, min);

    cout << is_correct_sort(array) << endl;
    sortArray(array);
    cout << is_correct_sort(array) << endl;



    //for (int x : array) {
    //    cout << x << ' ';
    //}

}
