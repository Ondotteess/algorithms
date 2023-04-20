#include <iostream>
#include <cstdlib>

using namespace std;

class binary_heap {
private:
    int size;
    int capacity;
    int* arr;

    void increase() {
        capacity *= 2;

        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++)  newArr[i] = arr[i];

        delete[] arr;
        arr = newArr;
    }

    void shrink() {
        capacity /= 2;

        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++) newArr[i] = arr[i];

        delete[] arr;
        arr = newArr;
    }

public:
    binary_heap() {
        size = 0;
        capacity = 2;
        arr = new int[capacity];
    }

    void insert(int a) {
        if (size == capacity) increase();
        arr[size++] = a;
        shift();
    }

    int peek_max() {
        return arr[0];
    }

    int extract_max() {
        swap(arr[0], arr[--size]);
        shift();
        return (arr[size + 1]);
    }

    void print_heap() {
        for (auto i = 0; i < size; i++) cout << arr[i] << " ";
    }

    void shift() {
        int i = size - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && arr[parent] < arr[i]) {
            swap(arr[parent], arr[i]);
            i = parent;
            parent = (i - 1) / 2;
        }

    }

    bool check() {
        int i = 0;

        while ((2 * i + 2) < size) {
            if (!(arr[2 * i + 1] <= arr[i])) return false;
            if (!(arr[2 * i + 2] <= arr[i])) return false;
            i++;
        }
        return true;

    }

    int get_size() {
        return size;
    }

};

int main() {
    binary_heap heap;

    for (int i = 0; i < 100000; i++) {
        heap.insert(rand() % 1000);
    }

    //for (int i = 0; i < 5000; i++) {
       auto n = heap.extract_max();
    //}

    cout << heap.check();

}
