#include <iostream>
#include <string>

using namespace std;

void add(int &set, int x){       // add 연산의 경우
    set |= (1<<x);               // set의 x번째 비트를 1로 전환(합집합 이용)
}

void remove(int &set, int x){   // remove 연산의 경우
    set &= ~(1<<x);             // set의 x번째 비트를 0으로 전환(차집합 이용)
}

int check(int &set, int x){     // check 연산의 경우
    
    if( ( set & (1<<x) )!= 0){  // set의 x번째 비트가 1인 경우
        return 1;               // 1 반환
    }
    else{                       // set의 x번째 비트가 0인 경우
        return 0;               // 0 반환
    }
}

void toggle(int &set, int x){   // toggle 연산의 경우
    
    if( ( set & (1<<x) )!= 0){  // set의 x번째 비트가 1인 경우
        set &= ~(1<<x);         // 0으로 전환
    }
    else{                       // set의 x번째 비트가 0인 경우
        set |= (1<<x);          // 1로 전환 
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int m;
    cin >> m;       // 연산의 수 m 입력 
    
    int set=0;      // set에 20개의 원소를 저장할 것이므로 크기가 4byte(>20bit)인 int형 사용
    
    while(m--){     // m번의 연산 반복
        
        string ins;
        int x;
        
        cin >> ins;                 // 연산의 종류 입력 
        
        if(ins=="all"){             // all 연산의 경우
            set = ((1 << 21) - 1);  // set의 하위 20비트를 모두 1로 전환
        }
        else if(ins=="empty"){      // empty 연산의 경우 
            set = 0;                // set의 하위 20비트를 모두 0로 전환
        }
        
        else{               // 연산에 x가 필요한 경우 
            cin >> x;       // x도 입력
            
            if(ins=="add"){
                add(set, x);
            }
            else if(ins=="remove"){
                remove(set, x);
            }
            else if(ins=="check"){
                cout << check(set, x) << '\n';  //check일 경우만 출력 있음, 나머지 연산들은 set값만 계산 
            }
            else if(ins=="toggle"){
                toggle(set, x);
            }
        }
        
    }

    return 0;
}

