#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void quicksort(vector<int>& arr, int left, int right) {
    int i = left;
    int j = right;
    int pivot = arr[left + rand() % (right - left + 1)];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        
        while (arr[j] > pivot) j--;
       
        if (i <= j) swap(arr[i++], arr[j--]);
        
    }

    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}


int main() {
 
   vector<int> arr = { -61698, -32249, 61173, 33772, -75481, 37317, -45253, -24448, 93096, 50610, 41413, 92439, -47067, -99751, -13164 };
   
   quicksort(arr, 0, arr.size() - 1);

   for (int x : arr) {
       cout << x << " ";
   }

}
