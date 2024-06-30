#include <iostream>
#include <vector>

using namespace std;


int find666(int n){     // n번째 종말의 수를 찾는 함수 
    
    vector<int> arr;    // 666이 들어간 수를 저장하는 벡터 생성
    
    int a = 0;          // a에 저장된 수가 종말의 수일지 판별 
    
    while(arr.size() != n){ // arr에 원소가 n개 들어갈 때까지 반복
        
        int tmp = a;
        
        while(tmp){     // tmp가 0이 될 때까지 반복
            
            if(tmp%1000 == 666){    // tmp의 뒤 세자리 수가 666이면
                arr.push_back(a);   // a를 arr의 원소로 넣음
                break;
            }
            else{                   // 아닌 경우
                tmp/=10;            // tmp를 10으로 나눈 후 반복
            }
            
        }
        a++;            // 다음 정수를 a에 저장 
    }
    
    return arr.back();  // 벡터를 리턴
}

int main()
{
    int n;
    cin >> n;
    
    cout << find666(n);
    
    return 0;
}

