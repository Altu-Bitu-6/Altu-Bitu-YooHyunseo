#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const vector<int> normal_dir= {0,4,3,1,2};    // 반시계 방향으로 정상으로 순회할 경우 

int my_max(int a, int b, int c) {             // max 함수를 이용해 세 수 중 최댓값 구하는 함수 재정의
    
    return max(max(a, b), c);
}

int detectConcave(vector<pair<int, int>>& input){   // int pair가 저장된 벡터 input에 한 바퀴 순회 정보가 들어오면, 
                                                    // ㄱ자 도형의 바깥 쪽을 도는지 안 쪽을 도는지 확인함. 
    
    int index, prev=input[5].first;                 // 도형이 닫혀있으므로 i가 0일때는 인덱스 5의 방향을 확인한다. 
    
    for(int i=0; i<6; i++){
        
        if(input[i].first!=normal_dir[prev]){       // 해당 인덱스에서 전의 방향과 대비해 비정상적인 순서의 방향일 때, (안 쪽 두 번째 변을 돌고있는 겅우와 같다. )
            return i;                               // 인덱스를 리턴함.
        }
        prev = input[i].first;                      // 지금의 방향 값을 다음 순회 시에 사용하기 위해 prev에 저장. 
    }
}


int main()
{
    int k;
    cin >> k;                                       // 단위 넓이에서 참외 생산량 k 
    
    vector<pair<int, int>> input(6);                // 도형 변 순회 정보 input 
    int dir, len;// 입력을 위해 변수 선언
    
    for(int i=0; i<6; i++){                         // 육각형의 여섯 개 변에 대해

        cin >> dir >> len ;                         // 해당 변의 방향과 길이 입력
        input[i] = make_pair(dir, len);
        
    }
    
    int index = detectConcave(input);               // index에 안쪽 두 번째 변의 순서 저장
    int prev_index=index-1;                         // prev_index에 안쪽 첫 번째 변의 순서 저장
    if(index==0){
        prev_index=5;
    }
    
    
    int max_dir1 = my_max(input[0].second, input[2].second, input[4].second);   // 가로 세로 길이들 중 가장 긴 변의 길이를 my_max를 통해 구하기
    int max_dir2 = my_max(input[1].second, input[3].second, input[5].second);
    
    int min_dir1 = input[prev_index].second;    // 안쪽 변의 가로(또는 세로) 길이 저장
    int min_dir2 = input[index].second;         // 안쪽 변의 세로(또는 가로) 길이 저장

    int area = max_dir1 * max_dir2 - min_dir1 * min_dir2;   // 참외밭의 넓이 구하기 
    
    cout << area * k << '\n';                   // 참외 생산량 출력 
    
    return 0;
}