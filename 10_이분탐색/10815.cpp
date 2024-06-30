#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int binarySearch(vector<int> &nums, int n, int key){
    
    int left = 0;
    int right = n-1;
    
    while(left<=right){
        
        int mid = (left+right)/2;
        
        if(nums[mid]==key){
            return 1;
        }
        else if(nums[mid] > key){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return 0;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    
    vector<int> nums(n);
    
    for(int i=0; i<n; i++){
        cin >> nums[i];
    }
    
    sort(nums.begin(), nums.end());

    int m;
    cin >> m;
    
    while(m--){
        int key;
        cin >> key;
        cout << binarySearch(nums, n, key) << ' ';
    }
    
    return 0;
}

