#include <iostream>
#include <vector>
using namespace std;

int types[3001] = {0};

int eatMaxChobap(vector<int> &belt, int n, int d, int k, int c){
    
    // n: 벨트 위 접시 수  d: 초밥의 가짓수
    // k: 연속해서 먹는 접시의 수, c: 쿠폰 번호
    
    int p1 = 0, p2 = k-1;
    int max_type = 0;
    
    for(int i=0; i<k; i++){         // belt의 0~k-1번 원소를 window 초기화 시 사용 
        
        if(types[belt[i]] == 0){
            max_type++;             // 첫번째 윈도우의 초밥종류 개수 저장 
        }
        
        types[belt[i]]++;           // 첫번째 윈도우의 type정보 업데이트
    }
    
    int temp_cnt = max_type;        // 현재 window의 초밥종류 정보를 저장하는 변수
    
    if(types[c]==0){
        max_type++;
    }
    
    for(int p1=1; p1<n; p1++){      // window 시작점인 p1이 벨트 위의 초밥들을 순회 
        
        p2 = (p2+1) % n;            // window 크기 k로 유지
        if(types[belt[p2]]==0){     // 추가된 원소에 대한 count 갱신  
            temp_cnt++;
        }
        types[belt[p2]]++;
        
        if(types[belt[p1-1]]==1){   // 삭제된 원소에 대한 count 갱신 
            temp_cnt--;
        }
        types[belt[p1-1]]--;
        
        if( types[c]==0 ){          // 지금 window에서 쿠폰초밥을 안먹었다면 
           max_type = max(max_type, temp_cnt+1);
        }
        else{
           max_type = max(max_type, temp_cnt); 
        }
    }
    
    return max_type;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); 
    cout.tie(0);
    
    int n, d, k, c;
    cin >> n >> d >> k >> c;
    
    vector<int> belt(n+1);
    
    for(int i=0; i<n; i++){
        cin >> belt[i];
    }
    
    cout << eatMaxChobap(belt, n, d, k, c);
}