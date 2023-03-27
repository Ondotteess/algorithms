#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <vector>

using namespace std;

long* lomuto_partition_branchfree(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first; 
    --last;
    if (*first > *last)
        swap(*first, *last);
    auto pivot_pos = first;
    auto pivot = *first;
    do {
        ++first;
        assert(first <= last);
    } while (*first < pivot);
    for (auto read = first + 1; read < last; ++read) {
        auto x = *read;
        auto smaller = -int(x < pivot);
        auto delta = smaller & (read - first);
        first[delta] = *first;
        read[-delta] = x;
        first -= smaller;
    }
    assert(*first >= pivot);
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}

long* hoare_partition(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first; // nothing interesting to do
    --last;
    if (*first > *last)
        swap(*first, *last);
    auto pivot_pos = first;
    auto pivot = *pivot_pos;
    for (;;) {
        ++first;
        auto f = *first;
        while (f < pivot)
            f = *++first;
        auto l = *last;
        while (pivot < l)
            l = *--last;
        if (first >= last)
            break;
        *first = l;
        *last = f;
        --last;
    }
    --first;
    swap(*first, *pivot_pos);
    return first;
}

long* lomuto_partition(long* first, long* last) {
    assert(first <= last);
    if (last - first < 2)
        return first; 
    --last;
    if (*first > *last)
        swap(*first, *last);
    auto pivot_pos = first;
    auto pivot = *first;
    do {
        ++first;
    } while (*first < pivot);
    assert(first <= last);
    for (auto read = first + 1; read < last; ++read) {
        auto x = *read;
        if (x < pivot) {
            *read = *first;
            *first = x;
            ++first;
        }
    }
    assert(*first >= pivot);
    --first;
    *pivot_pos = *first;
    *first = pivot;
    return first;
}


void quicksort_lomuto_branchfree(long* first, long* last) {
    if (last - first < 2)
        return;
    auto pivot_pos = hoare_partition(first, last);
    quicksort_lomuto_branchfree(first, pivot_pos);
    quicksort_lomuto_branchfree(pivot_pos + 1, last);
}

void quicksort_hoare(long* first, long* last) {
    if (last - first < 2)
        return;
    auto pivot_pos = hoare_partition(first, last);
    quicksort_hoare(first, pivot_pos + 1);
    quicksort_hoare(pivot_pos + 1, last);
}

void quicksort_lomuto(long* first, long* last) {
    if (last - first < 2) {
        return;
    }
    auto pivot_pos = lomuto_partition(first, last);
    quicksort_lomuto(first, pivot_pos);
    quicksort_lomuto(pivot_pos + 1, last);
}


void generate_random_array(long arr[], size_t size, int min_val, int max_val) {
    srand(time(nullptr));
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % (max_val - min_val + 1) + min_val; 
    }
}


int main() {
    
    const size_t array_size = 10000;
    long array_1[array_size];
    long array_2[array_size];
    long array_3[array_size];

    generate_random_array(array_1, array_size, 0, 1000);
    generate_random_array(array_2, array_size, 0, 1000);
    generate_random_array(array_3, array_size, 0, 1000);

    
    clock_t start_time_1 = clock();
    quicksort_lomuto(begin(array_1), end(array_1));
    clock_t end_time_1 = clock(); 
    double elapsed_time_1 = double(end_time_1 - start_time_1) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed_time_1 << " seconds." << endl;

    clock_t start_time_2 = clock();
    quicksort_lomuto(begin(array_1), end(array_1));
    clock_t end_time_2 = clock();
    double elapsed_time_2 = double(end_time_2 - start_time_2) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed_time_2 << " seconds." << endl;
    
    clock_t start_time_3 = clock();
    quicksort_lomuto(begin(array_1), end(array_1));
    clock_t end_time_3 = clock(); 
    double elapsed_time_3 = double(end_time_3 - start_time_3) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed_time_3 << " seconds." << endl;




}
