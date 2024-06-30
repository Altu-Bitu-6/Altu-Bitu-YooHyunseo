#include <iostream>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;               // 거점지를 방문한 횟수 n
    
    priority_queue<int> pq; // 선물을 가치있는 순서대로 저장하는 우선순위큐 pq
    
    while(n--){
        
        int a;
        cin >> a;
        
        
        if(a==0){           // 입력받은 수가 0이면 가장 가치 높은 선물 아이에게 주기
        
            if(pq.empty()){ // pq가 비어있으면 -1 출력
                cout << "-1" << '\n';
            }
            
            else{
                cout << pq.top() << '\n';   // 가장 가치있는 선물 가치 출력하고 pq에서 pop
                pq.pop();
            }
        }
        
        else{
        
            while(a--){         // 거점지에서 a개의 선물 충전
            
                int val;
                cin >> val;
                pq.push(val);   // 들어오는 선물의 가치 pq에 push
            }
        }
        
    }
    
}
