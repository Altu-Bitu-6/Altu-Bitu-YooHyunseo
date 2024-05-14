#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cnt[100001] = {0};

int getLongest(vector<int>& a, int k){
    
    int p1 = 0, p2 = 0, max_length = 0;
    int array_size = a.size();
    
    while(p1<array_size){
        
        if( cnt[a[p1]] >= k ){   // p1이 가리키는 원소의 개수가 k개 초과한 경우 
            cnt[a[p2]]--;        // 수열을 앞에서부터 하나씩 잘라내기 
            p2++;                // p2는 수열의 가장 첫번째 원소를 가리킴 
        }
        else{
            cnt[a[p1]]++;       // p1이 가리키는 원소를 수열의 맨 뒤에 추가
            p1++;               // p1은 다음 원소를 가리킴 
        }
        max_length = max(max_length, p1-p2);
    }
    return max_length;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    
    for(int i=0; i<n; i++){ // 길이가 n인 수열 a에 입력(index: 0 ~ n-1)
        cin >> a[i];
    }
    
    cout << getLongest(a, k);
}