#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

    int partition(vector<int>& nums, int l, int r, int pivot) {
        int pivotValue = nums[pivot];
        swap(nums[pivot], nums[r]);

        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (nums[j] > pivotValue) {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }

    int quickSelect(vector<int>& nums, int k, int l, int r) {
        int pivot = l + rand() % (r - l + 1);

        int p = partition(nums, l, r, pivot);

        if (p + 1 == k)      return nums[p];
        else if (p + 1 > k)  return quickSelect(nums, k, l, p);
        else                 return quickSelect(nums, k, p + 1, r);
    
    }

int main() {

    vector<int> arr = { 1, 0, 12, 9, 4, 13, 2, 6, 19, 10, 11, 15, 18, 7, 17, 3, 8, 16, 5, 14 };

    srand(time(NULL));
    for (int k = 1; k < 20; k++) {
        int l = 0, r = arr.size() - 1;
        int kthSmallest = quickSelect(arr, k, l, r);
        cout << k << " " << kthSmallest << endl;
    }
    return 0;
}
