#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    vector<int> score(n+1, 0);  // 입력을 통해 각 계단의 점수를 저장하는 벡터
    vector<int> dp(n+1, 0);     // i번째 계단의 누적된 점수를 저장하는 벡터
    vector<int> tmp(n+1, 0);    // i+1번째 누적점수를 쉽게 계산하기 위해 i-1번 계단을 밟지 않은 경우에 해당하는 i의 누적점수를 저장하는 벡터 
    
    for(int i=1; i<=n; i++){
        cin >> score[i];
    }
    
    dp[1] = score[1];
    dp[2] = score[1] + score[2];
    tmp[2] = score[2];
    
    for(int i=3; i<=n; i++){
        
        dp[i] = max(tmp[i-1], dp[i-2])+score[i];
        tmp[i] = dp[i-2]+score[i];
        
    }
    
    cout << dp[n] << '\n';
    
}