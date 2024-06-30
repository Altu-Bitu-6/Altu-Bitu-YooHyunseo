#include <iostream>
#include <queue>

using namespace std;

void Josephus(int n, int k){
    
    queue<int> order;
    
    for(int i=1; i<=n; i++){
        
        order.push(i); // 1부터 n까지의 원소를 큐에 넣어줌
        
    }
    
    int cntk=0;
    
    cout << '<';
    
    while (1){
        
        int current = order.front(); // queue의 front 원소를 변수에 저장 
        
        if(++cntk==k){ // k번째 순서가 되면 
            
            cout << current; // 해당 원소 출력 
            
            order.pop(); // 원소 pop 
            
            if(order.empty()){ // 남은 원소가 없다면 괄호 닫고 종료 
                cout << '>' ;
                break;
            }
        
            else{ // 남은 원소가 있을 때 
                cout << ',' << ' ';
            }
            
            cntk=0;
            
        }
        else{ // k번째 원소가 아닌 경우 
            order.pop();
            order.push(current); // queue에 다시 push 
        }
        
    }
}



int main()
{
    int n, k;
    cin >> n >> k;
    
    Josephus(n, k);
}