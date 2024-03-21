#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;                   // n 입력 
    
    priority_queue<int, vector<int>, greater<int> > number; // n개의 원소를 오름차순으로 저장할 우선순위큐 number 생성
    
    for(int i=0; i<n*n; i++){   // 표 전체 순회
        
        int input;
        cin >> input;
        number.push(input);     // 입력받은 수 number에 push
        
        if(number.size()>n){    // number의 원소가 n개보다 많아지면
            number.pop();       // 가장 작은 원소 pop
        }
    }
    
    cout << number.top();       // number에 남은 원소 중 가장 작은 원소 출력
}