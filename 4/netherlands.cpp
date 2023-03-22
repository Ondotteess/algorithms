#include <iostream>
#include <vector>

using namespace std;

void netherlands(vector<int> nums) {
    int n = nums.size(), low, mid, high;
    low = mid = 0;
    high = n - 1;
    while (mid <= high) {
        if (nums[mid] == 0) swap(nums[mid++], nums[low++]);

        else if (nums[mid] == 1) mid++;

        else if (nums[mid] == 2) swap(nums[mid], nums[high--]);
}
  
int main(){
  vector<int> array1 = { 0, 2, 2, 2, 0, 1, 0, 2, 1, 0, 2, 1, 2, 1, 0, 2, 0, 1, 0, 2, 2, 1, 0, 0, 2, 1, 2, 1, 0, 2, 2 };
  
  niggerland(array1);
  
  for ( int x : array1 ){
    cout << x << " "; 
  }
}
