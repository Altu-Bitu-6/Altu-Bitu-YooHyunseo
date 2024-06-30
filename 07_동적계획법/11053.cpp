#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    int max_num = 0;
    
    vector<int> arr(n, 0);
    vector<int> dp(n, 1);           // 인덱스까지의 '가장 긴 증가하는 부분 수열'의 길이 저장 
    
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    
    for(int i=0; i<n; i++){
        
        for(int j=0; j<i; j++){     // i보다 작은 j를 순회하며 확인
            
            if(arr[i]>arr[j]){      // 수열이 증가한다면 
            
                dp[i] = ( (dp[i] > (dp[j]+1) )? dp[i] : (dp[j]+1) );    // 길이 갱신
            }
        }
        
        if(max_num <= dp[i]){       // dp 중 가장 값이 큰 것을 max_num에 저장 
            max_num = dp[i];
        }
    }
    
    cout << max_num << '\n';        // 가장 긴 수열의 길이 max_num을 출력 
}