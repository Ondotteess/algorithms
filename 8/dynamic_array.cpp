#include <iostream>
#include <stdexcept>

using namespace std;

class DynamicArray {
private:
    int size;     
    int capacity; 
    int* arr;     

    void resize_1() {
        capacity *= 2;

        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++)  newArr[i] = arr[i];       

        delete[] arr;
        arr = newArr;
    }

    void resize_2() {
        capacity /= 2;

        int* newArr = new int[capacity];

        for (int i = 0; i < size; i++) newArr[i] = arr[i];

        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray() {
        size = 0;
        capacity = 2;
        arr = new int[capacity];
    }


    void push_back(int value) {
        if (size == capacity) {
            resize_1();
        }

        arr[size++] = value;
    }

    void pop_back() {
        if (size == 0) {
            cout << "Error: Out of bounds!";
            exit(0);
        }
        if (size == (capacity / 4)) {
            resize_2();
        }

        size--;
    }

    int& get_element(int index) {
        if (index < 0 || index >= size) {
            cout << "Error: Out of bounds!";
            exit(0);
        }

        return arr[index];
    }

    int get_size() {
        return size;
    }
    int get_capacity() {
        return capacity;
    }
};

int main() {
    DynamicArray arr;

    for (auto i = 0; i < 1000; i++) arr.push_back(i);
    cout << arr.get_size() << ' ' << arr.get_capacity() << endl;
    for (auto i = 0; i < 950; i++) arr.pop_back();
    cout << arr.get_size() << ' ' << arr.get_capacity() << endl;

    return 0;
}
